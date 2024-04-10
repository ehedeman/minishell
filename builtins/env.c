/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:10 by smatschu          #+#    #+#             */
/*   Updated: 2024/04/10 16:18:15 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>

int main()
{
	//have to use this extern var to get the env info
	extern char **environ;

	while(1)
	{
		char *input = readline("minishell_test$ ");
		char *args[] = { "env", NULL };
		pid_t pid = fork();
		
		if (pid == -1)
		{
			perror("fork");
			free(input);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process executes the env command
			if (execve("/usr/bin/env", args, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// Parent process waits for the child to complete
			int status;				
			waitpid(pid, &status, 0);
		}
		free(input);
		}
	return 0;
}