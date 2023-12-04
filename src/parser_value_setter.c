/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_value_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:29 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 11:20:08 by eguefif          ###   ########.fr       */
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
	return (0);
}
