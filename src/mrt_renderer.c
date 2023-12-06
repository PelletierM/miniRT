/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/06 11:46:17 by maxpelle         ###   ########.fr       */
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
			ray.orientation.x *= data->ratio;
			color = trace_pixel(data, ray);
			mlx_put_pixel(data->img, x, (data->height - y), get_vect_rgba(color));
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


		x_scale = ((float) x / data->width - (data->camera.vp_horiz_len / 2));
		camera_x = vsmul(data->camera.x_axis, x_scale);
		y_scale = ((float) y / data->height - (data->camera.vp_vert_len / 2));
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
/*
		float		viewport_height;
		float		viewport_width;
		t_vector	viewport_u;
		t_vector	viewport_v;
		t_vector	pixel_delta_u;
		t_vector	pixel_delta_v;
		t_vector	viewport_upper_left;
		t_vector	pixel00_loc;
		float		focal_length;
		
		focal_length = data->camera.orientation.z;
		viewport_height = 2.0;
		viewport_width = viewport_height * (float)((float) data->width / (float) data->height);

		viewport_u.x = viewport_width;
		viewport_u.y = 0;
		viewport_u.z = 0;

		viewport_v.x = 0;
		viewport_v.y = -viewport_height;
		viewport_v.z = 0;

		pixel_delta_u = vsdiv(viewport_u, (float) data->width);
		pixel_delta_v = vsdiv(viewport_v, (float) data->height);
		
		t_vector tmp;
		tmp.x = 0;
		tmp.y = 0;
		tmp.z = focal_length;
		viewport_upper_left = vsub(data->camera.position, tmp);
		viewport_upper_left = vsub(viewport_upper_left,
				vsdiv(viewport_v, 2));
		viewport_upper_left = vsub(viewport_upper_left,
				vsdiv(viewport_u, 2));
		pixel00_loc = vadd(viewport_upper_left, vsmul(
					vadd(pixel_delta_u, pixel_delta_v), 0.5));
		t_vector c = vadd(pixel00_loc, vadd(vsmul(pixel_delta_u, x),
					vsmul(pixel_delta_v, y)));
		ray.orientation = vsub(c, ray.position);
		*/
