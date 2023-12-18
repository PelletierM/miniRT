/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vectors1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:10:26 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/18 10:15:45 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vdot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	vcross(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}

t_vector	vnormalize(t_vector v1)
{
	float		length;

	length = sqrt(vdot(v1, v1));
	return (vsdiv(v1, length));
}

t_vector	vssub(t_vector v1, float factor)
{
	t_vector	result;

	result.x = v1.x - factor;
	result.y = v1.y - factor;
	result.z = v1.z - factor;
	return (result);
}

t_vector	vsdiv(t_vector v1, float factor)
{
	t_vector	result;

	if (factor == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		mrt_error_message(ERR_DIV_ZERO, 0);
		return (result);
	}
	result.x = v1.x / factor;
	result.y = v1.y / factor;
	result.z = v1.z / factor;
	return (result);
}
