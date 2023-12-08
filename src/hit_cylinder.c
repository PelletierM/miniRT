/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:30:35 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 12:57:04 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	get_cyl_t(t_quadratic s, t_cylinder cy, t_ray ray, int *flag);
float	get_disk_t(t_cylinder cy, t_ray ray, int *flag);
float	get_hit_disk(t_plane plane, float r, t_ray ray);
float	get_t_from_inside(t_cylinder cy, float t1, t_ray ray, int *flag);

float	check_hit_cylinders(t_cylinder cy, t_ray ray, int *flag)
{
	t_quadratic	s_cyl;

	s_cyl = solve_quadratic_cylinder(cy, ray);
	if (s_cyl.dis < 0)
		return (0);
	return (get_cyl_t(s_cyl, cy, ray, flag));
}

float	get_cyl_t(t_quadratic s_cyl, t_cylinder cy, t_ray ray, int *flag)
{
	float		m;
	t_vector	x;

	x = vsub(ray.position, cy.position);
	if (s_cyl.t2 > 0 && s_cyl.t1 > 0)
	{
		*flag = 4;
		m = vdot(ray.orientation, cy.orientation) * s_cyl.t2 + vdot(
				x, cy.orientation);
		if (m > 0 && m < cy.height)
			return (s_cyl.t2);
		return (get_disk_t(cy, ray, flag));
	}
	else if (s_cyl.t1 > 0)
		return (get_t_from_inside(cy, s_cyl.t1, ray, flag));
	return (0);
}

float	get_t_from_inside(t_cylinder cy, float t1, t_ray ray, int *flag)
{
	float		t3;
	float		t4;
	float		m;
	t_vector	x;

	x = vsub(ray.position, cy.position);
	t3 = get_hit_disk(cy.bottom, cy.diameter / 2, ray);
	t4 = get_hit_disk(cy.top, cy.diameter / 2, ray);
	if (t3 < t1 && t3 < t4)
	{
		*flag = 1;
		return (t3);
	}
	if (t4 < t1 && t4 < t3)
	{
		*flag = 2;
		return (t4);
	}
	m = vdot(ray.orientation, cy.orientation) * t1 + vdot(
			x, cy.orientation);
	if (m > 0 && m < cy.height)
	{
		*flag = 3;
		return (t1);
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
	if (t3 <= t4)
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

float	get_hit_disk(t_plane p, float r, t_ray ray)
{
	float		t;
	t_vector	hit_pos;

	t = check_hit_planes(p, ray);
	hit_pos = vadd(ray.position, vsmul(ray.orientation, t));
	if (vdistance(hit_pos, p.position) <= r)
		return (t);
	return (MAX_DIST);
}
