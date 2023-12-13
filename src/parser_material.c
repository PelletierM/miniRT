/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:56:19 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/13 16:01:59 by eguefif          ###   ########.fr       */
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
	data->materials[data->num_materials].metallic = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	data->materials[data->num_materials].emissive_ratio = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->num_materials++;
	return (0);
}
