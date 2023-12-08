/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 07:41:54 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 10:54:31 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	vcopy(t_vector v)
{
	t_vector	cpy;

	cpy.x = v.x;
	cpy.y = v.y;
	cpy.z = v.z;
	return (cpy);
}

t_vector	translate_point(t_vector position,
								float t,
								t_vector orientation)
{
	t_vector	translation;

	translation = vsmul(orientation, t);
	position = vadd(position, translation);
	return (position);
}

t_vector	create_v_from_points(t_vector p1, t_vector p2)
{
	t_vector	retval;

	retval = vsub(p2, p1);
	return (retval);
}

float	vlength(t_vector v1)
{
	return (sqrt(vdot(v1, v1)));
}

float	vdistance(t_vector v1, t_vector v2)
{
	return (sqrt(pow(v1.x - v2.x, 2) + pow(
				v1.y - v2.y, 2) + pow(v1.z - v2.z, 2)));
}

int	is_vect_negative(t_vector vector)
{
	return (vector.x < 0 || vector.y < 0 || vector.z < 0);
}