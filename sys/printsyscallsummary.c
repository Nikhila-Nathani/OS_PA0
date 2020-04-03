#include<stdio.h>
#include<proc.h>

extern int syscall_flag;
void syscallsummary_start(){
	syscall_flag = 1;
	printf("Setting syscall\n");
	int i,j;
    // setting each counter and time_spent variables to zero, while starting
    for(i=0; i < NPROC; i++){

        struct pentry *proc = &proctab[i];

        for(j=0; j < 27; j++){

            proc->time_spent_syscall[j]=0;
			proc->counter_for_syscall[j]=0;
        }
    }

}

void syscallsummary_stop(){
	syscall_flag = 0;
}

char* getSysCallName(int i){

	switch(i){

		case 0:
		    return "sys_freemem";
            break;

		case 1:
		    return "sys_chprio";
            break;

		case 2:
		    return "sys_getpid";
            break;

		case 3:
		    return "sys_getprio";
            break;

		case 4:
		    return "sys_gettime";
			break;

		case 5:
		    return "sys_kill";
            break;

		case 6:
		    return "sys_receive";
            break;

		case 7:
            return "sys_recvclr";
            break;

		case 8:
		    return "sys_recvtim";
            break;

		case 9:
		    return "sys_resume";
            break;

		case 10:
		    return "sys_scount";
            break;

		case 11:
		    return "sys_sdelete";
            break;

		case 12:
		    return "sys_send";
            break;

		case 13:
		    return "sys_setdev";
            break;

		case 14:
		    return "sys_setnok";
            break;

		case 15:
		    return "sys_screate";
            break;

		case 16:
		    return "sys_signal";
            break;

		case 17:
		    return "sys_signaln";
            break;

		case 18:
		    return "sys_sleep";
            break;

		case 19:
		    return "sys_sleep10";
            break;

		case 20:
		    return "sys_sleep100";
            break;

		case 21:
		    return "sys_sleep1000";
            break;

		case 22:
		    return "sys_sreset";
            break;

		case 23:
		    return "sys_stacktrace";
            break;

		case 24:
		    return "sys_suspend";
            break;

		case 25:
		    return "sys_unsleep";
            break;

		case 26:
		    return "sys_wait";
            break;
	}
}


void printsyscallsummary(){
	kprintf("\nvoid printsyscallsummary()");
	int i,j;
	for(i=0; i < NPROC; i++){
        struct pentry *proc = &proctab[i];
        int flag=1;
        for(j=0; j < 27; j++){
            if(proc->counter_for_syscall[j]>0){
                if(flag==1){
					flag = 0;
                    kprintf("\nProcess [pid:%d]",i);
				}
                int aet=(proc->time_spent_syscall[j])/(proc->counter_for_syscall[j]);
                kprintf("\n\tSyscall: %s, count: %d, average execution time: %d (ms)",getSysCallName(j),proc->counter_for_syscall[j],aet);
            }
        }
	}

}

