/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	STATWORD ps;    
	struct	pentry	*pptr;

	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[getpid()];
		proc->counter_for_syscall[3] ++;
	}

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		
		if(syscall_flag==1){
			struct pentry *proc = &proctab[getpid()];
			int time = ctr1000 - tStart;
			proc->time_spent_syscall[3] += time;

		}	
		return(SYSERR);
	}
	restore(ps);

	 if(syscall_flag==1){
              struct pentry *proc = &proctab[getpid()];
              int time = ctr1000 - tStart;
              proc->time_spent_syscall[3] += time;

         }

	return(pptr->pprio);
}
