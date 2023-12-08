/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_mvmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:51:36 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/08 11:52:23 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		rot_cam_vert(t_data *data, int direction, float cs, float sn);
void		rot_cam_horiz(t_data *data, int direction, float cs, float sn);

void	move_cam(t_data *data, int direction)
{
	if (direction == CAM_MV_LEFT)
		data->camera.position = vsub(data->camera.position,
				vsmul(data->camera.x_axis, CAM_MV_RATIO));
	else if (direction == CAM_MV_RIGHT)
		data->camera.position = vadd(data->camera.position,
				vsmul(data->camera.x_axis, CAM_MV_RATIO));
	else if (direction == CAM_MV_FORWARD)
		data->camera.position = vadd(data->camera.position,
				vsmul(data->camera.z_axis, CAM_MV_RATIO));
	else if (direction == CAM_MV_BACK)
		data->camera.position = vsub(data->camera.position,
				vsmul(data->camera.z_axis, CAM_MV_RATIO));
	else if (direction == CAM_MV_DOWN)
		data->camera.position = vadd(data->camera.position,
				vsmul(data->camera.y_axis, CAM_MV_RATIO));
	else if (direction == CAM_MV_UP)
		data->camera.position = vsub(data->camera.position,
				vsmul(data->camera.y_axis, CAM_MV_RATIO));
}

void	rot_cam(t_data *data, int direction)
{
	float	cs;
	float	sn;

	cs = cosf((float) CAM_ROT_ANGLE);
	sn = sinf((float) CAM_ROT_ANGLE);
	if (direction == CAM_ROT_LEFT || direction == CAM_ROT_RIGHT)
		rot_cam_horiz(data, direction, cs, sn);
	else if (direction == CAM_ROT_UP || direction == CAM_ROT_DOWN)
		rot_cam_vert(data, direction, cs, sn);
}

void	rot_cam_vert(t_data *data, int direction, float cs, float sn)
{
	if (direction == CAM_ROT_UP)
	{
		data->camera.z_axis = vadd(vadd(vsmul(data->camera.z_axis, cs),
					vsmul(vcross(data->camera.x_axis, data->camera.z_axis),
						-1 * sn)),
				(vsmul(vsmul(data->camera.x_axis,
							vdot(data->camera.x_axis, data->camera.z_axis)),
						1 - cs)));
	}
	if (direction == CAM_ROT_DOWN)
	{
		data->camera.z_axis = vadd(vadd(vsmul(data->camera.z_axis, cs),
					vsmul(vcross(data->camera.x_axis, data->camera.z_axis),
						sn)), (vsmul(vsmul(data->camera.x_axis,
							vdot(data->camera.x_axis, data->camera.z_axis)),
						1 - cs)));
	}
}

void	rot_cam_horiz(t_data *data, int direction, float cs, float sn)
{
	float	new_x;
	float	new_z;

	if (direction == CAM_ROT_LEFT)
	{
		new_x = cs * data->camera.z_axis.x - sn * data->camera.z_axis.z;
		new_z = sn * data->camera.z_axis.x + cs * data->camera.z_axis.z;
	}
	else 
	{
		new_x = cs * data->camera.z_axis.x + sn * data->camera.z_axis.z;
		new_z = -1 * sn * data->camera.z_axis.x
			+ cs * data->camera.z_axis.z;
	}
	data->camera.z_axis.x = new_x;
	data->camera.z_axis.z = new_z;
}

void	zoom_cam(t_data *data, int direction)
{
	if (direction == CAM_ZOOM_IN)
		data->camera.fov -= CAM_ZOOM_RATIO;
	else if (direction == CAM_ZOOM_OUT)
		data->camera.fov += CAM_ZOOM_RATIO;
}
