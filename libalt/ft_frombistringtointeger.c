/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fromBiStringToInteger.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <sslift@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:31:41 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_frombistringtointeger(char *str)
{
	int total;

	total = 0;
	while (*str)
	{
		total *= 2;
		if (*str++ == '1')
		{
			total += 1;
		}
	}
	return (total);
}
