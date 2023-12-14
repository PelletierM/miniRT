/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_value_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:08:12 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/13 17:32:15 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_ambient(t_data data);
int	check_camera(t_data data);
int	check_light(t_data data);
int	check_spheres(t_data data);
int	check_planes(t_data data);
int	check_materials(t_data data);

int	check_data(t_data data)
{
	if (check_ambient(data))
		return (1);
	if (check_camera(data))
		return (1);
	if (check_light(data))
		return (1);
	if (check_spheres(data))
		return (1);
	if (check_planes(data))
		return (1);
	if (check_cylinders(data))
		return (1);
	if (check_materials(data))
		return (1);
	return (0);
}

int	check_ambient(t_data data)
{
	if (data.ambient.ratio < 0 || data.ambient.ratio > 1)
		return (1);
	if (check_color(data.ambient.color))
		return (1);
	return (0);
}

int	check_camera(t_data data)
{
	if (data.camera.fov < 0 || data.camera.fov > 180)
		return (1);
	if (check_normalized_vector(data.camera.z_axis))
		return (1);
	return (0);
}

int	check_light(t_data data)
{
	if (data.light.ratio < 0 || data.light.ratio > 1)
		return (1);
	if (check_color(data.light.color))
		return (1);
	return (0);
}

int	check_materials(t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_materials)
	{
		if (data.materials[i].id < 0)
			return (1);
		if (data.materials[i].roughness < 0
				&& data.materials[i].roughness > 1)
			return (1);
		if (data.materials[i].metallic < 0
				&& data.materials[i].metallic > 1)
			return (1);
		if (data.materials[i].emissive_ratio < 0
				&& data.materials[i].emissive_ratio > 5)
			return (1);
		i++;
	}
	return (0);
}
