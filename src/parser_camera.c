/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:08:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 11:20:35 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_camera2(char *line, t_data *data);

int	set_camera(char *line, t_data *data)
{
	if (data->flag & 2)
		return (1);
	line++;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->camera.position))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->camera.z_axis))
		return (1);
	data->camera.z_axis = vnormalize(data->camera.z_axis);
	return (set_camera2(line, data));
}

int	set_camera2(char *line, t_data *data)
{
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->camera.fov = M_PI * get_float(line) / 180;
	line = skip_float(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->flag += 2;
	data->camera.mv_flag = 0;
	return (0);
}
