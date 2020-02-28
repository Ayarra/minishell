/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 03:53:56 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/07 18:58:33 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_exp(t_parse *args, t_minishell *init)
{
	if (!expansions(args->command, init))
	{
		if (args->command)
			free_tab(args->command);
		if (args->options)
			free_tab(args->options);
		ft_memdel((void **)&args);
		return (0);
	}
	if (!expansions(args->options, init))
	{
		if (args->command)
			free_tab(args->command);
		if (args->options)
			free_tab(args->options);
		ft_memdel((void **)&args);
		return (0);
	}
	return (1);
}

char	*characters(char **str)
{
	char	*head;
	int		i;

	i = 0;
	head = *str;
	while (**str && **str != '$')
	{
		(*str)++;
		i++;
	}
	head = ft_strndup(head, i);
	return (head);
}

char	*dollar_sign(char **str, t_minishell *env, int *error)
{
	char	*head;
	int		l;
	char	*tmp;
	char	*tmp2;
	char	*wii;

	l = 0;
	if (ft_strequ(*str, "$"))
		return (unique_dollar(str));
	(*str)++;
	head = *str;
	l = dollar_counter(str);
	if (l)
	{
		tmp2 = ft_strndup(head, l);
		tmp = var_val(env, tmp2);
		ft_memdel((void **)&tmp2);
		if ((wii = dollar_etc(tmp, head, error)))
			return (wii);
		else
			return (0);
	}
	else
		return (0);
}

char	*tilde(char **str, t_minishell *env)
{
	char *tmp;
	char *tld;

	tmp = 0;
	if (ft_strequ(*str, "~"))
		return (unique_tilde(str, env));
	(*str)++;
	if ((tmp = ft_strdup(var_val(env, "HOME"))))
	{
		if ((tld = tilde_cases(str, tmp, env)))
			return (tld);
		else
			return (0);
	}
	else
		return ("\0");
}

int		expansions(char **args, t_minishell *env)
{
	char	*result;
	char	*holder;
	int		i;

	result = 0;
	i = 0;
	while (args[i])
	{
		holder = args[i];
		if (!(result = exp_chyata(&holder, env)))
			return (0);
		if (*holder)
		{
			if (!(result = exp_dollar(env, result, holder)))
				return (0);
		}
		ft_memdel((void **)&args[i]);
		args[i] = ft_strdup(result);
		ft_memdel((void **)&result);
		result = 0;
		i++;
	}
	return (1);
}
