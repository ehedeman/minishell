/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:37:36 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/08 16:16:02 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_size(t_env_list *lst)
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

static char	**assign_link_pointer(t_env_list *env, char **envp)
{
	int		size;
	char	*temp;
	int		i;

	i = 0;
	size = find_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		if (env->value)
			envp[i] = ft_strjoin(temp, env->value);
		else
			envp[i] = ft_strjoin(temp, "\0");
		free(temp);
		env = env->next;
		i++;
	}
	envp[i++] = NULL;
	return (envp);
}

static t_exec	*allocate_exec(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec) * 1);
	if (!new)
		return (NULL);
	new->envp = NULL;
	new->args = NULL;
	new->current = NULL;
	return (new);
}

/* g_sig tells program that theres a file being executed.*/
int	exec_command(t_statement *temp, t_mini *mini, int i)
{
	t_exec	*exec;

	exec = allocate_exec();
	if (!exec)
		return (-1);
	mini->pid = 0;
	g_sig = 1;
	signal(SIGQUIT, handler);
	exec->envp = assign_link_pointer(mini->env, exec->envp);
	exec->args = malloc(sizeof(char *) * (temp->argc + 1));
	exec->current = temp;
	exec->args[0] = ft_strjoin("/bin/", temp->argv[i]);
	if (exec_com_fork(exec, mini, i) == -1)
		return (-1);
	free_env_args(exec->envp, exec->args, 1);
	free(exec);
	g_sig = 0;
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	exec_file(t_statement *temp, t_mini *mini, int i)
{
	t_exec	*exec;

	exec = allocate_exec();
	if (!exec)
		return (-1);
	mini->pid = 0;
	g_sig = 1;
	if (ft_strcmp(temp->argv[i], "./minishell"))
		signal(SIGQUIT, handler);
	exec->envp = assign_link_pointer(mini->env, exec->envp);
	exec->current = temp;
	exec->args = malloc(sizeof(char *) * (temp->argc + 1));
	if (exec_file_fork(exec, mini, i) == -1)
		return (-1);
	free_env_args(exec->envp, exec->args, 0);
	free(exec);
	g_sig = 0;
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
