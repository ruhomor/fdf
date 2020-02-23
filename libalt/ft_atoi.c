/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:22:13 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sign(long nb)
{
	if (nb > 0)
		return (1);
	else if (nb == 0)
		return (0);
	else
		return (-1);
}

static int	ft_nb(const char *str, int start, int sign)
{
	long nb;

	nb = 0;
	while (*(str + start) != '\0')
	{
		if ((*(str + start) - '0' > 9) || (*(str + start) - '0' < 0))
			break ;
		nb = 10 * nb + sign * (*(str + start) - '0');
		if (sign * ft_sign(nb) < 0)
			return (ft_sign(ft_sign(nb) >> 1));
		start++;
	}
	return ((int)nb);
}

int			ft_atoi(const char *str)
{
	int start;
	int sign;

	start = 0;
	sign = 1;
	while ((*(str + start) == ' ') || (*(str + start) == '\t') ||
			(*(str + start) == '\n') || (*(str + start) == '\v') ||
			(*(str + start) == '\f') || (*(str + start) == '\r'))
		start++;
	if ((*(str + start) == '-') || (*(str + start) == '+'))
	{
		if (*(str + start) == '-')
			sign = -1;
		start++;
	}
	return (ft_nb(str, start, sign));
}
