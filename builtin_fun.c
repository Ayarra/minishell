/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 03:54:05 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/07 22:32:19 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		mini_alnum(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int		search_env(t_minishell **env, char *info)
{
	char		**tmp;
	t_minishell	*old;

	old = env[0];
	if ((tmp = ft_strsplit(info, '=')) == NULL)
		return (-1);
	while (env[0])
	{
		if (ft_strequ(env[0]->var, tmp[0]))
		{
			ft_memdel((void **)&env[0]->data);
			env[0]->data = ft_strdup(tmp[1]);
			free_tab(tmp);
			env[0] = old;
			return (1);
		}
		env[0] = env[0]->next;
	}
	free_tab(tmp);
	env[0] = old;
	return (0);
}

void	delete_var(t_minishell **env, char *var)
{
	t_minishell *head;
	t_minishell *last;

	head = *env;
	if (head != NULL && ft_strequ(head->var, var))
	{
		*env = head->next;
		ft_memdel((void **)&(head->var));
		ft_memdel((void **)&(head->data));
		ft_memdel((void **)&head);
		return ;
	}
	while (head != NULL && !ft_strequ(head->var, var))
	{
		last = head;
		head = head->next;
	}
	if (head == NULL)
		return ;
	last->next = head->next;
	ft_memdel((void **)&(head->var));
	ft_memdel((void **)&(head->data));
	ft_memdel((void **)&head);
}

char	*var_val(t_minishell *env, char *var)
{
	while (env)
	{
		if (ft_strequ(env->var, var))
		{
			if (env->data)
			{
				return (env->data);
			}
			else
				return ("\0");
		}
		env = env->next;
	}
	return (NULL);
}

void	builtin_echo(char **var)
{
	int length;
	int i;

	i = 1;
	length = 0;
	while (var[length])
		length++;
	if (length == 1)
		ft_putchar('\n');
	else
	{
		while (var[i])
		{
			ft_putstr(var[i]);
			i++;
			if (var[i])
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
