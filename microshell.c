#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	int		fd[3][2];
	char	*args1[] = {"/bin/ls", "-la", NULL};
	char	*args2[] = {"/usr/bin/head", "-n1", NULL};
	int		child;

	pipe(fd[0]);
	pipe(fd[1]);
	pipe(fd[2]);
	child = fork();
	if (!child)
	{
		dup2(fd[0][1], 1);
		close(fd[0][0]);
		close(fd[0][1]);
		execve(args1[0], args1, env);
		exit(1);
	}
	child = fork();
	if (!child)
	{
		dup2(fd[1][0], fd[0][0]);
		dup2(fd[1][1], 1);
		close(fd[1][0]);
		close(fd[1][1]);
		execve(args2[0], args2, env);
		exit(1);
	}


	child = fork();
	if (!child)
	{
		dup2(fd[2][0], fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		execve(args2[0], args2, env);
		exit(1);
	}
	int g = wait(0);
	int	k = 0;
	while (g != -1)
	{
		g = wait(0);
		k++;
		printf("%d %d\n",k, g);
	}
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][0]);
	close(fd[2][1]);
	return (0);
}
