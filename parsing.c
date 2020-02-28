/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 03:54:19 by hhamdaou          #+#    #+#             */
/*   Updated: 2019/12/07 19:00:36 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_command(char *str, int *i)
{
	char	*head;
	char	*command;
	int		l;

	l = 0;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	head = &str[*i];
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			l += quotes(str, i);
		}
		else
		{
			l++;
		}
		(*i)++;
	}
	command = ft_strndup(head, l);
	head = command;
	command = quotes_trim(head);
	ft_memdel((void **)&head);
	return (command);
}

int			parsing_hmmm(char *av, int j)
{
	int l;

	l = 0;
	while (av[j] && av[j] != ' ')
	{
		if (av[j] == '"' || av[j] == '\'')
		{
			l += quotes(av, &l);
			j++;
		}
		else
		{
			j++;
			l++;
		}
	}
	return (j);
}

int			options_number(char *av, int *i)
{
	int l;
	int j;
	int nb;

	l = 0;
	nb = 0;
	j = *i;
	while (av[j] != '\0')
	{
		while (av[j] && (av[j] == ' ' || av[j] == '\t'))
			j++;
		if (!av[j])
			break ;
		j = parsing_hmmm(av, j);
		nb++;
	}
	return (nb);
}

char		**get_options(char *str, int *i)
{
	int		opt_nb;
	char	**options;
	int		j;

	j = 1;
	opt_nb = options_number(str, i);
	options = (char **)malloc(sizeof(char *) * (opt_nb + 2));
	options[0] = ft_strdup("full");
	while (j <= opt_nb)
	{
		options[j] = get_command(str, i);
		j++;
	}
	options[j] = 0;
	return (options);
}

t_parse		*parsing(char *str)
{
	t_parse	*args;
	int		i;

	i = 0;
	args = (t_parse *)malloc((sizeof(t_parse)));
	args->command = (char **)malloc((sizeof(char *) * 2));
	args->options = 0;
	args->command[0] = get_command(str, &i);
	args->options = get_options(str, &i);
	args->command[1] = 0;
	return (args);
}
