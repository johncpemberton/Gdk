// /** The BSD 2-Clause License
//
// Copyright (c) 2015, John Pemberton
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

#include "UefiDependencies.h"


void TestString()
{
  DEBUG((EFI_D_ERROR, "Initializing string...\n"));
//  std::string mystr = "Testing yolo swaggins\n";
  DEBUG((EFI_D_ERROR, "Printing string...\n"));
//  DEBUG((EFI_D_ERROR, mystr.data()));
  DEBUG((EFI_D_ERROR, "Done Printing String\n\n"));


  DEBUG((EFI_D_ERROR, "Starting string loop...\n"));
  for (int i = 0; i < 20; ++i) {
    DEBUG((EFI_D_ERROR, "initializing...\n"));
//    mystr = "Number: ";
    DEBUG((EFI_D_ERROR, "appending %d...\n", i));
    //mystr += std::to_string(i);
    DEBUG((EFI_D_ERROR, "appending new line...\n"));
//    mystr += "\n";
  }
  DEBUG((EFI_D_ERROR, "Done with string loop.\n"));

}