/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:09:39 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/05 01:14:48 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_jooj(char *str1, char *str2)
{
	ft_memdel((void **)&str1);
	ft_memdel((void **)&str2);
}

void	unkow_tilde(char *str)
{
	ft_putstr("Unknown user: ");
	ft_putstr(str);
	ft_putstr(".\n");
}

char	*unique_tilde(char **str, t_minishell *env)
{
	(*str)++;
	return (ft_strdup(var_val(env, "HOME")));
}

char	*tilde_dollar(char **str, t_minishell *env, char *tmp)
{
	int		error;
	char	*tld;
	char	*tmp2;

	error = 0;
	if ((tld = dollar_sign(str, env, &error)))
	{
		if (tld[0] != '/')
		{
			unkow_tilde(tld);
			free_jooj(tmp, tld);
			return (0);
		}
		else
		{
			tmp2 = ft_strjoin(tmp, tld);
			free_jooj(tmp, tld);
			return (tmp2);
		}
	}
	else
	{
		free_jooj(tmp, tld);
		return (0);
	}
}

char	*tilde_cases(char **str, char *tmp, t_minishell *env)
{
	char *tld;

	if (ft_strequ(*str, "$"))
	{
		unkow_tilde(*str);
		ft_memdel((void **)&tmp);
		return (0);
	}
	else if (**str == '$')
	{
		if ((tld = tilde_dollar(str, env, tmp)))
			return (tld);
		else
			return (0);
	}
	else if (**str != '/')
	{
		unkow_tilde(*str);
		ft_memdel((void **)&tmp);
		return (0);
	}
	else
		return (tmp);
}
