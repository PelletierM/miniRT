/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:23:36 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 11:08:25 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	calculate_area(t_vector p1, t_vector p2, t_vector p3);
float 	get_triangle_t(t_triangle triangle, t_ray ray);
int		is_in_triangle(t_triangle tr, t_vector pt);

void	check_triangle_hit(t_data *data, t_ray ray, t_hit *hit)
{
	float	t;
	int		i;
	i = 0;
	while(i < data->num_triangles)
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

float get_triangle_t(t_triangle triangle, t_ray ray)
{
	t_plane	pl;
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
	float		area;
	float		a1;
	float		a2;
	float		a3;

	//printf("triangle: %f %f %f\n", tr.c1.x, tr.c1.y, tr.c1.z);
	//printf("triangle: %f %f %f\n", tr.c2.x, tr.c2.y, tr.c2.z);
	//printf("triangle: %f %f %f\n", tr.c3.x, tr.c3.y, tr.c3.z);
	area = calculate_area(tr.c1, tr.c2, tr.c3);
	a1 = calculate_area(tr.c1, tr.c2, pt);
	a2 = calculate_area(tr.c3, tr.c2, pt);
	a3 = calculate_area(tr.c1, tr.c3, pt);
	//printf("%f != %f\n", area, a1+a2+a3);
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
	//printf("cross: %f %f %f\n", c.x, c.y, c.z);
	//printf("edge1: %f %f %f\n", edge1.x, edge2.y, edge1.z);
	//printf("edge2: %f %f %f\n", edge2.y, edge2.y, edge2.z);
	//printf("%f\n", vcross(edge1, edge2).z);
	return (vlength(vcross(edge1, edge2)) / 2);
}
