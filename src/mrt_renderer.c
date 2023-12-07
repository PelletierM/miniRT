/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/07 16:21:56 by eguefif          ###   ########.fr       */
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
	hit.shape = 0;
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
	i = 0;
	while (i < data->num_planes)
	{
		t = check_hit_planes(data->planes[i], ray);
		if (t > 0 && t < hit.t)
		{
			color.x = data->planes[i].color.x;
			color.y = data->planes[i].color.y;
			color.z = data->planes[i].color.z;
			hit.t = t;
			hit.shape = 2;
			hit.i = i;
		}
		i++;
	}
	i = 0;
	int	flag = 0;
	while (i < data->num_cylinders)
	{
		t = check_hit_cylinders(data->cylinders[i], ray, &flag);
		if (t > 0 && t < hit.t)
		{
			color.x = data->cylinders[i].color.x;
			color.y = data->cylinders[i].color.y;
			color.z = data->cylinders[i].color.z;
			hit.t = t;
			hit.shape = 3;
			hit.i = i;
		}
		i++;
	}
	t_vector	normal;
	if (hit.t != 1000000)
	{
		t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, hit.t));
		if (hit.shape == 1)
		{
			normal = vsub(hit_pos, data->spheres[hit.i].position);
			normal = vsdiv(normal, data->spheres[hit.i].diameter / 2);
		}
		else if (hit.shape == 2)
			normal = vnormalize(data->planes[hit.i].orientation);
		else if (hit.shape == 3)
		{
		//	return (color);
			t_vector	x;
			float		m;
			if (flag == 1)
			{
				normal = vnormalize(data->cylinders[hit.i].bottom.orientation);
				//normal = vsmul(normal, -1);
			}
			else if (flag == 2)
			{
				normal = vnormalize(data->cylinders[hit.i].top.orientation);
				//normal = vsmul(normal, -1);
			}
			else
			{
				x = vsub(ray.position, data->cylinders[hit.i].position);
				m = vdot(ray.orientation, vsmul(data->cylinders[hit.i].orientation, hit.t)) + vdot(x, data->cylinders[hit.i].orientation);
				normal = vnormalize(
						(vsub(hit_pos, vadd(data->cylinders[hit.i].position,
											vsmul(data->cylinders[hit.i].orientation, m)))));
				if (flag == 3)
					normal = vsmul(normal, -1);
			}
		}
		else
			return (color);
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

float		check_hit_planes(t_plane plane, t_ray ray)
{
	float	denominator;
	float	numerator;

	denominator = vdot(ray.orientation, plane.orientation);
	if (denominator == 0)
		return (0);
	numerator = vdot(plane.orientation, vsub(vsmul(plane.position, 1), ray.position));
	return (numerator / denominator);
}
