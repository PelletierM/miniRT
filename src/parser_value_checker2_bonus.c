/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_value_checker2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:16:32 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/15 15:48:16 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	check_spheres(t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_spheres)
	{
		if (data.spheres[i].diameter <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_planes(t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_planes)
	{
		if (check_normalized_vector(data.planes[i].orientation))
			return (1);
		i++;
	}
	return (0);
}

int	check_cylinders(t_data data)
{
	int	i;

	i = 0;
	while (i < data.num_cylinders)
	{
		if (data.cylinders[i].diameter <= 0)
			return (1);
		if (data.cylinders[i].height <= 0)
			return (1);
		if (check_normalized_vector(data.cylinders[i].orientation))
			return (1);
		i++;
	}
	return (0);
}

int	check_color(t_vector color)
{
	if (color.x < 0 || color.x > 1)
		return (1);
	if (color.y < 0 || color.y > 1)
		return (1);
	if (color.z < 0 || color.z > 1)
		return (1);
	return (0);
}

int	check_normalized_vector(t_vector vector)
{
	if (vector.x < -1 || vector.x > 1)
		return (1);
	if (vector.y < -1 || vector.y > 1)
		return (1);
	if (vector.z < -1 || vector.z > 1)
		return (1);
	return (0);
}
