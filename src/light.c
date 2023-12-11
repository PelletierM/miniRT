/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:26:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/11 13:09:41 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			is_shadow(t_hit hit, t_data *data);
t_vector	cap_light(t_vector color);

t_hit	get_light(t_hit hit, t_data *data)
{
	float		light;
	t_vector	light_direction;
	t_vector	light_color;

	light_color = vsmul(data->ambient.color, data->ambient.ratio);
	if (!is_shadow(hit, data))
	{
		light_direction = vsub(hit.position, data->light.position);
		light_direction = vnormalize(light_direction);
		light_direction = vsmul(light_direction, -1);
		light = vdot(hit.normal, light_direction);
		light *= data->light.ratio;
		if (light > 0)
			light_color = vadd(light_color, vsmul(data->light.color, light));
	}
	hit.color = vmul(cap_light(light_color), vsmul(hit.color, (float) 1 / 255));
	hit.color = cap_light(hit.color);
	return (hit);
}

int	is_shadow(t_hit hit, t_data *data)
{
	t_ray	ray;
	t_hit	new_hit;

	ray.position = vcopy(translate_point(hit.position, 0.01, hit.normal));
	ray.orientation = create_vector_from_points(hit.position, data->light.position);
	new_hit = get_closest_hit(data, ray);
	if (new_hit.t > 1)
		return (0);
	if (new_hit.t == MAX_DIST)
		return (0);
	return (1);
}

t_vector	cap_light(t_vector color)
{
	if (color.x < 0)
		color.x = 0;
	if (color .x > 255)
		color.x = 255;
	if (color.y < 0)
		color.y = 0;
	if (color .y > 255)
		color.y = 255;
	if (color.z < 0)
		color.z = 0;
	if (color .z > 255)
		color.z = 255;
	return (color);
}
