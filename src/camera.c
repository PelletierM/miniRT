/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:34:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/07 16:16:13 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	mrt_create_camera(t_data *data)
{
	t_vector	ref_y;

	// We should not allow a camera orientation vector (normalized) that is 0,1,0
	// If we get such an input, it could be changed to 0,0.99,0 and then normalized
	ref_y.x = 0;
	ref_y.y = 1;
	ref_y.z = 0;
	data->camera.z_axis = vnormalize(data->camera.z_axis);
	data->camera.x_axis = vcross(ref_y, data->camera.z_axis);
	data->camera.x_axis = vnormalize(data->camera.x_axis);
	data->camera.y_axis = vcross(data->camera.x_axis, data->camera.z_axis);
	data->camera.y_axis = vnormalize(data->camera.y_axis);

	// We should not allow and FOV of 0 (focal length becomes infinite)
	// or of 180 (focal length becomes 0), it should be 0 < FOV < 180
	data->camera.focal_len = (float) VP_DIAG / (tanf(data->camera.fov / 2) * 2);
	data->camera.vp_vert_len = sqrt(pow(VP_DIAG, 2) / (pow(data->ratio, 2) + 1));
	data->camera.vp_horiz_len = data->camera.vp_vert_len * data->ratio;
}

void	move_camera(t_data *data, int direction)
{
	if (direction == CAM_MV_LEFT)
		data->camera.position = vsub(data->camera.position, data->camera.x_axis);
	else if (direction == CAM_MV_RIGHT)
		data->camera.position = vadd(data->camera.position, data->camera.x_axis);
	else if (direction == CAM_MV_FORWARD)
		data->camera.position = vadd(data->camera.position, data->camera.z_axis);
	else if (direction == CAM_MV_BACK)
		data->camera.position = vsub(data->camera.position, data->camera.z_axis);
	else if (direction == CAM_MV_DOWN)
		data->camera.position = vadd(data->camera.position, data->camera.y_axis);
	else if (direction == CAM_MV_UP)
		data->camera.position = vsub(data->camera.position, data->camera.y_axis);
}

void	rotate_camera(t_data *data, int direction)
{
	float	new_x = 0;
	float	new_z = 0;
	float	new_y = 0;
	float	cs;
	float	sn;

	cs = cosf((float) CAM_ROT_ANGLE);
	sn = sinf((float) CAM_ROT_ANGLE);
	if (direction == CAM_ROT_LEFT)
	{
		new_x = cs * data->camera.z_axis.x - sn * data->camera.z_axis.z;
		new_z = sn * data->camera.z_axis.x + cs * data->camera.z_axis.z;
		new_y = data->camera.z_axis.y;
	}
	else if (direction == CAM_ROT_RIGHT)
	{
		new_x = cs * data->camera.z_axis.x + sn * data->camera.z_axis.z;
		new_z = -1 * sn * data->camera.z_axis.x + cs * data->camera.z_axis.z;
		new_y = data->camera.z_axis.y;
	}
	data->camera.z_axis.x = new_x;
	data->camera.z_axis.z = new_z;
}
