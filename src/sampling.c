/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:01:33 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/14 09:10:55 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	update_color(t_data *data, t_vector color, int x, int y, int start)
{
	t_vector new_color;

	data->accumulator[y * data->width + x + start] = vadd(
			data->accumulator[y * data->width + x + start], color);
	new_color = vsdiv(data->accumulator[y * data->width + x + start],
			data->samples);
	return (new_color);
}
