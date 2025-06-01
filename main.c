/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/06/01 17:21:12 by jait-chd         ###   ########.fr       */
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

char *sub_dup(const char *line, int len) {
    char *res = malloc(len + 1);
    if (!res)
        return NULL;
    for (int i = 0; i < len; i++) {
        res[i] = line[i];
    }
    res[len] = '\0';
    return res;
}

char *extract_token(char *line, t_args *token, int *count) {
    while (*line == ' ' || *line == '\t') 
        line++;

    if (*line == '\0') 
        return NULL;
	char symbol;
    char *start = line;
    if (*line == PIPE) {
        token[*count].value = sub_dup(line, 1);
        token[*count].type = PIPE;
        (*count)++;
        return line + 1;
    }
    if (*line == RED_OUT) {
        token[*count].value = sub_dup(line, 1);
        token[*count].type = RED_OUT;
        (*count)++;
        return line + 1;
    }
    if (*line == RED_IN) {
        token[*count].value = sub_dup(line, 1);
        token[*count].type = RED_IN;
        (*count)++;
        return line + 1;
    }

    while (*line && *line != ' ' && *line != '\t' && *line != '|' && *line != '>' && *line != '<') {
        line++;
    }

    int len = line - start;
    token[*count].value = sub_dup(start, len);
    token[*count].type = WORD;
    (*count)++;

    return line;
}

int tokenize(char *line, t_args *tokens) {
    int count = 0;
    while (*line) {
        line = extract_token(line, tokens, &count);
        if (!line)
            break;
    }
    return count;
}

void print_tokens(t_args *tokens, int len) {
    int i = 0;
	while ( i < len) {
        printf("Token %d: Value = '%s', Type = '%c'\n", i, tokens[i].value, tokens[i].type);
		i++;
	}
}

void check_for_type(char *line , t_args *tokens) {
	int i  = 0;
	int token_count = 0;
	while(*line == ' ' || *line == '\t')
		i++;
	while(*line != ' ' && *line != '\t') {
		i++;	
		token_count++;
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
		if(!line)
		break;
		check_for_type(line , tokens);
		//len = tokenize(line, tokens);
		piping(line , env);
        usleep(999);
		continue;
        //print_tokens(tokens, len);
        add_history(line);
    }

    return 0;
}
