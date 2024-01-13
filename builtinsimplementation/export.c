#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
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

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	end;

	end = start + len;
	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (0);
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char *get_key(char *line)
{
	int i = 0;
	char *key;

	while(line[i] && line[i] != '=')
		i++;
	key = ft_substr(line, 0, i);
	return key;
}
char *get_value(char *line)
{
	int i = 0;
	int tmp;
	char *value;

	while(line[i] && line[i] != '=')
		i++;
	i++;
	tmp = i;
	while(line[i])
		i++;
	value = ft_substr(line, tmp, i - tmp);
	return value;
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s2[i] || s1[i]))
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

char **create_new_env(char *value, char *var_name, char **env)
{
	int env_size;
	char **new_env;
	int i;
	char *new_var;

	env_size = 0;
	i = 0;
	while(env[env_size])
		env_size++;
	new_env = malloc((env_size + 2) * (sizeof(char *)));
	while(env[i])
	{
		new_env[i] = env[i];
		i++; 
	}
	new_var = ft_strjoin(var_name, "=");
	new_var = ft_strjoin(new_var, value);
	new_env[i++] = new_var;
	new_env[i] = NULL; 
	return new_env;
}

char **append_new_env_var_value(char *value, char *var_name, char **env)
{
	char *new_var;
	int i;

	i = 0;
	while(env[i] && ft_strncmp(var_name, env[i], ft_strlen(var_name)))
		i++;
	new_var = ft_strjoin(var_name, "=");
	new_var = ft_strjoin(new_var, value);
	free(env[i]);
	env[i] = new_var;
	return env;
}

void printfenv(char **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(env[i])
	{
		j = 0;
		printf("declare -x ");
		while(env[i][j] && env[i][j] != '=')
			printf("%c", env[i][j++]);
		printf("\"");
		while(env[i][j])
			printf("%c", env[i][j++]);
		printf("\"");
		i++;
	}
}

char **ft_export(char **env, char *variable, int flag)
{
	char *var_name;
	char *value;

	if(flag == 1)
	{
		var_name = get_key(variable);
		value = get_value(variable);
		if(getenv(var_name) == NULL)
			return create_new_env(value, var_name, env);
		else
			return append_new_env_var_value(value, var_name, env);
	}
	printfenv(env);
	return env;
}