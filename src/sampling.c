/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:01:33 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/12 17:19:28 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	update_color(int samples, t_vector color, t_vector color_old)
{
	t_vector new_color;
	color = vsmul(color, (float) 1 / (float) (samples + 1));
	color_old = vsmul(color_old, (float) samples / (float) (samples + 1));
	new_color = vadd(color, color_old);
	new_color = clamp_color(new_color);
	return (new_color);
}
