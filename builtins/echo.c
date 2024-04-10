/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:45:52 by smatschu          #+#    #+#             */
/*   Updated: 2024/04/10 15:24:08 by smatschu         ###   ########.fr       */
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
		
		//echo
		//char *args[] = {"/bin/echo", input, NULL };  // echo command will echo the user's input
		
		//echo - n (echo without the new line)
		char *args[] = {"/bin/echo", "-n", input, NULL };  // should parse in such a way that it considers the option -n
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
			if (execve("/bin/echo", args, env) == -1)
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
