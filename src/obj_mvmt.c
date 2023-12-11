/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mvmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:22:35 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/11 13:52:55 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	get_new_orientation_rot(t_vector, t_camera camera, int i);

void	move_obj(t_data *data, int i)
{
	(void) data;
	(void) i;
}

void	rot_obj(t_data *data, int i)
{
	printf("test\n");
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
