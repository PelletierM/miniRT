/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:10:15 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/15 16:30:03 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_get_click_target(t_data *data)
{
	int			x;
	int			y;
	t_ray		ray;
	t_hit		hit;
	t_vector	hit_dist;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	ray = get_current_ray(data, x, y);
	hit = get_closest_hit(data, ray);
	if (hit.t != -1)
	{
		hit_dist = vsub(vadd(ray.position, vsmul(ray.orientation, hit.t)), data->camera.position);
		data->camera.focus_dist = sqrt(vdot(hit_dist, hit_dist));
		data->nav_flag = 0;
		data->nav_mode.obj = hit.shape;
		data->nav_mode.i = hit.i;
		data->samples = 1;
	}
	else if (data->nav_mode.obj != OBJ_CAM)
	{
		data->nav_mode.obj = OBJ_CAM;
		data->nav_mode.i = 0;
		data->nav_flag = 0;
	}
}
