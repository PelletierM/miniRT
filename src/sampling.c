/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:01:33 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/14 09:45:27 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	update_color(t_data *data, t_vector color, int x, int y)
{
	t_vector new_color;

	data->accumulator[y * data->width + x] = vadd(
			data->accumulator[y * data->width + x], color);
	new_color = vsdiv(data->accumulator[y * data->width + x],
			data->samples);
	return (new_color);
}
