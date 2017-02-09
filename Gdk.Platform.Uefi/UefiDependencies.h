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


#ifndef __UEFI_DEPENDENCIES_H__
#define __UEFI_DEPENDENCIES_H__

#include <intrin.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
  #define _DEBUG_DEFINED
  #pragma push_macro("_DEBUG")
  #undef _DEBUG
#endif

#ifdef _ASSERT
  #define _ASSERT_DEFINED
  #pragma push_macro("_ASSERT")
  #undef _ASSERT
#endif

#ifdef NULL
  #define NULL_DEFINED
  #pragma push_macro("NULL")
  #undef NULL
#endif

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>

#ifdef NULL_DEFINED
  #undef NULL_DEFINED
  #ifdef NULL
    #undef NULL
  #endif
  #pragma pop_macro("NULL")
#endif

#ifdef _ASSERT_DEFINED
  #undef _ASSERT_DEFINED
  #ifdef _ASSERT
    #undef _ASSERT
  #endif
  #pragma pop_macro("_ASSERT")
#endif

#ifdef _DEBUG_DEFINED
  #undef _DEBUG_DEFINED
  #ifdef _DEBUG
    #undef _DEBUG
  #endif
  #pragma pop_macro("_DEBUG")
#endif

// DebugLibCompatibility redefines some of the macros defined in
// Library/DebugLib.h because they conflict with VC++ standard
// defines.
#include "DebugLibCompatibility.h"

EFI_STATUS
EFIAPI
UefiBootServicesTableLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
UefiRuntimeServicesTableLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
UefiLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
HobLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );

EFI_STATUS
EFIAPI
UefiMain(
  IN  EFI_HANDLE        Handle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
  );

extern void Main();

#ifdef __cplusplus
}
#endif

#endif