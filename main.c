/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:09:15 by jait-chd          #+#    #+#             */
/*   Updated: 2025/04/30 21:50:20 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int counter , char **vectors , char **env)
{
    (void)vectors;
    int i = 0;
    if(counter != 1)
        (write(2,"No such file or directory\n",27)) , (exit(127));
    
    char *readline1;
	while(1)  
	{ 
		readline1 = readline("crounshell:~$ ");	
		execute_cmd(readline1 , env);
		usleep(1000);
		if(strcmp(readline1 , "exit") == 0) 	
			built_in_exit();
		if(strcmp(readline1, "env") == 0)	
			builtin_env(env);
		add_history(readline1);
		}
		return (0);
}
