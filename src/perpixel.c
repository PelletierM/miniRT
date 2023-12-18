/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:06:59 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 14:19:30 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	black_color(void);
void		get_new_camera(t_data *data, t_camera *new_camera, int x, int y);

void	perpixel(int x, int y, t_data *data)
{
	t_ray		ray;
	t_vector	color;

	ray = get_current_ray(data, x, y);
	color = trace_pixel(data, ray, 0);
	color = update_color(data, color, x, y);
}

t_ray	get_current_ray(t_data *data, int x, int y)
{
	t_ray		ray;
	t_camera	new_camera;

	ray.position.x = data->camera.position.x;
	ray.position.y = data->camera.position.y;
	ray.position.z = data->camera.position.z;
	get_new_camera(data, &new_camera, x, y);
	ray.orientation = vadd(vadd(
				new_camera.z_axis, new_camera.y_axis), new_camera.x_axis);
	ray = apply_dof(data, ray);
	return (ray);
}

void	get_new_camera(t_data *data, t_camera *new_camera, int x, int y)
{
	float	pixel_len;
	float	pixel_height;
	float	ratio;
	float	x_scale;
	float	y_scale;

	x_scale = (((float) x / data->width) * data->camera.vp_horiz_len)
		- (data->camera.vp_horiz_len / 2);
	new_camera->x_axis = vsmul(data->camera.x_axis, x_scale);
	y_scale = (((float) y / data->height) * data->camera.vp_vert_len)
		- (data->camera.vp_vert_len / 2);
	new_camera->y_axis = vsmul(data->camera.y_axis, y_scale);
	new_camera->z_axis = vsmul(data->camera.z_axis, data->camera.focal_len);
	pixel_len = (float) 1 / data->width * data->camera.vp_horiz_len;
	pixel_height = (float) 1 / data->height * data->camera.vp_vert_len;
	ratio = ((float) rand() / (float)(RAND_MAX)) - 0.5;
	new_camera->x_axis = vadd(new_camera->x_axis,
			vsmul(data->camera.x_axis, ratio * pixel_len));
	ratio = ((float) rand() / (float)(RAND_MAX)) - 0.5;
	new_camera->y_axis = vadd(new_camera->y_axis,
			vsmul(data->camera.y_axis, ratio * pixel_height));
}

t_vector	trace_pixel(t_data *data, t_ray ray, int depth)
{
	t_hit		hit;
	t_vector	light_color;
	t_vector	color;
	t_ray		next_ray;
	float		emissive_ratio;

	color = black_color();
	if (depth == MAX_BOUNCE || depth > data->samples)
		return (color);
	hit = get_closest_hit(data, ray);
	if (hit.t == MAX_DIST)
		return (color);
	get_object_color(data, &hit, ray);
	emissive_ratio = get_emissive_ratio(data, hit);
	get_object_color(data, &hit, ray);
	if (emissive_ratio > 0)
		return (vsmul(hit.color, emissive_ratio));
	get_normal_hit(data, ray, &hit);
	light_color = get_light(hit, data);
	next_ray.position = translate_pt(hit.position, 0.001, hit.normal);
	next_ray.orientation = get_material_normal(data, hit, ray);
	light_color = vadd(light_color,
			vsmul(trace_pixel(data, next_ray, depth + 1), 0.8));
	color = vmul(light_color, hit.color);
	return (color);
}

t_vector	black_color(void)
{
	t_vector	color;

	color.x = 0;
	color.y = 0;
	color.z = 0;
	return (color);
}
