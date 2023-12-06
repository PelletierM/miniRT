/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vectors1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:10:26 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/06 10:20:53 by eguefif          ###   ########.fr       */
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
