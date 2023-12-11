/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/11 13:12:56 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	miss(void);
void	perpixel(int x, int y, t_data *data);

void	*render_thread(void *param)
{
	t_thread	*thread;
	t_data		*data;
	int			i;
	int			max;
	int			div;

	thread = (t_thread *) param;
	data = thread->data;
	div = 1;
	if (THREAD_MAX > 0)
		div = (int) ((data->width * data->height) / THREAD_MAX);
	mrt_create_cam(data);
	i = thread->id * div;
	max = i + div;
	while (i < max)
	{
		perpixel((i % data->width), (i / data->width), data);
		i++;
	}
	return (NULL);
}

void	perpixel(int x, int y, t_data *data)
{
	t_ray		ray;
	t_hit		hit;

	ray = get_current_ray(data, x, y);
	hit = trace_pixel(data, ray);
	mlx_put_pixel(data->img, x, y, get_vect_rgba(hit.color));
}

t_ray	get_current_ray(t_data *data, int x, int y)
{
	t_ray		ray;
	t_camera	new_cam;
	float		x_scale;
	float		y_scale;

	ray.position.x = data->camera.position.x;
	ray.position.y = data->camera.position.y;
	ray.position.z = data->camera.position.z;
	x_scale = (((float) x / data->width) * data->camera.vp_horiz_len)
		- (data->camera.vp_horiz_len / 2);
	new_cam.x_axis = vsmul(data->camera.x_axis, x_scale);
	y_scale = (((float) y / data->height) * data->camera.vp_vert_len)
		- (data->camera.vp_vert_len / 2);
	new_cam.y_axis = vsmul(data->camera.y_axis, y_scale);
	new_cam.z_axis = vsmul(data->camera.z_axis, data->camera.focal_len);
	ray.orientation = vadd(vadd(
				new_cam.z_axis, new_cam.y_axis), new_cam.x_axis);
	return (ray);
}

t_hit	trace_pixel(t_data *data, t_ray ray)
{
	t_hit		hit;

	hit = get_closest_hit(data, ray);
	if (hit.t == MAX_DIST)
		return (miss());
	get_normal_hit(data, ray, &hit);
	hit = get_light(hit, data);
	return (hit);
}

t_hit	miss(void)
{
	t_hit	hit;

	hit.color.x = 0;
	hit.color.y = 0;
	hit.color.z = 0;
	hit.t = -1;
	hit.i = -1;
	hit.shape = -1;
	return (hit);
}
