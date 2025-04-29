/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/04/29 18:10:04 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include<readline/history.h>
#include <fcntl.h>
#include <errno.h>



static void	ft_freee(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = (char *)malloc(ft_strlen(s) + 1);
	if (!cpy)
		return (NULL);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}


static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	if (start >= s_len)
		return (ft_strdup(""));
	if (len < s_len - start)
		str = (char *)malloc((len + 1) * sizeof(char));
	else
		str = (char *)malloc((s_len - start + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}


static size_t	ft_counting(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	ft_start_end(const char *s, size_t *i, size_t *j, char c)
{
	*j = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	while (s[*i + *j] && s[*i + *j] != c)
		(*j)++;
}

static char	**ft_free(char **r, size_t l)
{
	while (l > 0)
	{
		l--;
		free(r[l]);
	}
	free(r);
	return (0);
}

static char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	count;
	char	**r;

	if (s == 0)
		return (0);
	i = 0;
	l = 0;
	count = ft_counting(s, c);
	r = (char **)malloc((count + 1) * sizeof(char *));
	if (r == NULL)
		return (NULL);
	while (l < count)
	{
		ft_start_end(s, &i, &j, c);
		r[l] = ft_substr(s, i, j);
		if (r[l] == 0)
			return (ft_free(r, l));
		i = i + j;
		l++;
	}
	r[count] = 0;
	return (r);
}

static void builtin_env(char **env) {
	int i = 0;
	while(env[i]) {
		printf("%s\n" , env[i]);
		i++;
	}
}

static char	*jo_in(char const *s1, char slash, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = slash;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

static char	**cut_paths(char *envp[])
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static void	execute_cmd(char *cmd, char *env[])
{
	char	**cmdd;
	char	**paths;
	char	*path;

	int (i), (ernoaccess), (flag);
	i = 0;
	flag = 0;
       	ernoaccess = 1;
	(cmdd = ft_split(cmd, ' '), paths = cut_paths(env));
	while (paths[i])
	{
		path = jo_in(paths[i], '/', cmdd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			if (execve(path, cmdd, NULL) == -1)
				perror("ERROR in execve func");
			exit(EXIT_FAILURE);
		}

		if(flag == 0 && errno != 2)
			(ernoaccess = errno, flag = 1);
		(free(path), i++);
	}
	(perror(cmdd[0]), ft_freee(cmdd), ft_freee(paths));
	if(ernoaccess == 13)
		exit(126);
	else
		exit(127);
}

void pars_args(int counter , char **vectors , char  **env) 
{

	char **args = ft_split()
}


int main(int counter , char **vectors , char **env)
{
    (void)vectors;
    int i = 0;
    if(counter != 1)
        (write(2,"No such file or directory\n",27)) , (exit(127));
    
    char *readline1;
	char *readline2;
      char* cwd;	
    char buff[1];
	cwd = getcwd( buff, 1 );
	while(1)  { 
      	readline1 = readline("crounshell:~$ ");	
		if(strcmp(readline1 , "exit") == 0) 	
			exit(0);
		if(strcmp(readline1, "env") == 0)	
			builtin_env(env);
		}
		add_history(readline1);
		return (0);
}

