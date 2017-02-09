// /** The BSD 2-Clause License
//
// Copyright (c) 2017, John Pemberton
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// **/


#define _HAS_EXCEPTIONS 0
#define _ITERATOR_DEBUG_LEVEL 0
#define _CRT_SECURE_NO_WARNINGS

#include "UefiDependencies.h"
#include "Platform.hpp"


#pragma section(".CRT$XCA", long, read) // First C++ Initializer
#pragma section(".CRT$XCZ", long, read) // Last C++ Initializer
#pragma section(".CRT$XIA", long, read) // First C Initializer
#pragma section(".CRT$XIZ", long, read) // Last C Initializer

// Put .CRT data into .rdata section
#pragma comment(linker, "/merge:.CRT=.rdata")

typedef void(__cdecl* _PVFV)(void);
typedef int(__cdecl* _PIFV)(void);

__declspec(allocate(".CRT$XIA")) _PIFV __xi_a[] = { 0 };
__declspec(allocate(".CRT$XIZ")) _PIFV __xi_z[] = { 0 };
__declspec(allocate(".CRT$XCA")) _PVFV __xc_a[] = { 0 };
__declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[] = { 0 };

extern "C" __declspec(allocate(".CRT$XIA")) _PIFV __xi_a[];
extern "C" __declspec(allocate(".CRT$XIZ")) _PIFV __xi_z[];    /* C initializers */
extern "C" __declspec(allocate(".CRT$XCA")) _PVFV __xc_a[];
extern "C" __declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[];    /* C++ initializers */

int __cdecl _initterm_e(_PIFV * pfbegin, _PIFV * pfend)
{
  int ret = 0;
  //
  // Walk the table of function pointers from the bottom up, until
  // the end is encountered. Do not skip the first entry. The initial
  // value of pfbegin points to the first valid entry. Do not try to
  // execute what pfend points to. Only entries before pfend are valid.
  //
  while (pfbegin < pfend && ret == 0)
  {
    DEBUG((EFI_D_ERROR, "Executing C initializer...\n", *pfbegin));
    //
    // If current table entry is non-NULL, call thru it.
    //
    if (*pfbegin != NULL) {
      DEBUG((EFI_D_ERROR, "%08X\n", *pfbegin));
      ret = (**pfbegin)();
    }
++pfbegin;
  }

  return ret;
}

void __cdecl _initterm(_PVFV * pfbegin, _PVFV * pfend)
{
  //
  // Walk the table of function pointers from the bottom up, until
  // the end is encountered. Do not skip the first entry. The initial
  // value of pfbegin points to the first valid entry. Do not try to
  // execute what pfend points to. Only entries before pfend are valid.
  //
  while (pfbegin < pfend)
  {
    DEBUG((EFI_D_ERROR, "Executing C++ initializer...\n"));
    //
    // If current table entry is non-NULL, call thru it.
    //
    if (*pfbegin != NULL)
      (**pfbegin)();
    ++pfbegin;
  }
}

void InitStaticObjects()
{
  DEBUG((EFI_D_ERROR, "Initializing static objects...\n"));
  if (_initterm_e(__xi_a, __xi_z) != 0) {
    DEBUG((EFI_D_ERROR, "Looks like one of the C initializers failed.\n"));
  }
  else {
    DEBUG((EFI_D_ERROR, "Successfully initialized C objects. Initializing C++ objects...\n"));
    _initterm(__xc_a, __xc_z);
  }
  DEBUG((EFI_D_ERROR, "Done initializing static objects.\n"));
}


void __cdecl core_delete(void *Ptr)
{
  DEBUG((EFI_D_ERROR, "Delete operator called.\n"));
  ASSERT(Ptr != NULL);

  EFI_STATUS Status = gBS->FreePool(Ptr);
  ASSERT_EFI_ERROR(Status);
}

void *__cdecl core_new(size_t Size)
{
  DEBUG((EFI_D_ERROR, "New operator called for size: %ld.\n", Size));
  ASSERT(Size > 0);

  void *Ptr;
  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
  if (EFI_ERROR(Status))
    Ptr = nullptr;

  return Ptr;
}

void __cdecl core_delete_arr(void *Ptr)
{
  DEBUG((EFI_D_ERROR, "Delete[] operator called.\n"));
  ASSERT(Ptr != NULL);

  EFI_STATUS Status = gBS->FreePool(Ptr);
  ASSERT_EFI_ERROR(Status);
}

void *__cdecl core_new_arr(size_t Size)
{
  DEBUG((EFI_D_ERROR, "New[] operator called for size: %ld.\n", Size));
  ASSERT(Size > 0);

  void *Ptr;
  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
  if (EFI_ERROR(Status))
    Ptr = nullptr;

  return Ptr;
}

void *__cdecl operator new(size_t Size)
{
  return core_new(Size);
}

void *__cdecl operator new[](size_t Size)
{
  return core_new_arr(Size);
}

void __cdecl operator delete(void *Block)
{
  return core_delete(Block);
}

void __cdecl operator delete[](void *Block)
{
  return core_delete_arr(Block);
}

void __cdecl operator delete(void *Block, size_t Size)
{
  (void)Size;
  return core_delete(Block);
}

void __cdecl operator delete[](void *Block, size_t Size)
{
  (void)Size;
  return core_delete_arr(Block);
}


//void __cdecl operator delete(void *Ptr, const std::nothrow_t &)
//{
//  DEBUG((EFI_D_ERROR, "Delete (nothrow) operator called.\n"));
//  ASSERT(Ptr != NULL);
//
//  EFI_STATUS Status = gBS->FreePool(Ptr);
//  ASSERT_EFI_ERROR(Status);
//}
//
//void *__cdecl operator new(size_t Size, const std::nothrow_t &)
//{
//  DEBUG((EFI_D_ERROR, "New (nothrow) operator called for size: %ld.\n", Size));
//  ASSERT(Size > 0);
//
//  void *Ptr;
//  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
//  if (EFI_ERROR(Status))
//    Ptr = nullptr;
//
//  return Ptr;
//}
//
//void __cdecl operator delete[](void *Ptr, const std::nothrow_t &)
//{
//  DEBUG((EFI_D_ERROR, "Delete[] (nothrow) operator called.\n"));
//  ASSERT(Ptr != NULL);
//
//  EFI_STATUS Status = gBS->FreePool(Ptr);
//  ASSERT_EFI_ERROR(Status);
//}
//
//void *__cdecl operator new[](size_t Size, const std::nothrow_t &)
//{
//  DEBUG((EFI_D_ERROR, "New[] (nothrow) operator called for size: %ld.\n", Size));
//  ASSERT(Size > 0);
//
//  void *Ptr;
//  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
//  if (EFI_ERROR(Status))
//    Ptr = nullptr;
//
//  return Ptr;
//}

EFI_STATUS
EFIAPI
UefiMain(
  IN  EFI_HANDLE        Handle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
  )
{
  InitStaticObjects();
  Main();
  return EFI_SUCCESS;
}

// TODO
