/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:39:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/05 10:54:58 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int	get_vect_rgba(t_vector c)
{
	return (c.x << 24 | c.y << 16 | c.z << 8 | 255);
}

int	get_alpha(unsigned int color)
{
	return ((color >> 24) & 0xFF);
}

int	get_red(unsigned int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_green(unsigned int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_blue(unsigned int color)
{
	return ((color >> 0) & 0xFF);
}
