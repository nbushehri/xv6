#ifndef XV6_SIGNAL
#define XV6_SIGNAL

#define SIGKILL	0
#define SIGFPE	1
#define SIGSEGV 2

#define PROT_READ 0
#define PROT_WRITE 1
//#define PROT_NONE 2

typedef struct {
   uint addr;
   uint type;
}siginfo_t;

typedef void (*sighandler_t)(int, siginfo_t);

#endif
