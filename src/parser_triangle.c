/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:04:30 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 14:40:22 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	get_triangle_normal(t_triangle triangle);
int			set_triangle2(char *line, t_data *data);

int	set_triangle(char *line, t_data *data)
{
	line += 2;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->triangles[data->num_triangles].c1))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->triangles[data->num_triangles].c2))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->triangles[data->num_triangles].c3))
		return (1);
	return (set_triangle2(line, data));
}

t_vector	get_triangle_normal(t_triangle triangle)
{
	t_vector	v1;
	t_vector	v2;

	v1 = create_vector_from_points(triangle.c1, triangle.c2);
	v2 = create_vector_from_points(triangle.c1, triangle.c3);
	return (vnormalize(vcross(v1, v2)));
}

int	set_triangle2(char *line, t_data *data)
{
	line = skip_coord(line);
	line = skip_spaces(line);
	data->triangles[data->num_triangles].material_id = ft_atoi(line);
	line = skip_digits(line);
	line = skip_spaces(line);
	data->triangles[data->num_triangles].normal = get_triangle_normal(
			data->triangles[data->num_triangles]);
	if (*line != '\n')
		return (1);
	data->num_triangles++;
	return (0);
}
