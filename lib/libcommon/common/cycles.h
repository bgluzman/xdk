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

/*
  Authors:
  Copyright (C) 2013, Daniel G. Waddington <d.waddington@samsung.com>
*/

#ifndef __CYCLES_H__
#define __CYCLES_H__

#include <stdlib.h>
#include <linux/perf_event.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "types.h"

#ifndef INLINE 
#define INLINE inline __attribute__((always_inline))
#endif 

#if defined(__i386__) || defined(__amd64__)

#if defined(__amd64__)

/** 
 * Reads complete 40 bit counter into 64 bit value.
 * @return the read value. 
 */
INLINE cpu_time_t rdtsc() {
  unsigned a, d;
  asm volatile("lfence"); // should be mfence for AMD
  asm volatile("rdtsc" : "=a" (a), "=d" (d)); 
  return ((unsigned long long) a) | (((unsigned long long) d) << 32);    
}

/** 
 * Reads low 32 bits of the timestamp counter.
 * @return the read value. 
 */
INLINE uint32_t rdtsc_low() {
  uint32_t a;
  asm volatile("lfence"); // should be mfence for AMD
  asm volatile("rdtsc" : "=a" (a)); //, "=d" (d)); 
  return a;
}


#elif defined(__i386)

/** 
 * Reads complete 40 bit counter into 64 bit value.
 * @return the read value. 
 */
INLINE cpu_time_t rdtsc() {
  unsigned long long ret;
  asm volatile("lfence"); // should be mfence for AMD
  asm volatile("rdtsc": "=A" (ret));
  return ret;
}

#endif


/**
 * Returns the frequency of the timestamp counters in MHz.
 * It does so by parsing the output of the "dmesg" command on Linux-like OSes.
 *
 * @return the TSC frequency in megahertz.
 */
double get_tsc_frequency_in_mhz(void); 

#elif defined(__arm__)

/* From https://github.com/thoughtpolic/enable_arm_pmu/blob/master/perf_event_open.c */

static int fddev = -1;
__attribute__((constructor)) static void
init(void) {
  static struct perf_event_attr attr;
  attr.type = PERF_TYPE_HARDWARE;
  attr.config = PERF_COUNT_HW_CPU_CYCLES;
  fddev = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
}

__attribute__((destructor)) static void
fini(void) {
  close(fddev);
}

static inline long long rdtsc() {
  long long result = 0;
  if (read(fddev, &result, sizeof(result)) < sizeof(result)) return 0;
  return result;
}

/**
 * Returns the frequency of the timestamp counters in MHz.
 * It does so by parsing the output of the "dmesg" command on Linux-like OSes.
 *
 * @return the TSC frequency in megahertz.
 */
double get_tsc_frequency_in_mhz(void); 


#else
#error Platform not supported.
#endif

#endif
