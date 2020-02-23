/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:40:50 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstat(t_list *lst, size_t n)
{
	size_t i;

	if (ft_lstsize(lst) <= n)
		return (NULL);
	i = 0;
	while (i < n)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
