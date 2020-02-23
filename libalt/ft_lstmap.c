/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 10:01:20 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst_res;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	if (!(lst_res = (t_list *)malloc(ft_lstsize(lst) * sizeof(t_list))))
		return (NULL);
	tmp = lst_res;
	*lst_res = *f(lst);
	while (lst && lst->next)
	{
		lst_res->next = f(lst->next);
		lst = lst->next;
		lst_res = lst_res->next;
	}
	lst_res->next = NULL;
	return (tmp);
}
