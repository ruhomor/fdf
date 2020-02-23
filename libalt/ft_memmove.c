/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:15:49 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t count)
{
	unsigned char	*tmp;
	unsigned char	*tmp_src;

	tmp = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (dst <= src)
		tmp = (unsigned char *)ft_memcpy(dst, src, count);
	else
	{
		while (count > 0)
		{
			*(tmp + count - 1) = *(tmp_src + count - 1);
			count--;
		}
	}
	return (tmp);
}
