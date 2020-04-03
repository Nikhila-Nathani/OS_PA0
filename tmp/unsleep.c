/* unsleep.c - unsleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * unsleep  --  remove  process from the sleep queue prematurely
 *------------------------------------------------------------------------
 */
SYSCALL	unsleep(int pid)
{
	
	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[getpid()];
		proc->counter_for_syscall[25] ++;
	}

	STATWORD ps;    
	struct	pentry	*pptr;
	struct	qent	*qptr;
	int	remain;
	int	next;

        disable(ps);
	if (isbadpid(pid) ||
	    ( (pptr = &proctab[pid])->pstate != PRSLEEP &&
	     pptr->pstate != PRTRECV) ) {
		restore(ps);
		
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[25] += time;

	}
		return(SYSERR);
	}
	qptr = &q[pid];
	remain = qptr->qkey;
	if ( (next=qptr->qnext) < NPROC)
		q[next].qkey += remain;
	dequeue(pid);
	if ( (next=q[clockq].qnext) < NPROC)
		sltop = (int *) & q[next].qkey;
	else
		slnempty = FALSE;
        restore(ps);
	
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[25] += time;

	}
	return(OK);
}
