/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:39:29 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/05 16:54:12 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*unique_dollar(char **str)
{
	(*str)++;
	return (ft_strdup("$"));
}

int			dollar_counter(char **str)
{
	int l;

	l = 0;
	while (**str && **str != '$' && ft_isalnum(**str) && **str != '_')
	{
		(*str)++;
		l++;
	}
	return (l);
}

char		*dollar_etc(char *tmp, char *head, int *error)
{
	if (tmp)
	{
		head = ft_strdup(tmp);
		return (head);
	}
	else
	{
		ft_putstr(head);
		ft_putendl(": Undefined variable.");
		*error = 1;
		return (0);
	}
}

char		*exp_dollar(t_minishell *env, char *result, char *holder)
{
	char	*tmp;
	char	*tmp2;
	int		error;

	error = 0;
	while ((tmp = dollar_sign(&holder, env, &error)))
	{
		tmp2 = ft_strdup(result);
		ft_memdel((void **)&result);
		result = ft_strjoin(tmp2, tmp);
		free_jooj(tmp, tmp2);
		tmp = characters(&holder);
		tmp2 = ft_strdup(result);
		ft_memdel((void **)&result);
		result = ft_strjoin(tmp2, tmp);
		free_jooj(tmp, tmp2);
	}
	ft_memdel((void **)&tmp);
	if (error)
	{
		if (result)
			ft_memdel((void **)&result);
		return (0);
	}
	return (result);
}

char		*exp_chyata(char **holder, t_minishell *env)
{
	char *tmp;
	char *tmp2;
	char *result;

	result = NULL;
	if (**holder && **holder == '~')
	{
		if (!(result = tilde(holder, env)))
			return (0);
	}
	if (result)
	{
		tmp = characters(holder);
		tmp2 = ft_strdup(result);
		ft_memdel((void **)&result);
		result = ft_strjoin(tmp2, tmp);
		free_jooj(tmp, tmp2);
	}
	else
		result = characters(holder);
	return (result);
}
