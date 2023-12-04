/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:54:44 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 13:05:10 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_cylinder_part(char *line, t_data *data, int num);

// coord - coord - ratio - ratio - coord
int	set_cylinder(char *line, t_data *data, int num)
{
	line += 2;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->cylinders[num].position))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->cylinders[num].orientation))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	return (set_cylinder_part(line, data, num));
}

int	set_cylinder_part(char *line, t_data *data, int num)
{
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->cylinders[num].diameter = get_double(line);
	line = skip_double(line);
	line = skip_spaces(line);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->cylinders[num].height = get_double(line);
	line = skip_double(line);
	line = skip_spaces(line);
	if (get_coord(line, &data->cylinders[num].color))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	return (0);
}
