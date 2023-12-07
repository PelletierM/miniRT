/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:54:44 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/07 08:36:33 by eguefif          ###   ########.fr       */
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
	//data->cylinders[data->num_cylinders].orientation = vnormalize(
	//		data->cylinders[data->num_cylinders].orientation);
	if (!*line)
		return (1);
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
	data->num_cylinders++;
	return (0);
}
