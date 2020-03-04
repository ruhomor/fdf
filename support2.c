/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 06:43:36 by kachiote          #+#    #+#             */
/*   Updated: 2020/03/04 06:43:38 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color				hsvtorgb(t_color hsv)
{
	t_color			rgb;
	unsigned char	region;
	unsigned char	remainder;
	t_color			wot;

	rgb = (t_color){0, 0, 0};
	if (hsv.g == 0)
	{
		shufflr(&rgb, hsv.b, hsv.b, hsv.b);
		return (rgb);
	}
	region = hsv.r / 43;
	remainder = (hsv.r - (region * 43)) * 6;
	wotrewot(&wot, hsv, remainder);
	return (regionhandle(wot, hsv, region));
}

void				sm(t_color rgb, t_color *hsv, unsigned char rgbmin,
		unsigned char rgbmax)
{
	if (rgbmax == rgb.r)
		hsv->r = 0 + 43 * (rgb.g - rgb.b) / (rgbmax - rgbmin);
	else if (rgbmax == rgb.g)
		hsv->r = 85 + 43 * (rgb.b - rgb.r) / (rgbmax - rgbmin);
	else
		hsv->r = 171 + 43 * (rgb.r - rgb.g) / (rgbmax - rgbmin);
}

unsigned char		rgbminft(t_color rgb)
{
	if (rgb.r < rgb.g)
	{
		if (rgb.r < rgb.b)
			return (rgb.r);
		else
			return (rgb.b);
	}
	else
	{
		if (rgb.g < rgb.b)
			return (rgb.g);
		else
			return (rgb.b);
	}
}

unsigned char		rgbmaxft(t_color rgb)
{
	if (rgb.r > rgb.g)
	{
		if (rgb.r > rgb.b)
			return (rgb.r);
		else
			return (rgb.b);
	}
	else
	{
		if (rgb.g > rgb.b)
			return (rgb.g);
		else
			return (rgb.b);
	}
}

t_color				rgbtohsv(t_color rgb)
{
	t_color			hsv;
	unsigned char	rgbmin;
	unsigned char	rgbmax;

	rgbmin = rgbminft(rgb);
	rgbmax = rgbmaxft(rgb);
	hsv.b = rgbmax;
	if (hsv.b == 0)
	{
		hsv.r = 0;
		hsv.g = 0;
		return (hsv);
	}
	hsv.g = 255 * (int)(rgbmax - rgbmin) / hsv.b;
	if (hsv.g == 0)
	{
		hsv.r = 0;
		return (hsv);
	}
	sm(rgb, &hsv, rgbmin, rgbmax);
	return (hsv);
}
