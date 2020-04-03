#ifndef _lab0_h_
#define _lab0_h_

//#include <conf.h>
//#include <kernel.h>
//#include <proc.h>
#include <stdio.h>
//#include <printsegaddress.c>
//#include "printtos.c"
//#include "printprocstks.c"


long zfunction(long );

void printsegaddress(void);

void printtos(void);

void printprocstks(int );

void syscallsummary_start(void);
void syscallsummary_stop(void);
void printsyscallsummary(void);

#endif
