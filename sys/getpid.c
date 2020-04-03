/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[currpid];
		proc->counter_for_syscall[2] ++;
	}


	
	    if(syscall_flag==1){
		struct pentry *proc = &proctab[currpid];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[2] += time;

	}


	return(currpid);
}
