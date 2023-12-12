/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:06:59 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/12 17:32:53 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	black_color(void);
t_vector	get_ambient(t_data *data);

void	perpixel(int x, int y, t_data *data)
{
	t_ray		ray;
	t_vector	color;

	ray = get_current_ray(data, x, y);
	color = trace_pixel(data, ray);
	color = clamp_color(color);
	color = update_color(data->samples, color, get_img_pixel(data, x, y));
	mlx_put_pixel(data->img, x, y, get_vect_rgba(color));
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

	float pixel_len = (float) 1 / data->width * data->camera.vp_horiz_len;
	float pixel_height = (float) 1 / data->height * data->camera.vp_vert_len;

	float ratio = ((float) rand() / (float) (RAND_MAX)) - 0.5; 	
	new_cam.x_axis = vadd(new_cam.x_axis, vsmul(data->camera.x_axis, ratio * pixel_len));
	ratio = ((float) rand() / (float) (RAND_MAX)) - 0.5; 	
	new_cam.y_axis = vadd(new_cam.y_axis, vsmul(data->camera.y_axis, ratio * pixel_height));

	ray.orientation = vadd(vadd(
				new_cam.z_axis, new_cam.y_axis), new_cam.x_axis);
	return (ray);
}

t_vector	trace_pixel(t_data *data, t_ray ray)
{
	t_hit		hit;
	t_vector	color;
	float		multiplier;
	int			i;

	multiplier = 1.0;
	color = black_color();
	i = 0;
	while (i < MAX_BOUNCE)
	{
		hit = get_closest_hit(data, ray);
		if (hit.t == MAX_DIST)
		{
			color = vadd(color, vsmul(black_color(), multiplier));
			break ;
		}
		get_normal_hit(data, ray, &hit);
		hit = get_light(hit, data);
		color = vadd(color, vsmul(hit.color, multiplier));
		multiplier *= 0.5;
		ray.position = translate_pt(hit.position, 0.00001, hit.normal);
		ray.orientation = vreflect(ray.orientation, hit.normal);
		i++;
	}
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

t_vector	get_ambient(t_data *data)
{
	return (vsmul(data->ambient.color, data->ambient.ratio));
}
