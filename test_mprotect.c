#include "types.h"
#include "user.h"
#include "syscall.h"
#include "signal.h"
//#include "defs.h"

int *p;

void handler(int signum, siginfo_t info)
{
	printf(1,"Handler called, error address is 0x%x\n", info.addr);
	printf(1,"Handler called, type is %d\n", info.type);
	//printf(1, "Handler, signum is: %d\n", signum);
	if(info.type == PROT_READ)
	{
		printf(1,"ERROR: Writing to a page with insufficient permission.\n");
		printf(1, "status: %d\n",mprotect((void *) info.addr, sizeof(int), PROT_READ | PROT_WRITE));
	}
	else
	{
		//printf(1, "Signum is: %d\n", signum);
		printf(1, "ERROR: Didn't get proper exception, this should not happen.\n");
		exit();
	}
	//printf(1,"Exiting handler\n");
}

int main(void)
{
	int status = 0;
	signal(SIGSEGV, handler);
 	p = (int *)sbrk(1);
	//printf(1, "line: %d\n", __LINE__);
 	status = mprotect((void *)p, sizeof(int), PROT_READ);
 	//printf(1,"line: %d status: %d\n", __LINE__, status);
	*p=100;
	//printf(1, "line: %d\n", __LINE__);
 	printf(1, "COMPLETED: value is %d, expecting 100!\n (status: %d)\n", *p, status);
 	
 	exit();
}
