/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_value_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:29 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 15:47:33 by eguefif          ###   ########.fr       */
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
	if (!ft_strncmp(line, "sp", 2))
		return (set_sphere(line, data));
	if (!ft_strncmp(line, "pl", 2))
		return (set_plane(line, data));
	if (!ft_strncmp(line, "cy", 2))
		return (set_cylinder(line, data));
	return (0);
}
