/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 05:16:13 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t count)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	*tmp_src;

	tmp = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	i = 0;
	while (i < count)
	{
		*(tmp + i) = *(tmp_src + i);
		if (*(tmp + i) == (unsigned char)c)
			return (tmp + i + 1);
		i++;
	}
	return (NULL);
}
