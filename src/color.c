/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:39:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/12 16:38:54 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int	get_vect_rgba(t_vector c)
{
	return ((int) c.x << 24 | (int) c.y << 16 | (int) c.z << 8 | 255);
}

t_vector	clamp_color(t_vector color)
{
	if (color.x < 0)
		color.x = 0;
	if (color.x > 255)
		color.x = 255;
	if (color.y < 0)
		color.y = 0;
	if (color.y > 255)
		color.y = 255;
	if (color.z < 0)
		color.z = 0;
	if (color.y > 255)
		color.z = 255;
	return (color);
}
