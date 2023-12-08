/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:47:59 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/08 11:58:04 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	cap_fov(float fov)
{
	if (fov < 0.00174533)
		fov = 0.00174533;
	if (fov > 3.1241394)
		fov = 3.1241394;
	return (fov);
}

t_vector	cap_axis_y(t_vector v)
{
	t_vector	tmp;
	int			sign;

	sign = v.y < 0;
	if (v.y > 0.996 || v.y < -0.996)
	{
		v.y = -0.996 * sign + 0.996 * !sign;
		if (v.z != 0 || v.x != 0)
		{
			tmp.x = v.x;
			tmp.z = v.z;
			tmp.y = 0;
			tmp = vsmul(vnormalize(tmp), 0.089);
			v.x = tmp.x;
			v.z = tmp.z;
		}
		else
		{
			v.z = 0.089;
			v.x = 0;
		}
	}
	v = vnormalize(v);
	return (v);
}
