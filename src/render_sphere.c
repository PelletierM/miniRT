/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/05 16:44:31 by eguefif          ###   ########.fr       */
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

	a = op_vect_dot(ray.orientation, ray.orientation);
	b = op_vect_dot(op_vect_scalar_mul(ray.orientation,
				(float) 2), op_vect_sub(ray.position, sp.position));
	c = op_vect_dot(op_vect_sub(ray.position, sp.position),
			op_vect_sub(ray.position, sp.position)) - powf(sp.diameter / 2, 2);

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
	if (t1 < 0 && t2 < 0)
		return (t2);
	else if (t2 < 0)
		return (t2);
	return (t1);
}

	/*
Our formula to get a, b,c.
a = powf(ray.orientation.x, 2) + pow(ray.orientation.y, 2) + powf(ray.orientation.z, 2);
b = 2 * (ray.position.x * ray.orientation.x - sp.position.x * ray.orientation.x +
	ray.position.y * ray.orientation.y - sp.position.y * ray.orientation.y +
	ray.position.z * ray.orientation.z - sp.position.z * ray.orientation.z);
c = (powf(ray.position.x, 2) - 2 * (ray.position.x * sp.position.x) + powf(sp.position.x, 2) +
powf(ray.position.y, 2) - 2 * (ray.position.y * sp.position.y)  + powf(sp.position.y, 2) +
powf(ray.position.z, 2) - 2 * (ray.position.z * sp.position.z)  + powf(sp.position.z, 2) - 
															powf(sp.diameter / 2, 2));
			*/
