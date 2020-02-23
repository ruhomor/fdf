/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:08:01 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *srch)
{
	int		i;
	int		j;

	i = 0;
	if (*srch == '\0')
		return ((char *)str);
	while (*(str + i) != '\0')
	{
		if (*(str + i) == *srch)
		{
			j = 0;
			while (*(srch + j) != '\0')
			{
				if (*(srch + j) != *(str + i + j))
					break ;
				j++;
			}
			if (*(srch + j) == '\0')
				return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}
