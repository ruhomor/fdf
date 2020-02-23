/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:09:39 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	i;
	size_t	j;

	n = size;
	i = 0;
	while ((n != 0) && (*(dst + i) != '\0'))
	{
		i++;
		n--;
	}
	n = (size - i);
	if (n <= 1)
		return (i + ft_strlen(src));
	j = 0;
	while (j < ft_strlen(src))
	{
		if (n-- > 1)
			*(dst + i + j) = *(src + j);
		else
			break ;
		j++;
	}
	*(dst + i + j) = '\0';
	return (i + ft_strlen(src));
}
