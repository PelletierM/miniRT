/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:13:42 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 09:14:09 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
