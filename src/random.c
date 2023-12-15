/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:15:21 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/14 16:20:24 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/*
uint32_t rand_32(uint32_t seed)
{
	uint32_t	tmp1;
	uint32_t	tmp2;

	tmp1 = seed * 747796405 + 2891336453;
	tmp2 = ((tmp1 >> ((tmp1 >> 28) + 4)) ^ tmp1) * 277803737;
	return ((tmp2 >> 22) ^ tmp2);
}
*/

/*
uint64_t rand_64(uint64_t seed)
{
	uint64_t i;

	i = 0x9FB21C651E98DF25;

	seed ^= ((seed << 49) | (seed >> 15)) ^ ((seed << 24) | (seed >> 40));
	seed *= i;
	seed ^= seed >> 35;
	seed *= i;
	seed ^= seed >> 28;

	return seed;
}
*/

float	random_float()
{
	return ((float) rand() / RAND_MAX);
}

float	random_float_range(float min, float max)
{
	return min + (max - min) * random_float();
}

t_vector	vrandom()
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
	return  (v);
}

t_vector	random_in_unit_sphere()
{
	t_vector	v;
	while (true)
	{
		v = vrandom_range(-1, 1);
			if (vlength_squared(v) < 1)
		return (v);
	}
}

t_vector	random_unit_vector()
{
	return (vnormalize(random_in_unit_sphere()));
}
