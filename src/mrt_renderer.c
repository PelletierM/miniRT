/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/15 15:53:59 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	miss(void);
void	get_range(int id, t_data *data, int *range);

void	*render_thread(void *param)
{
	t_thread	*thread;
	t_data		*data;
	int			range[2];
	int			i;

	thread = (t_thread *) param;
	data = thread->data;
	get_range(thread->id, data, range);
	i = range[0];
	while (i < range[1])
	{
		perpixel((i % data->width), (i / data->width), data);
		i++;
	}
	return (NULL);
}

void	get_range(int id, t_data *data, int *range)
{
	int			div;
	int			remaining;

	div = 1;
	if (THREAD_MAX > 0)
		div = (int)((data->width * data->height) / THREAD_MAX);
	remaining = (int)((data->width * data->height) % THREAD_MAX);
	range[0] = id * div;
	if (remaining > id)
		range[0] += id;
	range[1] = range[0] + div;
	if (remaining > id)
		range[1] += 1;
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
		y = 0;
		while (y < data->height)
		{
			if (data->accumulator[y * data->width + x].x > max)
				max = data->accumulator[y * data->width + x].x;
			if (data->accumulator[y * data->width + x].y > max)
				max = data->accumulator[y * data->width + x].y;
			if (data->accumulator[y * data->width + x].z > max)
				max = data->accumulator[y * data->width + x].z;
			y++;
		}
		x++;
	}
	ratio = 1;
	if (max > 1)
		ratio = 1 / max; 
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
			mlx_put_pixel(data->img, x, y, get_vect_rgba(color));
			y++;
		}
		x++;
	}
}
