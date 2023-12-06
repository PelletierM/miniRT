/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/06 11:20:14 by eguefif          ###   ########.fr       */
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
		t_ray	ray;
		
		ray.position.x = data->camera.position.x;
		ray.position.y = data->camera.position.y;
		ray.position.z = data->camera.position.z;
		
		ray.orientation.x = ((float) x / data->width) * 2 - 1;
		ray.orientation.y = ((float) y / data->height) * 2 - 1;
		ray.orientation.z = data->camera.orientation.z;
		return (ray);
}

t_vector	trace_pixel(t_data *data, t_ray ray)
{
	t_vector	color;
	t_hit		hit;
	int			i;
	float		t;

	i = 0;
	hit.t = 0;
	hit.i = 1000000;
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
		t_vector hit_pos = op_vect_add(ray.position, op_vect_scalar_mul(ray.orientation, hit.t)); 
		t_vector normal = op_vect_sub(hit_pos, data->spheres[hit.i].position);
		normal = op_vect_scalar_div(normal, data->spheres[hit.i].diameter / 2);
		t_vector light_direction = op_vect_sub(hit_pos, data->light.position);
		light_direction = op_vect_normalize(light_direction);
		light_direction = op_vect_scalar_mul(light_direction, -1);
		float light = op_vect_dot(normal, light_direction);
		if (light < data->ambient.ratio)
			light = data->ambient.ratio;
		color = op_vect_scalar_mul(color, light);
	}
	return (color);
}
