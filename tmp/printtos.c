#include<stdio.h>

long *esp,*ebp;

void printtos(){

    asm("movl %esp,esp");
    asm("movl %ebp,ebp");
	int i;
	kprintf("\nvoid printtos()\n");
	kprintf("Before[0x%08x]: 0x%08x\n",ebp+2,*(ebp+2));
	kprintf("After[0x%08x]: 0x%08x\n",ebp,*ebp);
	//kprintf("Afteresp[0x%08X]: 0x%08x\n",esp,*esp);
	for(i=1; i<=4; i++){
		kprintf("\telement[0x%08x]: 0x%08x\n",(esp+i),(*(esp+i)));
	}
//    long *j;
//	for(j=esp; j<esp+4; j++){
//		kprintf("\telement[0x%08x]: 0x%08x\n",j,*(j));
//	}
}
