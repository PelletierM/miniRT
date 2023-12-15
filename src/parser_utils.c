/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:00:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/15 17:30:58 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	get_decimal_for_float(char *line);

int	get_ratio(char *line, float *ratio)
{
	float	value;

	if (!*line && !*(line + 1))
		return (1);
	value = get_float(line);
	if (value >= 0 && value <= 1)
		*ratio = value;
	else
		return (1);
	return (0);
}

float	get_float(char *line)
{
	int		integer;
	float	retval;
	float	neg;

	neg = 1;
	if (*line == '-')
		neg = -1;
	integer = ft_atoi(line);
	if (integer < 0)
		integer *= -1;
	if (*line && (*line == '+' || *line == '-'))
		line++;
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != '.')
		return (neg * (float) integer);
	line++;
	retval = get_decimal_for_float(line);
	return (neg * ((float) integer + retval));
}

static float	get_decimal_for_float(char *line)
{
	float	retval;
	int		div;

	div = 10;
	retval = 0;
	while (ft_isdigit(*line) && div < 10000)
	{
		retval += (float)(*line - '0') / div;
		line++;
		div *= 10;
	}
	return (retval);
}

int	get_color(char *line, t_vector *vector)
{
	int				i;
	float			v[3];

	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(*line) && *line != '-' && *line != '+')
			return (1);
		v[i] = get_float(line);
		if (*line == '+')
			line++;
		line = skip_float(line);
		if (*line != ',' && i < 2)
			return (1);
		if (i < 2)
			line++;
		i++;
	}
	vector->x = v[0] / 255;
	vector->y = v[1] / 255;
	vector->z = v[2] / 255;
	return (0);
}

int	get_coord(char *line, t_vector *vector)
{
	int		i;
	float	v[3];

	i = 0;
	while (*line && i < 3)
	{
		if (!ft_isdigit(*line) && *line != '-' && *line != '+')
			return (1);
		v[i] = get_float(line);
		if (*line && *line == '+')
			line++;
		line = skip_float(line);
		if (*line && *line != ',' && i < 2)
			return (1);
		if (i < 2)
			line++;
		i++;
	}
	vector->x = v[0];
	vector->y = v[1];
	vector->z = v[2];
	return (0);
}
