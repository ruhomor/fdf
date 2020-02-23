/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 03:20:25 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_if_split(char c_prev, char c_at, char c)
{
	if (c_at == c)
		return (0);
	if (c_prev == c)
		return (1);
	return (0);
}

static int	ft_nbr_split(char *str, char c)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (*(str + i) != '\0')
	{
		if ((i == 0) && (*str != c))
			nb++;
		else if ((*(str + i) != c) &&
			(ft_if_split(*(str + i - 1), *(str + i), c)))
			nb++;
		i++;
	}
	return (nb);
}

static char	**ft_cleanall(char **split)
{
	char *tmp;

	tmp = *split;
	while (tmp)
		free(tmp++);
	free(tmp);
	return (NULL);
}

static char	**ft_split(char **split, char *str, char c)
{
	size_t i;
	size_t len;
	size_t k;

	i = 0;
	k = 0;
	while (*(str + i) != '\0')
	{
		len = 0;
		if ((((i == 0) && (*str != c)) && (*(str + i) != '\0')) ||
			((*(str + i) != c) && (ft_if_split(*(str + i - 1), *(str + i), c))))
		{
			while ((*(str + i) != '\0') && (*(str + i) != c))
			{
				len++;
				i++;
			}
			if (!(split[k] = ft_strsub(str, i - len, len)))
				return (ft_cleanall(split));
			k++;
		}
		i++;
	}
	split[k] = NULL;
	return (split);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	char	*str;

	if (!s)
		return (NULL);
	if (!(str = ft_strdup(s)))
		return (NULL);
	if (!(split = (char **)malloc((ft_nbr_split(str, c) + 1) * sizeof(char *))))
		return (NULL);
	return (ft_split(split, str, c));
}
