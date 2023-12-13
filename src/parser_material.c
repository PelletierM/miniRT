/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:56:19 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/13 10:44:13 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_material(char *line, t_data *data)
{
	line += 2;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->materials[data->num_materials].id = ft_atoi(line);
	line = skip_digits(line);
	line = skip_spaces(line);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->materials[data->num_materials].roughness = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->materials[data->num_materials].metalic = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->num_materials++;
	return (0);
}
