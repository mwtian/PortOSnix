/*
 * Minithreads x86_64/OSX Machine Dependent Code
 *
 * You should not need to modify this file.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>     // included for currentTimeMillis
#include <sys/timeb.h>

#include "defs.h"
#include "machineprimitives.h"
#include "interrupts_private.h"

extern interrupt_level_t interrupt_level; 

uint64_t currentTimeMillis() {  
  struct timeb timebuffer;
  uint64_t lt = 0;
  ftime(&timebuffer);
  lt = timebuffer.time;
  lt = lt*1000;
  lt = lt+timebuffer.millitm;
  return lt;
}


/*
 * atomic_clear
 *
 */

void atomic_clear(tas_lock_t *l) {
	*l = 0;	
}

