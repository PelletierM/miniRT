/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:51:30 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/18 14:15:53 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	set_plane_2(char *line, t_data *data);

int	set_plane(char *line, t_data *data)
{
	line += 2;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->planes[data->num_planes].position))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->planes[data->num_planes].orientation))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	data->planes[data->num_planes].orientation = vnormalize(
			data->planes[data->num_planes].orientation);
	return (set_plane_2(line, data));
}

int	set_plane_2(char *line, t_data *data)
{
	if (!*line)
		return (1);
	data->planes[data->num_planes].material_id = ft_atoi(line);
	if (*line == '+' || *line == '-')
		line++;
	line = skip_digits(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->num_planes++;
	return (0);
}
