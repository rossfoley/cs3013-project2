#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define __NR_cs3013_syscall2 350

struct processinfo {
    long state; // Done
    pid_t pid; // Done
    pid_t parent_pid;
    pid_t youngest_child;
    pid_t younger_sibling;
    pid_t older_sibling;
    uid_t uid; // Done
    long long start_time; // Done
    long long user_time; // Done
    long long sys_time; // Done
    long long cutime;
    long long cstime;
}; //struct processinfo

long testCall2 (struct processinfo *info) {
	return (long) syscall(__NR_cs3013_syscall2, info);
}

int main () {
	struct processinfo *info = malloc(sizeof(struct processinfo));
	printf("The result of cs3013_syscall2 is: %ld\n", testCall2(info));
	printf("State: %li\n", info->state);
	printf("PID: %i\n", (int) info->pid);
	printf("UID: %i\n", (int) info->uid);
	printf("Start Time: %lli nanoseconds\n", info->start_time);
	printf("User Time: %lli microseconds\n", info->user_time);
	printf("System Time: %lli microseconds\n", info->sys_time);
	free(info);
	return 0;
}