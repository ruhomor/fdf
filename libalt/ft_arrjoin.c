/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:39:59 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wholelen(char **arr, size_t len)
{
	size_t i;
	size_t size;

	i = 0;
	size = 0;
	while (i < len)
	{
		size += ft_strlen(arr[i]);
		i++;
	}
	return (size + len - 1);
}

char			*ft_arrjoin(char **arr, size_t len, int del)
{
	size_t	i;
	char	*join;
	char	*delim;

	i = 0;
	if (!(join = ft_strnew(ft_wholelen(arr, len) + 1)))
		return (NULL);
	if (!(delim = ft_strnew(2)))
	{
		free(join);
		return (NULL);
	}
	*delim = del;
	while (i < len)
	{
		join = ft_strcat(join, arr[i]);
		if (i != len - 1)
			join = ft_strcat(join, delim);
		i++;
	}
	return (join);
}
