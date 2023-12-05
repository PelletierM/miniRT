/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:00:04 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/05 08:58:09 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_fill_bg(t_data *data)
{
	int	x;
	int	y;
	int	red;
	int	green;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			red = x * 255 / WIN_WIDTH;
			green = y * 255 / WIN_HEIGHT;
			ft_put_pixel(data, x, y, get_rgba(red, green, 0, 255));
			y++;
		}
		x++;
	}
}

void	ft_put_pixel(t_data *data, double x, double y, unsigned int color)
{
	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	mlx_put_pixel(data->img, x, y, color);
}
