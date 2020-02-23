/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intarrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:35:05 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_clearall(char **arr)
{
	char *tmp;

	tmp = *arr;
	while (tmp)
		free(tmp++);
	free(tmp);
	return (NULL);
}

char			*ft_intarrjoin(int *arr, size_t len, int del)
{
	char	**arr_str;
	char	*result;
	size_t	i;

	if (!(arr_str = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!(arr_str[i] = ft_itoa(arr[i])))
			return (ft_clearall(arr_str));
		i++;
	}
	if (!(result = ft_arrjoin(arr_str, len, del)))
		return (ft_clearall(arr_str));
	return (result);
}
