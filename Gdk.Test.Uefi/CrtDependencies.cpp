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

//#include <string>
//#include <functional>
//#include <vector>
//
//#include "UefiDependencies.h"
//#include <Library\BaseMemoryLib.h>
//#include <malloc.h>
////
//// Parameter Handler
////
//void __cdecl _invalid_parameter(
//  _In_opt_z_ wchar_t const*,
//  _In_opt_z_ wchar_t const*,
//  _In_opt_z_ wchar_t const*,
//  _In_       unsigned int,
//  _In_       uintptr_t
//  )
//{
//  // TODO
//}
//
//void __cdecl _invalid_parameter_noinfo(void)
//{
//  // TODO
//}
//
//void __cdecl _invalid_parameter_noinfo_noreturn(void)
//{
//  // TODO
//}
//
//int __cdecl _CrtDbgReport(
//  _In_       int         _ReportType,
//  _In_opt_z_ char const* _FileName,
//  _In_       int         _Linenumber,
//  _In_opt_z_ char const* _ModuleName,
//  _In_opt_z_ char const* _Format,
//  ...)
//{
//  // TODO
//  return 0;
//}
//
//int __cdecl _CrtDbgReportW(
//  _In_       int            _ReportType,
//  _In_opt_z_ wchar_t const* _FileName,
//  _In_       int            _LineNumber,
//  _In_opt_z_ wchar_t const* _ModuleName,
//  _In_opt_z_ wchar_t const* _Format,
//  ...)
//{
//  // TODO
//  return 0;
//}
//
////
//// Exceptions
////
//void __cdecl std::_Xbad_alloc(void)
//{
//  // TODO
//}
//
//void __cdecl std::_Xlength_error(const char*err_msg)
//{
//  // TODO
//}
//
//void __cdecl std::_Xout_of_range(const char *err_msg)
//{
//  // TODO
//}
//
////
//// Intrinsics
////
//void* __cdecl memmove(
//  _Out_writes_bytes_all_opt_(_Size) void*       _Dst,
//  _In_reads_bytes_opt_(_Size)       const void* _Src,
//  _In_                              size_t      _Size
//  )
//{
//  DEBUG((EFI_D_ERROR, "Memmove intrinsic called.\n"));
//  ASSERT(_Dst != NULL);
//  ASSERT(_Src != NULL);
//
//  if (gBS != NULL) {
//    const char *src = reinterpret_cast<const char *>(_Src);
//    std::vector<char> v(src, src + _Size);
//    gBS->CopyMem(_Dst, v.data(), _Size);
//  }
//  return _Dst;
//}
//
//
// Memory Allocation
//
//void __cdecl operator delete(void *Ptr)
//{
//  DEBUG((EFI_D_ERROR, "Delete operator called.\n"));
//  ASSERT(Ptr != NULL);
//
//  EFI_STATUS Status = gBS->FreePool(Ptr);
//  ASSERT_EFI_ERROR(Status);
//}
//
//void *__cdecl operator new(size_t Size)
//{
//  DEBUG((EFI_D_ERROR, "New operator called for size: %ld.\n", Size));
//  ASSERT(Size > 0);
//
//  void *Ptr;
//  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
//  if (EFI_ERROR(Status))
//  Ptr = nullptr;
//
//  return Ptr;
//}
//
//void __cdecl operator delete[](void *Ptr)
//{
//  DEBUG((EFI_D_ERROR, "Delete[] operator called.\n"));
//  ASSERT(Ptr != NULL);
//
//  EFI_STATUS Status = gBS->FreePool(Ptr);
//  ASSERT_EFI_ERROR(Status);
//}
//
//void *__cdecl operator new[](size_t Size)
//{
//  DEBUG((EFI_D_ERROR, "New[] operator called for size: %ld.\n", Size));
//  ASSERT(Size > 0);
//
//  void *Ptr;
//  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
//  if (EFI_ERROR(Status))
//    Ptr = nullptr;
//
//  return nullptr;
//}
//
//__declspec(restrict)
//void* __cdecl calloc(size_t _Count, size_t _Size)
//{
//  DEBUG((EFI_D_ERROR, "Calloc called for count: %ld and size: %ld.\n", _Count, _Size));
//  ASSERT(_Count > 0);
//  ASSERT(_Size > 0);
//
//  void *Ptr;
//  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, _Size * _Count, &Ptr);
//  if (EFI_ERROR(Status))
//    Ptr = nullptr;
//
//  return Ptr;
//}
//
//void __cdecl free(void* _Block)
//{
//  DEBUG((EFI_D_ERROR, "Free called.\n"));
//  ASSERT(_Block != NULL);
//
//  EFI_STATUS Status = gBS->FreePool(_Block);
//  ASSERT_EFI_ERROR(Status);
//}
//
//__declspec(restrict)
//void* __cdecl malloc(size_t _Size)
//{
//  DEBUG((EFI_D_ERROR, "Malloc called for size: %ld.\n", _Size));
//  ASSERT(_Size > 0);
//
//  void *Ptr;
//  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, _Size, &Ptr);
//  if (EFI_ERROR(Status))
//    Ptr = nullptr;
//
//  return Ptr;
//}
//
//__declspec(restrict)
//void* __cdecl realloc(void*  _Block, size_t _Size)
//{
//  DEBUG((EFI_D_ERROR, "Realloc called for size: %ld.\n", _Size));
//  ASSERT(_Size > 0);
//
//  free(_Block);
//
//  void *Ptr;
//  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, _Size, &Ptr);
//  if (EFI_ERROR(Status))
//    Ptr = nullptr;
//
//  return Ptr;
//}

