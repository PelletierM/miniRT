/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vectors2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:45:20 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/05 10:03:25 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	op_vect_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	op_vect_sub(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	op_vect_mul(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}

t_vector	op_vect_scalar_mul(t_vector v1, float factor)
{
	t_vector	result;

	result.x = v1.x * factor;
	result.y = v1.y * factor;
	result.z = v1.z * factor;
	return (result);
}

t_vector	op_vect_scalar_div(t_vector v1, float factor)
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
