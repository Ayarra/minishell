/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:29:01 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/07 19:00:13 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_ppid = 0;

void	nothing(int n)
{
	n = 0;
	if (!g_ppid)
		write(1, "\n$>", 3);
	else
		write(1, "\n", 1);
}

int		search_dollar(char *command, t_minishell *env, char *tmp)
{
	if (*command == '$')
	{
		tmp = command;
		tmp++;
		if (!(command = (var_val(env, tmp))))
			return (0);
	}
	return (1);
}

void	exec_fun_error(char *str)
{
	ft_putstr(str);
	ft_putendl(": Command not found.");
}

void	exec_funs(t_minishell *init, t_parse *args)
{
	char	**command;
	char	*exec;
	char	**envr;
	int		pid;

	g_ppid = 1;
	command = ft_strsplit(var_val(init, "PATH"), ':');
	envr = get_env(init);
	if ((exec = search_command(args->command[0], command, init)))
	{
		if ((pid = fork()) > 0)
			wait(0);
		else
		{
			*args->options = args->command[0];
			if (execve(exec, args->options, envr) == -1)
				exit(0);
		}
		ft_memdel((void **)&exec);
	}
	else
		exec_fun_error(args->command[0]);
	free_tab(envr);
	free_tab(command);
}

void	builtin_funs(t_parse *args, t_minishell **init, char **av)
{
	g_ppid = 0;
	if (ft_strequ(args->command[0], "env"))
		builtin_env(init[0]);
	else if (ft_strequ(args->command[0], "setenv"))
		builtin_setenv(&init[0], args->options);
	else if (ft_strequ(args->command[0], "unsetenv"))
		builtin_unsetenv(&init[0], args->options);
	else if (ft_strequ(args->command[0], "cd"))
		builtin_cd(&init[0], args->options);
	else if (ft_strequ(args->command[0], "echo"))
		builtin_echo(args->options);
	else if (ft_strequ(args->command[0], "exit"))
	{
		free_list(init[0]);
		if (args->command)
			free_tab(args->command);
		if (args->options)
			free_tab(args->options);
		ft_memdel((void **)&args);
		free_tab(av);
		exit(1);
	}
	else
		exec_funs(init[0], args);
}
