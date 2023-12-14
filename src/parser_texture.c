/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:52:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/14 14:00:23 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_path(char *line);

int	set_texture(char *line, t_data *data)
{
	line += 2;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	data->textures[data->num_textures].id = ft_atoi(line);
	if (*line == '+' || *line == '-')
		line++;
	line = skip_digits(line);
	line = skip_spaces(line);
	line = ft_strtrim(line, "\n ");
	if (ft_strlen(line) > MAX_CHAR_PATH)
		return (1);
	data->textures[data->num_textures].img = mlx_load_png(line);
	if (data->textures[data->num_textures].img)
		return (1);
	while (*line && is_path(line))
		line++;
	data->num_textures++;
	return (0);
}

void	delete_textures(t_data *data)
{
	int	i;

	i = 0;

	while (i < data->num_textures)
	{
		mlx_delete_texture(data->textures[i].img);
		i++;
	}
}

int	is_path(char *line)
{
	return (ft_isalpha(*line) || *line == '.' || *line == '/');
}
