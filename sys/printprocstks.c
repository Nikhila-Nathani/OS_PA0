#include<stdio.h>
#include<proc.h>

long *esp;

void printprocstks(int priority){

    int i;
    kprintf("\nvoid printprocstks(int priority)");
    asm("movl %esp,esp");

    for(i=0; i < NPROC; i++){
        struct pentry *proc = &proctab[i];
        if(proc->pprio > priority){
            kprintf("\nProcess [%s]\n",proc->pname);
            kprintf("\tpid: %d\n",i);
            kprintf("\tpriority: %d\n",proc->pprio);
            kprintf("\tbase: 0x%08x\n",proc->pbase);
            kprintf("\tlimit: 0x%08x\n",proc->plimit);
            kprintf("\tlen: %d\n",proc->pstklen);

            if(i == getpid()){
				kprintf("\tpointer: 0x %08x\n",esp);
			}
			else{
                kprintf("\tpointer: 0x %08x\n",proc->pesp);
			}
        }
    }

}
