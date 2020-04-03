/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{

	STATWORD ps;    
	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[getpid()];
		proc->counter_for_syscall[18] ++;
	}

	if (n<0 || clkruns==0){
		if(syscall_flag==1){
			struct pentry *proc = &proctab[getpid()];
			int time = ctr1000 - tStart;
			proc->time_spent_syscall[18] += time;
		}
		return(SYSERR);
	}
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		
    		if(syscall_flag==1){
			struct pentry *proc = &proctab[getpid()];
			int time = ctr1000 - tStart;
			proc->time_spent_syscall[18] += time;

		}	
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	
    	if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[18] += time;

	}
	return(OK);
}
