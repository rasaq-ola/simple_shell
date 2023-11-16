#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	
	pid = fork();

	if (pid == -1)
	{
		perror("unsuccessful\n");
		return 1;
	}

	return 0;
}
