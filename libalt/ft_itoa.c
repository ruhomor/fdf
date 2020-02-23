/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 05:55:47 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennb(int nb)
{
	int len;

	len = 0;
	if (nb <= 0)
		len++;
	if (nb == 0)
		return (len);
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	len = ft_lennb(n);
	if (!(str = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (n < 0)
		*str = '-';
	if (n == 0)
		*str = '0';
	i = len - 1;
	while ((i >= 0) && (n != 0))
	{
		*(str + i) = '0' + ft_abs(n % 10);
		n /= 10;
		i--;
	}
	*(str + len) = '\0';
	return (str);
}
