/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:34:59 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 15:34:57 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_sphere(char *line, t_data *data)
{
	line += 2;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->spheres[data->num_spheres].position))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->spheres[data->num_spheres].diameter = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	if (get_coord(line, &data->spheres[data->num_spheres].color))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->num_spheres++;
	return (0);
}
