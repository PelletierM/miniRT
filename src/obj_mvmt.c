/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mvmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:22:35 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/11 13:55:08 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_obj(t_data *data, int direction)
{
	t_vector	*pos;

	if (data->nav_mode.obj == OBJ_SPHERE)
		pos = &(data->spheres[data->nav_mode.i].position);
	else if (data->nav_mode.obj == OBJ_PLANE)
		pos = &(data->planes[data->nav_mode.i].position);
	else if (data->nav_mode.obj == OBJ_CYL)
		pos = &(data->cylinders[data->nav_mode.i].position);
	if (direction == OBJ_MV_LEFT)
		*pos = translate_pt(*pos, -1 * OBJ_MV_RATIO, data->camera.x_axis);
	else if (direction == OBJ_MV_RIGHT)
		*pos = translate_pt(*pos, OBJ_MV_RATIO, data->camera.x_axis);
	else if (direction == OBJ_MV_FORWARD)
		*pos = translate_pt(*pos, -1 * OBJ_MV_RATIO, data->camera.y_axis);
	else if (direction == OBJ_MV_BACK)
		*pos = translate_pt(*pos, OBJ_MV_RATIO, data->camera.y_axis);
	else if (direction == OBJ_MV_DOWN)
		*pos = translate_pt(*pos, -1 * OBJ_MV_RATIO, data->camera.z_axis);
	else if (direction == OBJ_MV_UP)
		*pos = translate_pt(*pos, OBJ_MV_RATIO, data->camera.z_axis);
	if (data->nav_mode.obj == OBJ_CYL)
		set_cylinders_disk(&data->cylinders[data->nav_mode.i]);
}

void	rot_obj(t_data *data, int i)
{
	(void) data;
	(void) i;
}

void	scale_obj(t_data *data, int i)
{
	(void) data;
	(void) i;
}
