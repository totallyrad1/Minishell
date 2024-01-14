#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	cpy = (char *)malloc((i + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	while (j < i)
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstring;
	int		i;
	int		j;
	int		s1len;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (free(s1), ft_strdup(s2));
	s1len = ft_strlen(s1);
	newstring = (char *)malloc((s1len + ft_strlen(s2) + 1) * sizeof(char));
	if (newstring == NULL)
		return (free(s1), NULL);
	while (s1[i])
	{
		newstring[i] = s1[i];
		i++;
	}
	while (s2[j])
		newstring[i++] = s2[j++];
	newstring[i] = '\0';
	return (free(s1), newstring);
}

void	ft_echo(char *string, int flag)
{
	int i = 0;
	if (!string)
		return ;
	if (flag == 0)
		string = ft_strjoin(string, "\n");
	printf("%s", string + i);
}