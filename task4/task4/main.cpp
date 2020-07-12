#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
int main() {

	pid_t pid1 = fork();
	if (pid1 == 0)
	{
		printf("child1: B");
		return 0;
	}
	pid_t pid2 = fork();
	if (pid2 == 0)
	{
		printf("child2: C");
		return 0;
	}
	if (pid1 > 0 || pid2 > 0)
	{
		printf("father: A");
	}
}
