#include <sys/syscall.h>
#include <stdio.h>

#define __NR_cs3013_syscall1 349


long testCall1 ( void) {
	return (long) syscall(__NR_cs3013_syscall1);
}

int main () {
	printf("The result of cs3013_syscall1 is: %ld\n", testCall1());
	return 0;
}
