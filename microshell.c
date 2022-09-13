#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int		fd[200][2];
	char	*args1[] = {"/bin/ls", "-la", NULL};
	char	*args2[] = {"/bin/cat", NULL};
	int		child;

	pipe(fd[0]);
	child = fork();
	if (!child)
	{
		dup2(fd[0][1], 1);
		close(fd[0][0]);
		execve(args1[0], args1, env);
		exit(1);
	}

	int i = 1;
	while (i < 3)
	{
		pipe(fd[i]);
		child = fork();
		if (!child)
		{
			dup2(fd[i - 1][0], 0);
			dup2(fd[i][1], 1);
			close(fd[i - 1][1]);
			close(fd[i][0]);
			execve(args2[0], args2, env);
			exit(1);
		}
		else
		{
			close(fd[i-1][0]);
			close(fd[i][1]);
		}
		i++;
	}

	child = fork();
	if (!child)
	{
		dup2(fd[i-1][0], 0);
		//close(fd[i][1]);
		close(fd[i-1][1]);
		execve(args2[0], args2, env);
		exit(1);
	}


	/*i = 0;
	while (i < 180)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}*/
	int g = wait(0);
	close(fd[0][0]);
	close(fd[0][1]);
	int	k = 1;
	while (g != -1)
	{
		g = wait(0);
		if (g != -1)
		{
			//printf("%d, %d\n", fd[k][0], fd[k][1]);
			close(fd[k][0]);
			close(fd[k][1]);

		}
		k++;
		//printf("%d %d\n",k, g);
	}
	// close(fd[0][0]);
	// close(fd[0][1]);
	// close(fd[1][0]);
	// close(fd[1][1]);
	return (0);
}
