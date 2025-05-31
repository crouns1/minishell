/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin_sbin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:43:33 by jait-chd          #+#    #+#             */
/*   Updated: 2025/05/31 09:23:33 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

void	execute_cmd(char *cmd, char *env[])
{
	char	**cmdd;
	char	**paths;
	char	*path;

	int pid = fork();
	int i;
	i = 0;

	if(pid == 0) 
		{
	cmdd = ft_split(cmd, ' ');
	paths = cut_paths(env);
	while (paths[i])
	{
		path = jo_in(paths[i], '/', cmdd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			if (execve(path, cmdd, NULL) == -1)
				perror("ERROR in execve func");
			 exit(EXIT_FAILURE);
		}
		i++;
	}
	exit(0);
	}
}
void piping(char *cmd1, char **env) {
	char **cmds = ft_split(cmd1, '|');
	if (!cmds || !cmds[0] || !cmds[1]) {
		execute_cmd(cmd1, env); 
		return;
	}

	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return;
	}
	pid_t pid1 = fork();
	if (pid1 == 0) 
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execute_cmd(cmds[0], env);
		exit(1);
	}

	pid_t pid2 = fork();
	if (pid2 == 0) 
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execute_cmd(cmds[1], env);
		exit(1);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
