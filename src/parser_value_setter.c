/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_value_setter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:39:29 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/01 14:19:26 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_values(char *line, t_data *data)
{
	if (!ft_strncmp(line, "A", 1))
	{
		return (set_ambient(line, data));
	}
	return (0);
}
