#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define LENBUF	10

void execute_code(unsigned char *p)
{
	int (*fn)();

	fn = p;
	fn();
	return;
}

void fuzz(int fd)
{
	unsigned char *code;
	int pid;
	int status;
	pid_t r;
	int lenbuf = LENBUF;

	code = mmap(NULL, lenbuf,
				PROT_EXEC | PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS,
				-1, 0);
	while (1) {
		read(fd, code, lenbuf);
		pid = fork();
		if (pid == -1) {
			exit(0);
		} else if (pid == 0) {
			execute_code(code);
		} else {
			r = waitpid(pid, &status, 0);
			if (r == -1) {
				kill(pid, 9);
				sleep(1);
				waitpid(pid, &status, WNOHANG);
			}
		}
	}
}

int main(void)
{
	int fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return errno;
	}

	fuzz(fd);

	return 0;
}
