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


#ifndef __DEBUG_LIB_COMPATIBILITY__
#define __DEBUG_LIB_COMPATIBILITY__

#ifdef ASSERT
  #undef ASSERT
#endif

#ifdef DEBUG
  #undef DEBUG
#endif

#ifdef ASSERT_EFI_ERROR
  #undef ASSERT_EFI_ERROR
#endif

#ifdef ASSERT_PROTOCOL_ALREADY_INSTALLED
  #undef ASSERT_PROTOCOL_ALREADY_INSTALLED
#endif 

#ifdef CR
  #undef CR
#endif

/**  
  Internal worker macro that calls DebugAssert().

  This macro calls DebugAssert(), passing in the filename, line number, and an
  expression that evaluated to FALSE.

  @param  Expression  Boolean expression that evaluated to FALSE

**/
#define _ALT_ASSERT(Expression)  DebugAssert (__FILE__, __LINE__, #Expression)


/**  
  Internal worker macro that calls DebugPrint().

  This macro calls DebugPrint() passing in the debug error level, a format 
  string, and a variable argument list.

  @param  Expression  Expression containing an error level, a format string, 
                      and a variable argument list based on the format string.

**/
#define _ALT_DEBUG(Expression)   DebugPrint Expression


/**  
  Macro that calls DebugAssert() if an expression evaluates to FALSE.

  If MDEPKG_NDEBUG is not defined and the DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED 
  bit of PcdDebugProperyMask is set, then this macro evaluates the Boolean 
  expression specified by Expression.  If Expression evaluates to FALSE, then 
  DebugAssert() is called passing in the source filename, source line number, 
  and Expression.

  @param  Expression  Boolean expression.

**/
#if !defined(MDEPKG_NDEBUG)       
  #define ASSERT(Expression)        \
    do {                            \
      if (DebugAssertEnabled ()) {  \
        if (!(Expression)) {        \
          _ALT_ASSERT (Expression);     \
        }                           \
      }                             \
    } while (FALSE)
#else
  #define ASSERT(Expression)
#endif

/**  
  Macro that calls DebugPrint().

  If MDEPKG_NDEBUG is not defined and the DEBUG_PROPERTY_DEBUG_PRINT_ENABLED 
  bit of PcdDebugProperyMask is set, then this macro passes Expression to 
  DebugPrint().

  @param  Expression  Expression containing an error level, a format string, 
                      and a variable argument list based on the format string.
  

**/
#if !defined(MDEPKG_NDEBUG)      
  #define DEBUG(Expression)        \
    do {                           \
      if (DebugPrintEnabled ()) {  \
        _ALT_DEBUG (Expression);       \
      }                            \
    } while (FALSE)
#else
  #define DEBUG(Expression)
#endif

/**  
  Macro that calls DebugAssert() if an EFI_STATUS evaluates to an error code.

  If MDEPKG_NDEBUG is not defined and the DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED 
  bit of PcdDebugProperyMask is set, then this macro evaluates the EFI_STATUS 
  value specified by StatusParameter.  If StatusParameter is an error code, 
  then DebugAssert() is called passing in the source filename, source line 
  number, and StatusParameter.

  @param  StatusParameter  EFI_STATUS value to evaluate.

**/
#if !defined(MDEPKG_NDEBUG)
  #define ASSERT_EFI_ERROR(StatusParameter)                                              \
    do {                                                                                 \
      if (DebugAssertEnabled ()) {                                                       \
        if (EFI_ERROR (StatusParameter)) {                                               \
          DEBUG ((EFI_D_ERROR, "\nASSERT_EFI_ERROR (Status = %r)\n", StatusParameter));  \
          _ALT_ASSERT (!EFI_ERROR (StatusParameter));                                        \
        }                                                                                \
      }                                                                                  \
    } while (FALSE)
#else
  #define ASSERT_EFI_ERROR(StatusParameter)
#endif

