/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:35:05 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 09:12:56 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_quadratic	solve_quadratic_cylinder(t_cylinder cy, t_ray ray)
{
	t_vector	x;
	t_quadratic	s_cyl;
	float		a;
	float		b;
	float		c;

	x = vsub(ray.position, cy.position);
	a = vdot(ray.orientation, ray.orientation) - pow(
			vdot(ray.orientation, cy.orientation), 2);
	b = 2 * (vdot(ray.orientation, x) - vdot(
				ray.orientation, cy.orientation) * vdot(x, cy.orientation));
	c = vdot(x, x) - pow(vdot(
				x, cy.orientation), 2) - pow(cy.diameter / 2, 2);
	s_cyl.dis = powf(b, 2) - 4 * a * c;
	if (s_cyl.dis < 0)
		return (s_cyl);
	s_cyl.t1 = (-b + sqrt(s_cyl.dis)) / (2 * a);
	s_cyl.t2 = (-b - sqrt(s_cyl.dis)) / (2 * a);
	return (s_cyl);
}

t_quadratic	solve_quadratic_sphere(t_sphere sp, t_ray ray)
{
	float		a;
	float		b;
	float		c;
	t_quadratic	s;

	a = vdot(ray.orientation, ray.orientation);
	b = vdot(vsmul(ray.orientation,
				(float) 2), vsub(ray.position, sp.position));
	c = vdot(vsub(ray.position, sp.position),
			vsub(ray.position, sp.position)) - powf(sp.diameter / 2, 2);
	s.dis = sqrt(powf(b, 2) - 4 * a * c);
	if (s.dis < 0)
		return (s);
	s.t1 = (-b + s.dis) / (2 * a);
	s.t2 = (-b - s.dis) / (2 * a);
	return (s);
}
