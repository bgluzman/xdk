/*
   eXokernel Development Kit (XDK)

   Based on code by Samsung Research America Copyright (C) 2013
 
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  
*/

#ifndef __NVME_COMMAND_H__
#define __NVME_COMMAND_H__

#include "nvme_command_structs.h"

/*
  Each submission command is 64 bytes long.
*/

class Submission_command_slot : public nvme_sub_command_common
{
public:
  void clear() {
    __builtin_memset(this, 0, sizeof(nvme_sub_command_common));
  }
  void * raw() const { return ((void *) this); }
};


class Completion_command_slot : public nvme_comp_command_common
{
public:
  void * raw() const { return ((void *) this); }
  void dump();
};  


#endif // __NVME_COMMAND_H__
