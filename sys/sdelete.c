/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{
	
	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[getpid()];
		proc->counter_for_syscall[11] ++;
	}

	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);
		
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[11] += time;

	}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);

	
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[11] += time;

	}
	return(OK);
}
