/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/06 12:54:22 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	trace_pixel(t_data *data, t_ray ray);
t_ray		get_current_ray(t_data *data, int x, int y);

void	render(void *param)
{
	t_data		*data;
	t_ray		ray;
	t_vector	color;
	int	x;
	int	y;

	data = (t_data *) param;
	x = 0;
	mrt_create_camera(data);
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			ray = get_current_ray(data, x, y);
			color = trace_pixel(data, ray);
			mlx_put_pixel(data->img, x, y, get_vect_rgba(color));
			y++;
		}
		x++;
	}
}

t_ray	get_current_ray(t_data *data, int x, int y)
{
		t_ray		ray;
		t_vector	camera_x;
		t_vector	camera_y;
		t_vector	camera_z;
		float		x_scale;
		float		y_scale;

		ray.position.x = data->camera.position.x;
		ray.position.y = data->camera.position.y;
		ray.position.z = data->camera.position.z;

		x_scale = (((float) x / data->width) * data->camera.vp_horiz_len)
			- (data->camera.vp_horiz_len / 2);
		camera_x = vsmul(data->camera.x_axis, x_scale);
		y_scale = (((float) y / data->height) * data->camera.vp_vert_len)
			- (data->camera.vp_vert_len / 2);
		camera_y = vsmul(data->camera.y_axis, y_scale);
		camera_z = vsmul(data->camera.z_axis, data->camera.focal_len);

		ray.orientation = vadd(vadd(camera_z, camera_y), camera_x);
		return (ray);
}

t_vector	trace_pixel(t_data *data, t_ray ray)
{
	t_vector	color;
	t_hit		hit;
	int			i;
	float		t;

	i = 0;
	hit.t = 10000000;
	hit.i = 0;
	t = 0;
	color.x = 0;
	color.y = 0;
	color.z = 0;
	while (i < data->num_spheres)
	{
		t = check_hit_sphere(data->spheres[i], ray);
		if (t > 0 && t < hit.t)
		{
			color.x = data->spheres[i].color.x;
			color.y = data->spheres[i].color.y;
			color.z = data->spheres[i].color.z;
			hit.t = t;
			hit.shape = 1;
			hit.i = i;
		}
		i++;
	}
	if (hit.t != 1000000)
	{
		t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, hit.t)); 
		t_vector normal = vsub(hit_pos, data->spheres[hit.i].position);
		normal = vsdiv(normal, data->spheres[hit.i].diameter / 2);
		t_vector light_direction = vsub(hit_pos, data->light.position);
		light_direction = vnormalize(light_direction);
		light_direction = vsmul(light_direction, -1);
		float light = vdot(normal, light_direction);
		if (light < data->ambient.ratio)
			light = data->ambient.ratio;
		color = vsmul(color, light);
	}
	return (color);
}
