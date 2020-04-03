#include<stdio.h>
void printsegaddress(){

	extern int etext,edata;
	printf("void printsegaddress()\n\n");
	kprintf("Current: etext[0x%08X] = 0x%08x, edata[0x%08X] = 0x%08x, ebss[0x%08X] = 0x%08x\n",&etext, etext, &edata, edata, &end, end);
	kprintf("Preceding: etext[0x%08X] = 0x%08x, edata[0x%08X] = 0x%08x, ebss[0x%08X] = 0x%08x\n",(int)(&etext-1), (int)(*(&etext-1)), (int)(&edata-1), (int)(*(&edata-1)), (int)(&end-1), (int)(*(&end-1)));
	kprintf("After: etext[0x%08X] = 0x%08x, edata[0x%08X] = 0x%08x, ebss[0x%08X] = 0x%08x\n",(int)(&etext+1), (int)(*(&etext+1)), (int)(&edata+1), (int)(*(&edata+1)), (int)(&end+1), (int)(*(&end+1)));
}
