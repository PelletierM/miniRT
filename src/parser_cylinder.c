/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:54:44 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/07 11:56:17 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_cylinder_part(char *line, t_data *data);

int	set_cylinder(char *line, t_data *data)
{
	line += 2;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->cylinders[data->num_cylinders].position))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->cylinders[data->num_cylinders].orientation))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	data->cylinders[data->num_cylinders].orientation = vnormalize(
			data->cylinders[data->num_cylinders].orientation);
	if (!*line)
		return (1);
	data->num_cylinders++;
	data->cylinders[data->num_cylinders].bottom.position = vcopy(
				data->cylinders[data->num_cylinders].position);
	
	data->cylinders[data->num_cylinders].bottom.orientation = vsmul(
			data->cylinders[data->num_cylinders].orientation, -1);

	data->cylinders[data->num_cylinders].top.orientation = vsmul(
			data->cylinders[data->num_cylinders].orientation, 1);

	data->cylinders[data->num_cylinders].top.position = translate_point(
			data->cylinders[data->num_cylinders].position,
			data->cylinders[data->num_cylinders].height,
			data->cylinders[data->num_cylinders].orientation);
	printf("Cyl: %f %f %f %f %f %f\n",
			data->cylinders[data->num_cylinders].position.x,
			data->cylinders[data->num_cylinders].position.y,
			data->cylinders[data->num_cylinders].position.z,
			data->cylinders[data->num_cylinders].orientation.z,
			data->cylinders[data->num_cylinders].orientation.z,
			data->cylinders[data->num_cylinders].orientation.z);
	printf("top: %f %f %f, %f %f %f\n",
			data->cylinders[data->num_cylinders].top.position.x,
			data->cylinders[data->num_cylinders].top.position.y,
			data->cylinders[data->num_cylinders].top.position.z,
			data->cylinders[data->num_cylinders].top.orientation.z,
			data->cylinders[data->num_cylinders].top.orientation.z,
			data->cylinders[data->num_cylinders].top.orientation.z);
	printf("bot: %f %f %f, %f %f %f\n",
			data->cylinders[data->num_cylinders].bottom.position.x,
			data->cylinders[data->num_cylinders].bottom.position.y,
			data->cylinders[data->num_cylinders].bottom.position.z,
			data->cylinders[data->num_cylinders].bottom.orientation.z,
			data->cylinders[data->num_cylinders].bottom.orientation.z,
			data->cylinders[data->num_cylinders].bottom.orientation.z);
	return (set_cylinder_part(line, data));
}

int	set_cylinder_part(char *line, t_data *data)
{
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->cylinders[data->num_cylinders].diameter = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->cylinders[data->num_cylinders].height = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	if (get_coord(line, &data->cylinders[data->num_cylinders].color))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);

	return (0);
}
