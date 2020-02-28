/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:58:01 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/01 20:58:27 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strndup(const char *s1, int l)
{
	char *str;

	if (!(str = (char *)malloc(l + 1 * sizeof(char))))
		return (0);
	ft_bzero(str, l + 1);
	str = ft_memcpy(str, s1, l);
	return (str);
}

int			quotes_counter(char *s)
{
	int q_nb;
	int i;

	i = 0;
	q_nb = 0;
	while (s[i])
	{
		if (s[i] == '"')
			q_nb++;
		i++;
	}
	return (q_nb);
}

int			quotes(char *av, int *i)
{
	int l;

	l = 0;
	(*i)++;
	while (av[*i] && (av[*i] != '"' && av[*i] != '\''))
	{
		l++;
		(*i)++;
	}
	return (l + 2);
}

char		*quotes_trim(char *s)
{
	char	*trim;
	int		q_nb;
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	q_nb = quotes_counter(s);
	i = ft_strlen(s);
	trim = (char *)malloc(sizeof(char) * (i - q_nb + 1));
	while (j < i - q_nb)
	{
		if (s[k] != '"')
		{
			trim[j] = s[k];
			k++;
			j++;
		}
		else
			k++;
	}
	trim[j] = '\0';
	return (trim);
}
