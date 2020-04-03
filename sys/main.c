/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
//#include <lab0.h>
#include "printsegaddress.c"
#include "printtos.c"
#include "printprocstks.c"
#include "printsyscallsummary.c"

int prX;
void halt();
/*
------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
*/
prch(c)
char c;
{
	int i;
	sleep(5);
}
//prch(){};

int main()
{
	kprintf("\n\nHello World, Xinu lives\n\n");

	kprintf("zfunction: 0x%08x\n",zfunction(0xaabbccdd));

	printsegaddress();

	printtos();

	printprocstks(10);


	syscallsummary_start();
	printf("\nStart call completed\n");
	resume(prX = create(prch,2000,20,"proc X",1,'A'));
	printf("\nProcess started success\n");
	sleep(2);
	sleep10(1);
	syscallsummary_stop();
	printsyscallsummary();
	return 0;
}
