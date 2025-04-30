/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:43:29 by jait-chd          #+#    #+#             */
/*   Updated: 2025/04/30 21:43:30 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_env(char **env) {
	int i = 0;
	while(env[i]) {
		printf("%s\n" , env[i]);
		i++;
	}
}

void built_in_exit(void) 
{
	printf("exit\n");
	exit(0);
}