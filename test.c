#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int		fd[200][2];
	char	*args1[] = {"/bin/ls", "-la", NULL};
	char	*args2[] = {"/usr/bin/head", "-n1", NULL};
	int		child;

    int k = 0;
	pipe(fd[k]);
    printf("%d, %d\n", fd[k][0], fd[k][1]);
    //close(fd[k][0]);
    //close(fd[k][1]);
    k++;
	pipe(fd[k]);
    printf("%d, %d\n", fd[k][0], fd[k][1]);
	
	return (0);
}
