/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 15:41:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	miss(void);

void	*render_thread(void *param)
{
	t_thread	*thread;
	t_data		*data;
	int			i;
	int			div;
	int			end;

	thread = (t_thread *) param;
	data = thread->data;
	div = (data->width * data->height) / THREAD_MAX;
	i = thread->id * div;
	if (thread->id == THREAD_MAX - 1)
		end = data->width * data->height;
	else
		end = i + div;
	while (i < end)
	{
		perpixel((i % data->width), (i / data->width), data);
		i++;
	}
	return (NULL);
}

float	clamp_image(t_data *data)
{
	float	max;
	float	ratio;
	int		x;
	int		y;

	x = 0;
	max = 0;
	while (x < data->width)
	{
		y = -1;
		while (++y < data->height)
		{
			if (data->accumulator[y * data->width + x].x > max)
				max = data->accumulator[y * data->width + x].x;
			if (data->accumulator[y * data->width + x].y > max)
				max = data->accumulator[y * data->width + x].y;
			if (data->accumulator[y * data->width + x].z > max)
				max = data->accumulator[y * data->width + x].z;
		}
		x++;
	}
	ratio = 1;
	if (max > 1 * data->camera.exposure)
		ratio = 1 * data->camera.exposure / max; 
	return (ratio);
}

void	update_image(t_data *data)
{
	t_vector	color;
	float		ratio;
	int			x;
	int			y;

	ratio = clamp_image(data);
	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			color.x = ratio * data->accumulator[y * data->width + x].x;
			color.y = ratio * data->accumulator[y * data->width + x].y;
			color.z = ratio * data->accumulator[y * data->width + x].z;
			color = clamp_color(data, color);
			mlx_put_pixel(data->img, x, y, get_vect_rgba(color));
			y++;
		}
		x++;
	}
}
