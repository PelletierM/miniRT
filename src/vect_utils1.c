/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 07:41:54 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/11 13:20:26 by eguefif          ###   ########.fr       */
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

t_vector	translate_point(t_vector position, float t, t_vector orientation)
{
	t_vector	translation;

	translation = vsmul(orientation, t);
	position = vadd(position, translation);
	return (position);
}

t_vector	create_vector_from_points(t_vector p1, t_vector p2)
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

t_vector	rotate_figure(t_vector target, t_vector axe, int direction)
{
	t_vector	retval;
	float		cs;
	float		sn;

	cs = cosf((float) CAM_ROT_ANGLE);
	sn = sinf((float) CAM_ROT_ANGLE);
	sn *= direction;
	retval = vadd(vsadd(vsmul(target, cs),
		   vdot(target, axe) * (1 - cs)),
			vsmul(vcross(axe, target), sn));
	return (retval);
}
