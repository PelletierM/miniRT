/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 09:56:19 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/15 15:30:32 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_path(char line);

int	set_material(char *line, t_data *data)
{
	char	**splits;
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
	get_color(line, &data->materials[data->num_materials].color);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line && *line == '\n')
		return (1);
	line = ft_strtrim(line, "\n ");
	splits = ft_split(line, ' ');
	if (ft_strlen(splits[0]) > MAX_CHAR_PATH)
	{
		ft_cleansplits(splits);
		return (1);
	}
	if (ft_strncmp(splits[0], "none", MAX_CHAR_PATH) != 0)
	{
		data->materials[data->num_materials].texture_flag = 1;
		data->materials[data->num_materials].img = mlx_load_png(splits[0]);
		if (!data->materials[data->num_materials].img)
		{
			ft_dprintf(2, "ERROR:\nTexture loading error\n");
			return (1);
		}
	}
	if (!splits[1] || ft_strlen(splits[1]) > MAX_CHAR_PATH || ft_strlen(splits[1]) == 0)
	{
		ft_cleansplits(splits);
		return (1);
	}
	if (ft_strncmp(splits[1], "none", MAX_CHAR_PATH) != 0)
	{
		data->materials[data->num_materials].norm_img = mlx_load_png(splits[1]);
		if (!data->materials[data->num_materials].norm_img)
		{
			ft_dprintf(2, "ERROR:\nTexture loading error\n");
			return (1);
		}
	}
	data->num_materials++;
	ft_cleansplits(splits);
	return (0);
}

int	is_path(char line)
{
	return (ft_isalpha(line) || line == '.' || line == '/');
}
