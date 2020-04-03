/* screate.c - screate, newsem */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>

LOCAL int newsem();

/*------------------------------------------------------------------------
 * screate  --  create and initialize a semaphore, returning its id
 *------------------------------------------------------------------------
 */
SYSCALL screate(int count)
{
	STATWORD ps;    
	
	extern long ctr1000;
	long tStart;
	if(syscall_flag==1){
		tStart = ctr1000;
		struct pentry *proc = &proctab[getpid()];
		proc->counter_for_syscall[15] ++;
	}
	int	sem;

	disable(ps);
	if ( count<0 || (sem=newsem())==SYSERR ) {
		restore(ps);
		
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[15] += time;

	}
		return(SYSERR);
	}
	semaph[sem].semcnt = count;
	/* sqhead and sqtail were initialized at system startup */
	restore(ps);
	
    if(syscall_flag==1){
		struct pentry *proc = &proctab[getpid()];
		int time = ctr1000 - tStart;
		proc->time_spent_syscall[15] += time;

	}
	return(sem);
}

/*------------------------------------------------------------------------
 * newsem  --  allocate an unused semaphore and return its index
 *------------------------------------------------------------------------
 */
LOCAL int newsem()
{
	int	sem;
	int	i;

	for (i=0 ; i<NSEM ; i++) {
		sem=nextsem--;
		if (nextsem < 0)
			nextsem = NSEM-1;
		if (semaph[sem].sstate==SFREE) {
			semaph[sem].sstate = SUSED;
			return(sem);
		}
	}
	return(SYSERR);
}
