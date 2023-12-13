/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:11:30 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/13 13:57:10 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_material_id(t_data *data, t_hit hit);

t_vector	get_material_normal(t_data *data, t_hit hit)
{
	t_vector	v;
	float		roughness;

	id = get_material_id(data, hit);
	if (id < 0)
		return (hit.normal);
	roughness = get_roughness_factor(data, id);
	roughness = 1;
	v.x = ((float) rand() / RAND_MAX) * roughness;
	v.y = ((float) rand() / RAND_MAX) * roughness;
	v.z = ((float) rand() / RAND_MAX) * roughness;
	v = vnormalize(v);	
	if (vdot(v, hit.normal) < 0)
		vsmul(v, -1);
	return (v);
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

float	get_roughness_factor(t_data *data, t_hit hit)
{
	int	i;
	int	id;

	i = 0;
	id = get_material_id(data, hit);
	if (id == -1)
		return (-1);
	while (i < data->num_materials)
	{
		if (data->materials[i].id == id)
			return (data->materials[i].roughness);
		i++;
	}
	return (1);
}

float	get_metallic_factor(t_data *data, t_hit hit)
{
	int	i;
	int	id;

	i = 0;
	id = get_material_id(data, hit);
	if (id == -1)
		return (-1);
	while (i < data->num_materials)
	{
		if (data->materials[i].id == id)
			return (data->materials[i].roughness);
		i++;
	}
	return (1);
}
