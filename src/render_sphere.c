/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/06 15:32:41 by eguefif          ###   ########.fr       */
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

float	check_hit_cylinders(t_cylinder cy, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	float	dis;
	t_vector	x;

	x = vsub(ray.position, cy.position);
	a = vdot(ray.orientation, ray.orientation) - pow(vdot(ray.orientation, cy.orientation), 2);
	b = 2 * (vdot(ray.orientation, x) - vdot(ray.orientation, cy.position) * vdot(x, cy.orientation));
	c = vdot(x, x) - pow(vdot(x, cy.orientation), 2) - pow(cy.diameter / 2, 2);

	dis = sqrt(powf(b, 2) - 4 * a * c);
	if (dis < 0 )
		return (0);
	if (dis == 0)
		return (-b / (2 * a));
	return (get_closest_t_value(a, b, dis));
}
