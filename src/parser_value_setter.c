/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_value_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:29 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/14 17:18:04 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_values(char *line, t_data *data)
{
	line = skip_spaces(line);
	if (!ft_strncmp(line, "A", 1))
		return (set_ambient(line, data));
	if (!ft_strncmp(line, "C", 1))
		return (set_camera(line, data));
	if (!ft_strncmp(line, "L", 1))
		return (set_light(line, data));
	if (!ft_strncmp(line, "sp", 2) && data->num_spheres < MAX_FIGURE)
		return (set_sphere(line, data));
	if (!ft_strncmp(line, "pl", 2) && data->num_planes < MAX_FIGURE)
		return (set_plane(line, data));
	if (!ft_strncmp(line, "cy", 2) && data->num_cylinders < MAX_FIGURE)
		return (set_cylinder(line, data));
	if (!ft_strncmp(line, "mt", 2) && data->num_materials < MAX_FIGURE)
		return (set_material(line, data));
	return (0);
}
