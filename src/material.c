/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:11:30 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/13 11:15:47 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_material_id(t_data *data, t_hit hit);
float	get_roughness_factor(t_data *data, int id);

t_vector	get_material_normal(t_data *data, t_hit hit)
{
	int			id;
	t_vector	v;

	id = get_material_id(data, hit);
	if (id < 0)
		return (hit.normal);
	v.x = (rand() / RAND_MAX - 1.0) * get_roughness_factor(data, id);
	v.y = (rand() / RAND_MAX - 1.0) * get_roughness_factor(data, id);
	v.z = (rand() / RAND_MAX - 1.0) * get_roughness_factor(data, id);
	return (vnormalize(vadd(hit.normal, v)));
}

int	get_material_id(t_data *data, t_hit hit)
{
	if (hit.shape == OBJ_SPHERE)
		return (data->spheres[hit.i].material_id);
	if (hit.shape == OBJ_CYL)
		return (data->cylinders[hit.i].material_id);
	if (hit.shape == OBJ_PLANE)
		return (data->planes[hit.i].material_id);
	return (-1);
}

float	get_roughness_factor(t_data *data, int id)
{
	int	i;

	i = 0;
	while (i < data->num_materials)
	{
		if (data->materials[i].id == id)
			return (data->materials[i].roughness);
		i++;
	}
	return (0);
}
