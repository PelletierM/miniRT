/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 07:41:54 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/13 17:47:54 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	is_vect_negative(t_vector vector)
{
	return (vector.x < 0 || vector.y < 0 || vector.z < 0);
}

t_vector	rotate_figure(t_vector target, t_vector axe, int direction)
{
	t_vector	retval;
	float		cs;
	float		sn;

	cs = cosf((float) OBJ_ROT_ANGLE);
	sn = sinf((float) OBJ_ROT_ANGLE);
	sn *= direction;
	retval = vadd(vsadd(vsmul(target, cs),
				vdot(target, axe) * (1 - cs)),
			vsmul(vcross(axe, target), sn));
	return (retval);
}

t_vector	vreflect(t_vector ray, t_vector normal)
{
	return (vsub(ray, vsmul(normal, (float) 2.0 * vdot(ray, normal))));
}

float	vlength_squared(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
