/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:15:21 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/18 14:19:42 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	random_float(void)
{
	return ((float) rand() / RAND_MAX);
}

float	random_float_range(float min, float max)
{
	return (min + (max - min) * random_float());
}

t_vector	vrandom(void)
{
	t_vector	v;

	v.x = random_float();
	v.y = random_float();
	v.z = random_float();
	return (v);
}

t_vector	vrandom_range(float min, float max)
{
	t_vector	v;

	v.x = random_float_range(min, max);
	v.y = random_float_range(min, max);
	v.z = random_float_range(min, max);
	return (v);
}

t_vector	random_unit_vector(void)
{
	t_vector	v;
	while (true)
	{
		v = vrandom_range(-1, 1);
		if (vlength_squared(v) < 1)
			break ;
	}
	return (vnormalize(v));
}
