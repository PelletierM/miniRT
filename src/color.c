/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:39:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/01 14:04:17 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
