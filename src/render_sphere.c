/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/07 11:43:40 by eguefif          ###   ########.fr       */
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

	x = vsub(ray.position, cy.position);
	a = vdot(ray.orientation, ray.orientation) - pow(vdot(ray.orientation, cy.orientation), 2);
	b = 2 * (vdot(ray.orientation, x) - vdot(ray.orientation, cy.orientation) * vdot(x, cy.orientation));
	c = vdot(x, x) - pow(vdot(x, cy.orientation), 2) - pow(cy.diameter / 2, 2);

	dis = powf(b, 2) - 4 * a * c;
	if (dis < 0 )
		return (0);
	if (dis == 0)
		return (-b / (2 * a));
	t1 = (-b + sqrt(dis)) / (2 *a);
	t2 = (-b - sqrt(dis)) / (2 *a);
	x = vsub(ray.position, cy.position);
	m1 = vdot(ray.orientation, vsmul(cy.orientation, t1)) + vdot(x, cy.orientation);
	m2 = vdot(ray.orientation, vsmul(cy.orientation, t2)) + vdot(x, cy.orientation);
	if (m1 >= 0 && m1 <= cy.height)
		return (t1);
	if (m2 >= 0 && m2 <= cy.height)
		return (t2);
	/*
	printf("%f %f %f, %f %f %f\n",
			cy.top.position.x,
			cy.top.position.y,
			cy.top.position.z,
			cy.top.orientation.z,
			cy.top.orientation.z,
			cy.top.orientation.z);
	printf("%f %f %f, %f %f %f\n",
			cy.bottom.position.x,
			cy.bottom.position.y,
			cy.bottom.position.z,
			cy.bottom.orientation.z,
			cy.bottom.orientation.z,
			cy.bottom.orientation.z);
			*/
	t1 = check_hit_planes(cy.bottom, ray);
	t2 = check_hit_planes(cy.top, ray);
	if (t1)
	{
		*flag = 1;
		t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, t1));
		if (vdistance(hit_pos, cy.bottom.position) < cy.diameter)
			return (t1);
	}
	else if (t2)
	{
		*flag = 2;
		t_vector hit_pos = vadd(ray.position, vsmul(ray.orientation, t2));
		if (vdistance(hit_pos, cy.top.position) < cy.diameter)
			return (t2);
	}
	return (0);
}
