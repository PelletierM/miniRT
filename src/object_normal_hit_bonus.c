/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normal_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:38:22 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 10:56:36 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	get_normal_cylinder(t_hit *hit, t_ray ray, t_data *data);
void	get_normal_spheres(t_hit *hit, t_data *data);

void	get_normal_hit(t_data *data, t_ray ray, t_hit *hit)
{
	hit->position = vadd(ray.position, vsmul(ray.orientation, hit->t));
	if (hit->shape == OBJ_SPHERE)
		get_normal_spheres(hit, data);
	if (hit->shape == OBJ_TRIANGLE)
	{
		hit->normal = vcopy(data->triangles[hit->i].normal);
		if (vdot(hit->normal, ray.orientation) < 0)
			hit->normal = vcopy(hit->normal);
		else
			hit->normal = vsmul(hit->normal, -1);
	}
	else if (hit->shape == OBJ_PLANE)
	{
		hit->normal = vcopy(data->planes[hit->i].orientation);
		if (vdot(data->planes[hit->i].orientation, ray.orientation) < 0)
			hit->normal = vcopy(data->planes[hit->i].orientation);
		else
			hit->normal = vsmul(data->planes[hit->i].orientation, -1);
	}
	else if (hit->shape == OBJ_CYL)
		get_normal_cylinder(hit, ray, data);
}

void	get_normal_spheres(t_hit *hit, t_data *data)
{
	hit->normal = vsub(hit->position, data->spheres[hit->i].position);
	hit->normal = vsdiv(hit->normal, data->spheres[hit->i].diameter / 2);
	if (hit->pos_hit_number == 1)
		hit->normal = vsmul(hit->normal, -1);
}

void	get_normal_cylinder(t_hit *hit, t_ray ray, t_data *data)
{
	t_vector	x;
	float		m;

	if (hit->flag == 1)
		hit->normal = data->cylinders[hit->i].bottom.orientation;
	else if (hit->flag == 2)
		hit->normal = data->cylinders[hit->i].top.orientation;
	else
	{
		x = vsub(ray.position, data->cylinders[hit->i].position);
		m = vdot(ray.orientation, vsmul(
					data->cylinders[hit->i].orientation, hit->t)) + vdot(
				x, data->cylinders[hit->i].orientation);
		hit->normal = vnormalize(
				(vsub(hit->position, vadd(
							data->cylinders[hit->i].position, vsmul(
								data->cylinders[hit->i].orientation, m)))));
		if (hit->flag == 3)
			hit->normal = vsmul(hit->normal, -1);
	}
}
