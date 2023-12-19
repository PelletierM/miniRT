/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:17:58 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/19 10:16:00 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_spheres_hit(t_data *data, t_ray ray, t_hit *hit);
void	check_planes_hit(t_data *data, t_ray ray, t_hit *hit);
void	check_cylinders_hit(t_data *data, t_ray ray, t_hit *hit);

t_hit	get_closest_hit(t_data *data, t_ray ray)
{
	t_hit	hit;

	hit.t = MAX_DIST;
	hit.i = 0;
	check_spheres_hit(data, ray, &hit);
	check_cylinders_hit(data, ray, &hit);
	check_planes_hit(data, ray, &hit);
	check_triangle_hit(data, ray, &hit);
	return (hit);
}

void	check_spheres_hit(t_data *data, t_ray ray, t_hit *hit)
{
	int		i;
	float	t;

	i = 0;
	while (i < data->num_spheres)
	{
		t = check_hit_sphere(data->spheres[i], ray, hit);
		if (t > 0 && t < hit->t)
		{
			hit->color = vcopy(data->spheres[i].color);
			hit->t = t;
			hit->shape = OBJ_SPHERE;
			hit->i = i;
		}
		i++;
	}
}

void	check_planes_hit(t_data *data, t_ray ray, t_hit *hit)
{
	int		i;
	float	t;

	i = 0;
	while (i < data->num_planes)
	{
		t = check_hit_planes(data->planes[i], ray);
		if (t > 0 && t < hit->t)
		{
			hit->color = vcopy(data->planes[i].color);
			hit->t = t;
			hit->shape = OBJ_PLANE;
			hit->i = i;
		}
		i++;
	}
}

void	check_cylinders_hit(t_data *data, t_ray ray, t_hit *hit)
{
	int		i;
	float	t;
	int		flag;

	i = 0;
	flag = 4;
	while (i < data->num_cylinders)
	{
		t = check_hit_cylinders(data->cylinders[i], ray, &flag);
		if (t > 0 && t < hit->t)
		{
			hit->color = vcopy(data->cylinders[i].color);
			hit->t = t;
			hit->shape = OBJ_CYL;
			hit->i = i;
			hit->flag = flag;
		}
		i++;
	}
}
