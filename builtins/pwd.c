/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:06 by smatschu          #+#    #+#             */
/*   Updated: 2024/04/10 14:53:57 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

int main()
{
    while(1)
	{
		char *input = readline("minishell_test$ ");
		
		// Prepare arguments for execve
		// pwd
		char *args[] = { NULL };  // pwd doesn't require imput, will use NULL
		char *env[] = { NULL };  // Use the current environment
		
		// Fork a child process
		pid_t pid = fork();
		
		if (pid == -1)
		{
			perror("fork");
			free(input);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process executes the pwd command
			if (execve("/bin/pwd", args, env) == -1)
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
		
		// Free the input allocated by readline
		free(input);
	}	
    return 0;
}
