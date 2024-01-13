#include <unistd.h>
#include <stdio.h>

void ft_cd(char *directory)
{
	if (!directory)
		return ;
	if (chdir(directory) != 0)
		printf("bash: cd: %s: No such file or directory", directory);
}
