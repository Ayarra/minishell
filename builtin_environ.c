/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_environ.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:40:14 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/01 20:33:02 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env(t_minishell *env)
{
	while (env)
	{
		ft_putstr(env->var);
		ft_putchar('=');
		ft_putendl(env->data);
		env = env->next;
	}
}

int			setenv_error(char *str)
{
	if (!mini_alnum(str))
	{
		ft_putendl("Variable name must contain alphanumeric characters.");
		return (1);
	}
	return (0);
}

int			len_arg_setenv(t_minishell *env, char **arg)
{
	int l;

	l = 1;
	while (arg[l])
		l++;
	if (l == 1)
		builtin_env(env);
	if (l > 3)
		ft_putendl("setenv: Too many arguments.");
	return (l);
}

void		builtin_setenv(t_minishell **env, char **av)
{
	int		len;
	char	*tmp;
	char	*tmp1;

	len = len_arg_setenv(*env, av);
	if (len <= 3 && len > 1)
	{
		if (setenv_error(av[1]))
			return ;
		tmp1 = ft_strjoin(av[1], "=");
		tmp = tmp1;
		if (av[2])
		{
			tmp = ft_strjoin(tmp, av[2]);
			len = -1;
		}
		if (search_env(&env[0], tmp) == 0)
			listadd(env, tmp);
		ft_memdel((void **)&tmp1);
		if (len == -1)
			ft_memdel((void **)&tmp);
	}
}

void		builtin_unsetenv(t_minishell **env, char **var)
{
	int i;

	if (!var[1])
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		i = 1;
		while (var[i])
		{
			delete_var(&env[0], var[i]);
			i++;
		}
	}
}
