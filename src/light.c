/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:26:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/15 14:08:43 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			is_shadow(t_hit hit, t_data *data);

t_vector get_light(t_hit hit, t_data *data)
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
	light_color = clamp_color(light_color);
	return (light_color);
}

int	is_shadow(t_hit hit, t_data *data)
{
	t_ray	ray;
	t_hit	new_hit;

	ray.position = vcopy(translate_pt(hit.position, 0.01, hit.normal));
	ray.orientation = create_vector_from_points(hit.position,
			data->light.position);
	new_hit = get_closest_hit(data, ray);
	if (new_hit.t > 1)
		return (0);
	if (new_hit.t == MAX_DIST)
		return (0);
	return (1);
}
