/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:26:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 14:13:42 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_shadow(t_hit hit, t_data *data);

t_hit	get_light(t_hit hit, t_data *data)
{
	float		light;
	t_vector	light_direction;

	if (is_shadow(hit, data))
		light = data->ambient.ratio;
	else
	{
		light_direction = vsub(hit.position, data->light.position);
		light_direction = vnormalize(light_direction);
		light_direction = vsmul(light_direction, -1);
		light = vdot(hit.normal, light_direction);
		if (light < data->ambient.ratio)
			light = data->ambient.ratio;
	}
	hit.color = vsmul(hit.color, light);
	return (hit);
}

int	is_shadow(t_hit hit, t_data *data)
{
	t_ray	ray;
	t_hit	new_hit;

	ray.position = vcopy(translate_point(hit.position, 0.2, hit.normal));
	ray.orientation = vcopy(hit.normal);
	new_hit = get_closest_hit(data, ray);
	if (new_hit.t == MAX_DIST)
		return (0);
	return (1);
}
