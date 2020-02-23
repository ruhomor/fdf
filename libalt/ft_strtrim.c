/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 02:26:53 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	finish;
	char	*str;

	if (!s)
		return (NULL);
	start = 0;
	while ((*(s + start) == ' ') || (*(s + start) == '\n') ||
			(*(s + start) == '\t'))
		start++;
	finish = ft_strlen(s) - 1;
	while ((finish > start) && ((*(s + finish) == ' ') ||
			(*(s + finish) == '\n') || (*(s + finish) == '\t')))
		finish--;
	if (!(str = ft_strnew(finish - start + 1)))
		return (NULL);
	str = ft_strncpy(str, s + start, finish - start + 1);
	return (str);
}
