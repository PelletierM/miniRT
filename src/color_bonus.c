/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:39:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 13:52:44 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_vector	get_rgb_vect(unsigned int color)
{
	t_vector	rgba;

	rgba.x = (float)((color & 0xff000000) >> 24) / 255; 
	rgba.y = (float)((color & 0x00ff0000) >> 16) / 255;
	rgba.z = (float)((color & 0x0000ff00) >> 8) / 255;
	return (rgba);
}

unsigned int	get_vect_rgba(t_vector c)
{
	return ((int)(c.x * 255) << 24 | (int)(c.y * 255) << 16 |
			(int)(c.z * 255) << 8 | 255);
}

t_vector	clamp_color(t_data *data, t_vector color)
{
	float	max;
	float	ratio;

	max = color.x;
	if (color.y > max)
		max = color.y;
	if (color.z > max)
		max = color.z;
	if (max > 1)
	{
		ratio = (float) 1 / max;
		color.x *= ratio + ((max - color.x)
				* ratio * (data->camera.exposure - 1) / 16);
		color.y *= ratio + ((max - color.y)
				* ratio * (data->camera.exposure - 1) / 16);
		color.z *= ratio + ((max - color.z)
				* ratio * (data->camera.exposure - 1) / 16);
	}
	if (color.x > 1)
		color.x = 1;
	if (color.y > 1)
		color.y = 1;
	if (color.z > 1)
		color.z = 1;
	return (color);
}

t_vector	get_img_pixel(mlx_texture_t *texture, int x, int y)
{
	t_vector	color;
	uint8_t		*curr;

	curr = &texture->pixels[(y * texture->width + x)
		* texture->bytes_per_pixel]; 
	color.x = (float) *curr / 255;
	curr++;
	color.y = (float) *curr / 255;
	curr++;
	color.z = (float) *curr / 255;
	return (color);
}
