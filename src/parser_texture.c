/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:52:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/14 13:04:41 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_texture(char *line, t_data *data)
{
	char	*splits;

	line += 2;
	if (*line != ' ')
		return (1);
	data->textures[data->num_textures].id = ft_atoi(line);
	line = skip_digits(line);
	line = skip_spaces(line);
	line = ft_strtrim(line, "\n ");
	ft_strncmp(data->textures[data->num_textures].id, line, MAX_CHAR_PATH);
	printf("|%s\n|", data->textures[data->num_textures].path);
	data->textures[data->num_textures].texture = mlx_load_png(line);
	if (data->textures[data->num_textures].texture)
		return (1);
	while (*line && ft_isalpha(*line))
		line++;
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->num_materials++;
	return (0);
}
