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
    pid_t parent_pid; // Done
    pid_t youngest_child; // Done
    pid_t younger_sibling;
    pid_t older_sibling;
    uid_t uid; // Done
    long long start_time; // Done
    long long user_time; // Done
    long long sys_time; // Done
    long long cutime; // Done
    long long cstime; // Done
}; // struct processinfo

long testCall2 (struct processinfo *info) {
	return (long) syscall(__NR_cs3013_syscall2, info);
}

int main () {
	struct processinfo *info = malloc(sizeof(struct processinfo));
	// Fork a child process to make sure that the youngest child PID is correct
	int pid = fork();
	if (pid != 0) {
		int status;
		printf("The result of cs3013_syscall2 is: %ld\n", testCall2(info));
		printf("State: %li\n", info->state);
		printf("PID: %i\n", (int) info->pid);
		printf("Parent PID: %i\n", (int) info->parent_pid);
		printf("Older Sibling PID: %i\n", (int) info->older_sibling);
		printf("Youngest Child PID: %i\n", (int) info->youngest_child);
		printf("UID: %i\n", (int) info->uid);
		printf("Start Time: %lli nanoseconds\n", info->start_time);
		printf("User Time: %lli microseconds\n", info->user_time);
		printf("System Time: %lli microseconds\n", info->sys_time);
		printf("User Time of Children: %lli microseconds\n", info->cutime);
		printf("System Time of Children: %lli microseconds\n", info->cstime);
		waitpid(pid, &status, 0);
	}
	
	free(info);
	return 0;
}