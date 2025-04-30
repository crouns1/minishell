/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:43:49 by jait-chd          #+#    #+#             */
/*   Updated: 2025/04/30 21:43:51 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include<readline/history.h>
#include <fcntl.h>
#include <errno.h>

char	**ft_split(char const *s, char c);
void	execute_cmd(char *cmd, char *env[]);
size_t	ft_strlen(const char *s);
void	ft_freee(char **str);
char	*ft_strdup(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void builtin_env(char **env);
void built_in_exit(void) ;

#endif