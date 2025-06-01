#include "../minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/06/01 15:57:04 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_TOKEN 1000

#define WORD 'W'
#define PIPE '|'
#define RED_IN '>'
#define RED_OUT '<'

#define HEREDOC 'H'
#define APPEND 'A'

#define S_QUOTE '\''
#define D_QUOTE '\"'

typedef struct s_args
{
	char *value;
	char type;
} t_args;


char *sub_dup(const char *line , int len) {
	len = strlen(line);
	char *res = malloc(len + 1); 
	int i = 0;
	if (!res)
		return NULL;
	while( i < len) {
		res[i] = line[i];
		i++;
	}
	res[len] = '\0';
	return res;
}

// void token_each_arg(char *line , t_args *token , int *count) {
// 	int  i = 0;
	
// }

char *extract_line(char *line, t_args *token, int *count) {
	int i = 0;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return NULL;

	char *start = line;
	while (*line && *line != ' ' && *line != '\t')
		line++;

	int len = line - start;
		token[*count].value = sub_dup(start, len); 
		token[*count].type = 'W'; 
	// token_each_arg(line , &count , token);
	(*count)++;
	return line;
}

int tokenize(char *line, t_args *tokens) {
	int count = 0;
	while (*line) {
		line = extract_line(line, tokens, &count);
	}
	return count;
}

void print_tokens(t_args *tokens, int len) {
	int i = 0;
	while(i  < len) {
		printf("Token N [[%d]] , Value > %s , Type %c\n", i , tokens->value, tokens->type);
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	t_args *tokens = malloc(sizeof(t_args) * MAX_TOKEN);

	if (argc != 1) {
		write(2, "No such file or directory\n", 27);
		exit(127);
	}
	
	char *line;
	int len;
	while (1) {
		line = readline("crounshell:~$ ");
		// execute_cmd(line , env);
		usleep(999);
		add_history(line);
		len = tokenize(line, tokens);
		print_tokens(tokens, len);
	}
	return 0;
}
