/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:39:51 by eguefif           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/12 16:38:54 by eguefif          ###   ########.fr       */
=======
/*   Updated: 2023/12/12 17:23:35 by maxpelle         ###   ########.fr       */
>>>>>>> d0e8ea53979a5646e3ca3c06d955847cc7de7f5f
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

	rgba.x = (color & 0xff000000) >> 24; 
	rgba.y = (color & 0x00ff0000) >> 16;
	rgba.z = (color & 0x0000ff00) >> 8;
	return (rgba);
}

unsigned int	get_vect_rgba(t_vector c)
{
	return ((int) c.x << 24 | (int) c.y << 16 | (int) c.z << 8 | 255);
}

t_vector	clamp_color(t_vector color)
{
	if (color.x < 0)
		color.x = 0;
	if (color.x > 255)
		color.x = 255;
	if (color.y < 0)
		color.y = 0;
	if (color.y > 255)
		color.y = 255;
	if (color.z < 0)
		color.z = 0;
	if (color.y > 255)
		color.z = 255;
	return (color);
}

t_vector	get_img_pixel(t_data *data, int x, int y)
{
	t_vector	color;
	uint8_t		*curr;

	curr = &data->img->pixels[(y * data->img->width + x) * 4]; 
	color.x = *curr;
	curr++;
	color.y = *curr;
	curr++;
	color.z = *curr;
	return (color);
}
