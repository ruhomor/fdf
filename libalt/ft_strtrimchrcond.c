/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimchrCond.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:39:16 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrimchrcond(char const *s, int c, int left, int right)
{
	size_t	start;
	size_t	finish;
	char	*str;

	if (!s)
		return (NULL);
	start = 0;
	while (((*(s + start) == c) || (*(s + start) == '\n') ||
			(*(s + start) == '\t')) && left)
		start++;
	finish = ft_strlen(s) - 1;
	while (((finish > start) && ((*(s + finish) == c) ||
			(*(s + finish) == '\n') || (*(s + finish) == '\t'))) && right)
		finish--;
	if (!(str = ft_strnew(finish - start + 1)))
		return (NULL);
	str = ft_strncpy(str, s + start, finish - start + 1);
	return (str);
}
