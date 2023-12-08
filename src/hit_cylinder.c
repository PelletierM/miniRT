/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:30:35 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 11:00:31 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	get_cyl_t(t_quadratic s, t_cylinder cy, t_ray ray, int *flag);
float	get_disk_t(t_cylinder cy, t_ray ray, int *flag);

float	check_hit_cylinders(t_cylinder cy, t_ray ray, int *flag)
{
	t_quadratic	s_cyl;

	s_cyl = solve_quadratic_cylinder(cy, ray);
	*flag = 4;
	if (s_cyl.dis < 0)
		return (0);
	return (get_cyl_t(s_cyl, cy, ray, flag));
}

float	get_cyl_t(t_quadratic s_cyl, t_cylinder cy, t_ray ray, int *flag)
{
	float		m1;
	float		m2;
	t_vector	x;

	x = vsub(ray.position, cy.position);
	if (s_cyl.t1 > 0 && s_cyl.t2 > 0)
	{
		m2 = vdot(ray.orientation, cy.orientation) * s_cyl.t2 + vdot(
				x, cy.orientation);
		if (m2 >= 0 && m2 <= cy.height)
			return (s_cyl.t2);
		return (get_disk_t(cy, ray, flag));
	}
	else
	{
		m1 = vdot(ray.orientation, cy.orientation) * s_cyl.t1 + vdot(
				x, cy.orientation);
		if (m1 >= 0 && m1 <= cy.height)
		{
			*flag = 3;
			return (s_cyl.t1);
		}
		return (get_disk_t(cy, ray, flag));
	}
	return (0);
}

float	get_disk_t(t_cylinder cy, t_ray ray, int *flag)
{
	float		t3;
	float		t4;
	t_vector	hit_pos;

	t3 = check_hit_planes(cy.bottom, ray);
	t4 = check_hit_planes(cy.top, ray);
	if (t3 < t4)
	{
		hit_pos = vadd(ray.position, vsmul(ray.orientation, t3));
		if (vdistance(hit_pos, cy.bottom.position) <= cy.diameter / 2)
		{
			*flag = 1;
			return (t3);
		}
	}
	else
	{
		hit_pos = vadd(ray.position, vsmul(ray.orientation, t4));
		if (vdistance(hit_pos, cy.top.position) <= cy.diameter / 2)
		{
			*flag = 2;
			return (t4);
		}
	}
	return (0);
}
