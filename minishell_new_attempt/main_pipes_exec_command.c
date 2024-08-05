/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipes_exec_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:40:28 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/05 13:52:46 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	find_size_pipe(t_env_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static	char	**assign_link_pointer_pipe(t_env_list *env, char **envp)
{
	int		size;
	char	*current;
	int		i;

	i = 0;
	size = find_size_pipe(env);
	envp = malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		current = ft_strjoin(env->name, "=");
		if (env->value)
			envp[i] = ft_strjoin(current, env->value);
		else
			envp[i] = ft_strjoin(current, "\0");
		free(current);
		env = env->next;
		i++;
	}
	envp[i++] = NULL;
	return (envp);
}

static void	copy_current_pipe(t_statement *current, int i, char **args)
{
	while (i <= current->argc)
	{
		if (i == current->argc)
		{
			args[i] = NULL;
			break ;
		}
		args[i] = current->argv[i];
		i++;
	}
}

static int	free_env_args_pipe(char **envp, char **args, int arg_zero)
{
	int		i;
	char	*trimmed_cmd;

	i = 0;
	if (!ft_strncmp(args[0], "/bin/", 5))
		trimmed_cmd = ft_strdup(&args[0][5]);
	else
		trimmed_cmd = ft_strdup(args[0]);
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	if (arg_zero)
	{
		if (arg_zero == 2)
		{
			write(2, trimmed_cmd, ft_strlen(trimmed_cmd));
			write(2, ": Command not found.\n", 21);
		}
		free(args[0]);
	}
	free(trimmed_cmd);
	free(args);
	return (-1);
}

void	print_all(char **args, char **envp)
{
	int i = 0;
	while (args[i])
	{
		write(2, args[i], ft_strlen(args[i]));
		write(2, "\n", 1);
		i++;
	}
	i = 0;
	while (envp[i])
	{
		write(2, envp[i], ft_strlen(envp[i]));
		write(2, "\n", 1);
		i++;
	}
}

static	void exits_pipe(char **args, char **envp)
{
	print_all(args, envp);
	if (execve(args[0], args, envp) == -1)
	{
		free_env_args_pipe(envp, args, 2);
		if (errno == EACCES)
			exit (126);
		else if (errno == ENOENT)
			exit (127);
		else
			exit (1);
	}
	else
		exit(EXIT_SUCCESS);
}

static int	exec_com_fork_pipe(t_statement *current, char **envp, char **args, t_mini *mini)
{
	int		i;
	int		status;

	i = 1;
	copy_current_pipe(current, i, args);
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_env_args_pipe(envp, args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
		exits_pipe(args, envp);
	else
	{
		waitpid(mini->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else
			mini->exit_status = 1;
	}
	return (0);
}

int	exec_command_pipe(t_statement *current, t_mini *mini)
{
	char	**args;
	char	**envp;

	mini->pid = 0;
	g_sig = 1;
	envp = NULL;
	envp = assign_link_pointer_pipe(mini->env, envp);
	args = malloc(sizeof(char *) * (current->argc + 1));
	args[0] = ft_strjoin("/bin/", current->argv[0]);
	if (exec_com_fork_pipe(current, envp, args, mini) == -1)
		return (-1);
	free_env_args_pipe(envp, args, 1);
	g_sig = 0;
	return (0);
}

