/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:26:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 13:21:54 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	get_light(t_hit hit, t_data *data)
{
	float		light;
	t_vector	light_direction;

	light_direction = vsub(hit.position, data->light.position);
	light_direction = vnormalize(light_direction);
	light_direction = vsmul(light_direction, -1);
	light = vdot(hit.normal, light_direction);
	if (light < data->ambient.ratio)
		light = data->ambient.ratio;
	hit.color = vsmul(hit.color, light);
	return (hit);
}
