/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:37:36 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/24 17:57:11 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	find_size(t_env_list *lst)
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

static	char	**assign_link_pointer(t_env_list *env, char **envp)
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
		envp[i] = ft_strjoin(temp, env->value);
		free(temp);
		env = env->next;
		i++;
	}
	envp[i++] = NULL;
	return (envp);
}

//g_exec_file tells program that theres a file being executed
int	exec_command(t_statement *temp, t_mini *mini)
{
	char	**args;
	char	**envp;

	mini->pid = 0;
	g_exec_file = 1;
	envp = NULL;
	envp = assign_link_pointer(mini->env, envp);
	args = malloc(sizeof(char *) * (temp->argc + 1));
	args[0] = ft_strjoin("/bin/", temp->argv[0]);
	if (exec_com_fork(temp, envp, args, mini) == -1)
		return (-1);
	free_env_args(envp, args, 1);
	g_exec_file = 0;
	return (0);
}

int	exec_file(t_statement *temp, t_mini *mini)
{
	char	**args;
	char	**envp;

	mini->pid = 0;
	g_exec_file = 1;
	envp = NULL;
	envp = assign_link_pointer(mini->env, envp);
	args = malloc(sizeof(char *) * (temp->argc + 1));
	if (exec_file_fork(temp, envp, args, mini) == -1)
		return (-1);
	free_env_args(envp, args, 0);
	g_exec_file = 0;
	return (0);
}
