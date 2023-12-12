/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:10:15 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/12 08:14:17 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_get_click_target(t_data *data)
{
	int		x;
	int		y;
	t_hit	hit;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	hit = get_closest_hit(data, get_current_ray(data, x, y));
	if (hit.t != -1)
	{
		data->nav_flag = 0;
		data->nav_mode.obj = hit.shape;
		data->nav_mode.i = hit.i;
	}
	else if (data->nav_mode.obj != OBJ_CAM)
	{
		data->nav_mode.obj = OBJ_CAM;
		data->nav_mode.i = 0;
		data->nav_flag = 0;
	}
}
