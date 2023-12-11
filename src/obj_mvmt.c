/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mvmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:22:35 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/11 14:01:35 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	get_new_orientation_rot(t_vector, t_camera camera, int i);

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
	if (data->nav_mode.obj == OBJ_CYL)
		data->cylinders[data->nav_mode.i].orientation = get_new_orientation_rot(
			data->cylinders[data->nav_mode.i].orientation,
			data->camera,
			i);
	if (data->nav_mode.obj == OBJ_PLANE)
		data->planes[data->nav_mode.i].orientation = get_new_orientation_rot(
			data->planes[data->nav_mode.i].orientation,
			data->camera,
			i);
}

t_vector	get_new_orientation_rot(t_vector v, t_camera camera, int i)
{
	if (i == OBJ_ROT_LEFT)
		return (rotate_figure(v, camera.z_axis, -1));
	else if (i == OBJ_ROT_RIGHT)
		return (rotate_figure(v, camera.z_axis, 1));
	else if (i == OBJ_ROT_UP)
		return (rotate_figure(v, camera.x_axis, 1));
	else if (i == OBJ_ROT_DOWN)
		return (rotate_figure(v, camera.x_axis, -1));
	return (v);
}

void	scale_obj(t_data *data, int i)
{
	if (data->nav_mode.obj == OBJ_SPHERE)
	{
		if (i == OBJ_SCALE_DOWN)
			data->spheres[data->nav_mode.i].diameter *= OBJ_SCALE_RATIO;
		if (i == OBJ_SCALE_UP)
			data->spheres[data->nav_mode.i].diameter /= OBJ_SCALE_RATIO;
	}
}