/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslift <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 05:08:18 by sslift            #+#    #+#             */
/*   Updated: 2020/02/21 21:27:19 by sslift           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		binary(int n)
{
	int left;
	int right;
	int mid;

	left = 0;
	right = 46340;
	if (right * right < n)
		return (0);
	else if (right * right == n)
		return (right);
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (mid * mid == n)
			return (mid);
		else if (mid * mid < n)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (left);
}

int		ft_sqrt(int nb)
{
	if (nb <= 0)
		return (0);
	return (binary(nb));
}