////void __cdecl operator delete(void *Ptr, const std::nothrow_t &)
////{
////  DEBUG((EFI_D_ERROR, "Delete (nothrow) operator called.\n"));
////  ASSERT(Ptr != NULL);
////
////  EFI_STATUS Status = gBS->FreePool(Ptr);
////  ASSERT_EFI_ERROR(Status);
////}
////
////void *__cdecl operator new(size_t Size, const std::nothrow_t &)
////{
////  DEBUG((EFI_D_ERROR, "New (nothrow) operator called for size: %ld.\n", Size));
////  ASSERT(Size > 0);
////
////  void *Ptr;
////  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
////  if (EFI_ERROR(Status))
////    Ptr = nullptr;
////
////  return Ptr;
////}
////
////void __cdecl operator delete[](void *Ptr, const std::nothrow_t &)
////{
////  DEBUG((EFI_D_ERROR, "Delete[] (nothrow) operator called.\n"));
////  ASSERT(Ptr != NULL);
////
////  EFI_STATUS Status = gBS->FreePool(Ptr);
////  ASSERT_EFI_ERROR(Status);
////}
////
////void *__cdecl operator new[](size_t Size, const std::nothrow_t &)
////{
////  DEBUG((EFI_D_ERROR, "New[] (nothrow) operator called for size: %ld.\n", Size));
////  ASSERT(Size > 0);
////
////  void *Ptr;
////  EFI_STATUS Status = gBS->AllocatePool(EfiBootServicesData, Size, &Ptr);
////  if (EFI_ERROR(Status))
////    Ptr = nullptr;
////
////  return Ptr;
////}
//
////
//// Standard I/O
////
////int __cdecl __stdio_common_vsprintf(
////  _In_                                    unsigned __int64 _Options,
////  _Out_writes_z_(_BufferCount)            char*            _Buffer,
////  _In_                                    size_t           _BufferCount,
////  _In_z_ _Printf_format_string_params_(2) char const*      _Format,
////  _In_opt_                                _locale_t        _Locale,
////  va_list          _ArgList
////  )
////{
////
////}
////
////int __cdecl __stdio_common_vsprintf_s(
////  _In_                                    unsigned __int64 _Options,
////  _Out_writes_z_(_BufferCount)            char*            _Buffer,
////  _In_                                    size_t           _BufferCount,
////  _In_z_ _Printf_format_string_params_(2) char const*      _Format,
////  _In_opt_                                _locale_t        _Locale,
////  va_list          _ArgList
////  )
////{
////
////}
////
////int __cdecl __stdio_common_vsnprintf_s(
////  _In_                                    unsigned __int64 _Options,
////  _Out_writes_z_(_BufferCount)            char*            _Buffer,
////  _In_                                    size_t           _BufferCount,
////  _In_                                    size_t           _MaxCount,
////  _In_z_ _Printf_format_string_params_(2) char const*      _Format,
////  _In_opt_                                _locale_t        _Locale,
////  va_list          _ArgList
////  )
////{
////
////}
////
////int __cdecl __stdio_common_vsprintf_p(
////  _In_                                    unsigned __int64 _Options,
////  _Out_writes_z_(_BufferCount)            char*            _Buffer,
////  _In_                                    size_t           _BufferCount,
////  _In_z_ _Printf_format_string_params_(2) char const*      _Format,
////  _In_opt_                                _locale_t        _Locale,
////  va_list          _ArgList
////  )
////{
////
////}
////
