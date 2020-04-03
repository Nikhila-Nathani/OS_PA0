/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	
	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[getpid()];
		proc->counter_for_syscall[13] ++;
	}
	short	*nxtdev;

	if (isbadpid(pid)){
	
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[13] += time;

	}
		return(SYSERR);
	}
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;


	
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[13] += time;

	}
	return(OK);
}