/**  
  Macro that calls DebugAssert() if a protocol is already installed in the 
  handle database.

  If MDEPKG_NDEBUG is defined or the DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED bit 
  of PcdDebugProperyMask is clear, then return.

  If Handle is NULL, then a check is made to see if the protocol specified by Guid 
  is present on any handle in the handle database.  If Handle is not NULL, then 
  a check is made to see if the protocol specified by Guid is present on the 
  handle specified by Handle.  If the check finds the protocol, then DebugAssert() 
  is called passing in the source filename, source line number, and Guid.

  If Guid is NULL, then ASSERT().

  @param  Handle  The handle to check for the protocol.  This is an optional 
                  parameter that may be NULL.  If it is NULL, then the entire 
                  handle database is searched.

  @param  Guid    The pointer to a protocol GUID.

**/
#if !defined(MDEPKG_NDEBUG)
  #define ASSERT_PROTOCOL_ALREADY_INSTALLED(Handle, Guid)                               \
    do {                                                                                \
      if (DebugAssertEnabled ()) {                                                      \
        VOID  *Instance;                                                                \
        ASSERT (Guid != NULL);                                                          \
        if (Handle == NULL) {                                                           \
          if (!EFI_ERROR (gBS->LocateProtocol ((EFI_GUID *)Guid, NULL, &Instance))) {   \
            _ALT_ASSERT (Guid already installed in database);                               \
          }                                                                             \
        } else {                                                                        \
          if (!EFI_ERROR (gBS->HandleProtocol (Handle, (EFI_GUID *)Guid, &Instance))) { \
            _ALT_ASSERT (Guid already installed on Handle);                                 \
          }                                                                             \
        }                                                                               \
      }                                                                                 \
    } while (FALSE)
#else
  #define ASSERT_PROTOCOL_ALREADY_INSTALLED(Handle, Guid)
#endif


/**
  Macro that calls DebugAssert() if the containing record does not have a 
  matching signature.  If the signatures matches, then a pointer to the data 
  structure that contains a specified field of that data structure is returned.  
  This is a lightweight method hide information by placing a public data 
  structure inside a larger private data structure and using a pointer to the 
  public data structure to retrieve a pointer to the private data structure.

  If MDEPKG_NDEBUG is defined or the DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED bit 
  of PcdDebugProperyMask is clear, then this macro computes the offset, in bytes,
  of the field specified by Field from the beginning of the data structure specified 
  by TYPE.  This offset is subtracted from Record, and is used to return a pointer 
  to a data structure of the type specified by TYPE.

  If MDEPKG_NDEBUG is not defined and the DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED bit
  of PcdDebugProperyMask is set, then this macro computes the offset, in bytes, 
  of field specified by Field from the beginning of the data structure specified 
  by TYPE.  This offset is subtracted from Record, and is used to compute a pointer
  to a data structure of the type specified by TYPE.  The Signature field of the 
  data structure specified by TYPE is compared to TestSignature.  If the signatures 
  match, then a pointer to the pointer to a data structure of the type specified by 
  TYPE is returned.  If the signatures do not match, then DebugAssert() is called 
  with a description of "CR has a bad signature" and Record is returned.  

  If the data type specified by TYPE does not contain the field specified by Field, 
  then the module will not compile.

  If TYPE does not contain a field called Signature, then the module will not 
  compile.

  @param  Record         The pointer to the field specified by Field within a data 
                         structure of type TYPE.

  @param  TYPE           The name of the data structure type to return  This 
                         data structure must contain the field specified by Field. 

  @param  Field          The name of the field in the data structure specified 
                         by TYPE to which Record points.

  @param  TestSignature  The 32-bit signature value to match.

**/
#if !defined(MDEPKG_NDEBUG)
  #define CR(Record, TYPE, Field, TestSignature)                                              \
    (DebugAssertEnabled () && (BASE_CR (Record, TYPE, Field)->Signature != TestSignature)) ?  \
    (TYPE *) (_ALT_ASSERT (CR has Bad Signature), Record) :                                       \
    BASE_CR (Record, TYPE, Field)
#else
  #define CR(Record, TYPE, Field, TestSignature)                                              \
    BASE_CR (Record, TYPE, Field)
#endif

#endif