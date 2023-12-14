/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:39:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/14 09:27:38 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_vector	get_rgb_vect(unsigned int color)
{
	t_vector	rgba;

	rgba.x = ((color & 0xff000000) >> 24) / 255; 
	rgba.y = ((color & 0x00ff0000) >> 16) / 255;
	rgba.z = ((color & 0x0000ff00) >> 8) / 255;
	return (rgba);
}

unsigned int	get_vect_rgba(t_vector c)
{
	return ((int)(c.x * 255) << 24 | (int)(c.y * 255) << 16 |
			(int)(c.z * 255) << 8 | 255);
}

t_vector	clamp_color(t_vector color)
{
	if (color.x < 0)
		color.x = 0;
	if (color.x > 1)
		color.x = 1;
	if (color.y < 0)
		color.y = 0;
	if (color.y > 1)
		color.y = 1;
	if (color.z < 0)
		color.z = 0;
	if (color.z > 1)
		color.z = 1;
	return (color);
}

t_vector	get_img_pixel(t_data *data, int x, int y)
{
	t_vector	color;
	uint8_t		*curr;

	curr = &data->img->pixels[(y * data->img->width + x) * 4]; 
	color.x = (float) *curr / 255;
	curr++;
	color.y = (float) *curr / 255;
	curr++;
	color.z = (float) *curr / 255;
	return (color);
}
