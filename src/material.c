/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:11:30 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 11:20:52 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			get_material_id(t_data *data, t_hit hit);
t_vector	get_roughness_normal(t_hit, float roughness, t_ray ray);
t_vector	get_metallic_normal(t_hit hit, t_ray ray);

t_vector	get_material_normal(t_data *data, t_hit hit, t_ray ray)
{
	t_vector	v;
	float		roughness;
	float		metallic;

	if (has_texture(data, &hit))
		v = get_texture_normal(data, hit, ray);
	roughness = get_roughness_factor(data, hit);
	metallic = get_metallic_factor(data, hit);
	v = vcopy(hit.normal);
	if (metallic > 0)
		v = get_metallic_normal(hit, ray);
	else if (roughness > 0)
		v = get_roughness_normal(hit, roughness, ray);
	return (v);
}

t_vector	get_metallic_normal(t_hit hit, t_ray ray)
{
	t_vector	v;

	v = vreflect(ray.orientation, hit.normal);
	return (vnormalize(v));
}

t_vector	get_roughness_normal(t_hit hit, float roughness, t_ray ray)
{
	t_vector	v;

	(void) ray;
	(void) roughness;
	(void) hit;

	v = vsmul(hit.normal, -1);
	while (vdot(hit.normal, v) < 0)
	{
		v = random_unit_vector();
		v = vadd(hit.normal, vsmul(v, roughness));
		if (random_float_range(0, 1) > pow(roughness, 2))
			v = vreflect(ray.orientation, v);
	}
	return (vnormalize(v));
}

int	get_material_id(t_data *data, t_hit hit)
{
	if (hit.shape == OBJ_SPHERE)
		return (data->spheres[hit.i].material_id);
	if (hit.shape == OBJ_CYL)
		return (data->cylinders[hit.i].material_id);
	if (hit.shape == OBJ_PLANE)
		return (data->planes[hit.i].material_id);
	if (hit.shape == OBJ_TRIANGLE)
		return (data->triangles[hit.i].material_id);
	return (-1);
}

float	get_roughness_factor(t_data *data, t_hit hit)
{
	int	i;
	int	id;

	i = 0;
	id = get_material_id(data, hit);
	if (id == -1)
		return (0);
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
			return (data->materials[i].metallic);
		i++;
	}
	return (1);
}

float	get_emissive_ratio(t_data *data, t_hit hit)
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
			return (data->materials[i].emissive_ratio);
		i++;
	}
	return (0);
}

t_vector	get_material_color(t_data *data, t_hit hit)
{
	int	i;
	int	id;

	i = 0;
	id = get_material_id(data, hit);
	if (id == -1)
		return (black_color());
	while (i < data->num_materials)
	{
		if (data->materials[i].id == id)
			return (data->materials[i].color);
		i++;
	}
	return (black_color());
}
