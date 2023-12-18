/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:23:36 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 14:31:08 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	calculate_area(t_vector p1, t_vector p2, t_vector p3);
float	get_triangle_t(t_triangle triangle, t_ray ray);
int		is_in_triangle(t_triangle tr, t_vector pt);

void	check_triangle_hit(t_data *data, t_ray ray, t_hit *hit)
{
	float	t;
	int		i;

	i = 0;
	while (i < data->num_triangles)
	{
		t = get_triangle_t(data->triangles[i], ray);
		if (t > 0 && t < hit->t)
		{
			hit->t = t;
			hit->shape = OBJ_TRIANGLE;
			hit->i = i;
		}
		i++;
	}
}

float	get_triangle_t(t_triangle triangle, t_ray ray)
{
	t_plane		pl;
	t_vector	position;
	float		t;

	pl.position = vcopy(triangle.c1);
	pl.orientation = vcopy(triangle.normal);
	t = check_hit_planes(pl, ray);
	position = vadd(ray.position, vsmul(ray.orientation, t));
	if (is_in_triangle(triangle, position))
		return (t);
	return (-1);
}

int	is_in_triangle(t_triangle tr, t_vector pt)
{
	float	area;
	float	a1;
	float	a2;
	float	a3;

	area = calculate_area(tr.c1, tr.c2, tr.c3);
	a1 = calculate_area(tr.c1, tr.c2, pt);
	a2 = calculate_area(tr.c3, tr.c2, pt);
	a3 = calculate_area(tr.c1, tr.c3, pt);
	if (a1 + a2 + a3 == area)
		return (1);
	return (0);
}

float	calculate_area(t_vector v1, t_vector v2, t_vector v3)
{
	t_vector	edge1;
	t_vector	edge2;

	edge1 = vsub(v2, v1);
	edge2 = vsub(v3, v1);
	return (vlength(vcross(edge1, edge2)) / 2);
}
