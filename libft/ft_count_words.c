/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 16:02:37 by hhamdaou          #+#    #+#             */
/*   Updated: 2018/10/20 16:03:28 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char const *str, char c)
{
	int words;
	int count;

	words = 0;
	count = 0;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str != c)
		{
			if (!count)
				words++;
			count++;
		}
		else
			count = 0;
		str++;
	}
	return (words);
}
