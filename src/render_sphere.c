/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/05 13:07:42 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float get_closest_t_value(float a, float b, float dis);

float	check_hit_sphere(t_sphere sp, t_ray ray)
{
	float	a;
	float	b;
	float	c;
	float	dis;

	a = ray.orientation.x + ray.orientation.y + ray.orientation.z;
	b = (ray.position.x * ray.orientation.x - sp.position.x * ray.orientation.x +
			ray.position.y * ray.orientation.y - sp.position.y * ray.orientation.y +
			ray.position.z * ray.orientation.z - sp.position.z * ray.orientation.z);
	c = (pow(ray.position.x, 2) - 2 * (ray.position.x * sp.position.x) + pow(sp.position.x, 2) +
			pow(ray.position.y, 2) - 2 * (ray.position.y * sp.position.y)  + pow(sp.position.y, 2) +
			pow(ray.position.z, 2) - 2 * (ray.position.z * sp.position.z)  + pow(sp.position.z, 2) - pow(sp.diameter / 2, 2));

	dis = sqrt(pow(b, 2) - 4 * a * c);
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
	if (t1 > t2 && t2 > 0)
		return (t2);
	else
		return (t1);
}

	/*
	a = op_vect_dot(ray.orientation, ray.orientation);
	b = 2 * op_vect_dot(ray.position, ray.orientation);
	c = op_vect_dot(ray.position, ray.position) - pow(sp.diameter / 2, 2);
			*/
