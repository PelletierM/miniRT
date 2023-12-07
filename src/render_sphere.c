/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/07 16:25:11 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	get_closest_t_value(float a, float b, float dis);

float	check_hit_sphere(t_sphere sp, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	float	dis;

	a = vdot(ray.orientation, ray.orientation);
	b = vdot(vsmul(ray.orientation,
				(float) 2), vsub(ray.position, sp.position));
	c = vdot(vsub(ray.position, sp.position),
			vsub(ray.position, sp.position)) - powf(sp.diameter / 2, 2);

	dis = sqrt(powf(b, 2) - 4 * a * c);
	if (dis < 0 )
		return (0);
	if (dis == 0)
		return (-b / (2 * a));
	return (get_closest_t_value(a, b, dis));
}

float get_closest_t_value(float a, float b, float dis)
{
	float	t1;
	float	t2;

	t1 = (-b + dis) / (2 *a);
	t2 = (-b - dis) / (2 *a);
	if (t1 > 0 && t2 > 0)
		return (t2);
	return (t1);
}

float	check_hit_cylinders(t_cylinder cy, t_ray ray, int *flag)
{
	float		a;
	float		b;
	float		c;
	float		dis;
	t_vector	x;
	float		m1;
	float		m2;
	float 		t1;
	float 		t2;
	float 		t3;
	float 		t4;

	x = vsub(ray.position, cy.position);
	a = vdot(ray.orientation, ray.orientation) - pow(vdot(ray.orientation, cy.orientation), 2);
	b = 2 * (vdot(ray.orientation, x) - vdot(ray.orientation, cy.orientation) * vdot(x, cy.orientation));
	c = vdot(x, x) - pow(vdot(x, cy.orientation), 2) - pow(cy.diameter / 2, 2);

	dis = powf(b, 2) - 4 * a * c;
	if (dis < 0 )
		return (0);
	t1 = (-b + sqrt(dis)) / (2 *a);
	t2 = (-b - sqrt(dis)) / (2 *a);
	x = vsub(ray.position, cy.position);
	m1 = vdot(ray.orientation, cy.orientation) * t1 + vdot(x, cy.orientation);
	m2 = vdot(ray.orientation, cy.orientation) * t2 + vdot(x, cy.orientation);
	t3 = check_hit_planes(cy.bottom, ray);
	t4 = check_hit_planes(cy.top, ray);
	if (t1 > 0 && t2 > 0)
	{
		if (m2 >= 0 && m2 <= cy.height)
		{
			*flag = 4;
			return (t2);
		}
		if (t3 < t4)
		{
			t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, t3));
			if (vdistance(hit_pos, cy.bottom.position) <= cy.diameter / 2)
			{
				*flag = 1;
				return (t3);
			}
		}
		else
		{
			t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, t4));
			if (vdistance(hit_pos, cy.top.position) <= cy.diameter / 2)
			{
				*flag = 2;
				return (t4);
			}
		}
	}
	else
	{
		if (m1 >= 0 && m1 <= cy.height)
		{
			*flag = 3;
			return (t1);
		}
		if (t3 < t4)
		{
			t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, t3));
			if (vdistance(hit_pos, cy.bottom.position) <= cy.diameter / 2)
			{
				*flag = 1;
				return (t3);
			}
		}
		else
		{
			t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, t4));
			if (vdistance(hit_pos, cy.top.position) <= cy.diameter / 2)
			{
				*flag = 2;
				return (t4);
			}
		}
	}
	return (0);
}
