/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:08:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 11:27:39 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_camera(char *line, t_data *data)
{
	line++;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->camera.position))
		return (1);
	line = skip_double(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->camera.orientation))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->camera.fov = get_double(line);
	line = skip_double(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	return (0);
}
