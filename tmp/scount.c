/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <proc.h>
/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
	
	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[getpid()];
		proc->counter_for_syscall[10] ++;
	}

extern	struct	sentry	semaph[];

	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
	{
		
    	if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[10] += time;

	}	
	return(SYSERR);}

	
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[10] += time;

	}
	return(semaph[sem].semcnt);
}
