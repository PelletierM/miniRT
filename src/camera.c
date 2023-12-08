/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:34:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/08 11:12:11 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float		cap_fov(float fov);
t_vector	cap_axis_y(t_vector v);

void	mrt_create_camera(t_data *data)
{
	t_vector	ref_y;

	ref_y.x = 0;
	ref_y.y = 1;
	ref_y.z = 0;
	data->camera.z_axis = cap_axis_y(data->camera.z_axis);
	data->camera.x_axis = vcross(ref_y, data->camera.z_axis);
	data->camera.x_axis = vnormalize(data->camera.x_axis);
	data->camera.y_axis = vcross(data->camera.x_axis, data->camera.z_axis);
	data->camera.y_axis = vnormalize(data->camera.y_axis);

	data->camera.fov = cap_fov(data->camera.fov);
	data->camera.focal_len = (float) VP_DIAG / (tanf(data->camera.fov / 2) * 2);
	data->camera.vp_vert_len = sqrt(pow(VP_DIAG, 2) / (pow(data->ratio, 2) + 1));
	data->camera.vp_horiz_len = data->camera.vp_vert_len * data->ratio;
}

float		cap_fov(float fov)
{
	if (fov < 0.00174533)
		fov = 0.00174533;
	if (fov > 3.1241394)
		fov = 3.1241394;
	return (fov);
}

t_vector	cap_axis_y(t_vector v)
{
	t_vector	tmp;
	int			sign;

	sign = v.y < 0;
	if (v.y > 0.996 || v.y < -0.996)
	{
		v.y = -0.996 * sign + 0.996 * !sign;
		if (v.z != 0 || v.x != 0)
		{
			tmp.x = v.x;
			tmp.z = v.z;
			tmp.y = 0;
			tmp = vsmul(vnormalize(tmp), 0.089);
			v.x = tmp.x;
			v.z = tmp.z;
		}
		else
		{
			v.z = 0.089;
			v.x = 0;
		}
	}
	v = vnormalize(v);
	return (v);
}

void	move_camera(t_data *data, int direction)
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

void	rotate_camera(t_data *data, int direction)
{
	float	new_x = 0;
	float	new_z = 0;
	float	cs;
	float	sn;

	cs = cosf((float) CAM_ROT_ANGLE);
	sn = sinf((float) CAM_ROT_ANGLE);
	if (direction == CAM_ROT_LEFT || direction == CAM_ROT_RIGHT)
	{
		if (direction == CAM_ROT_LEFT)
		{
			new_x = cs * data->camera.z_axis.x - sn * data->camera.z_axis.z;
			new_z = sn * data->camera.z_axis.x + cs * data->camera.z_axis.z;
		}
		else 
		{
			new_x = cs * data->camera.z_axis.x + sn * data->camera.z_axis.z;
			new_z = -1 * sn * data->camera.z_axis.x + cs * data->camera.z_axis.z;
		}
		data->camera.z_axis.x = new_x;
		data->camera.z_axis.z = new_z;
	}
	else if (direction == CAM_ROT_UP)
	{
		data->camera.z_axis = vadd(vadd(vsmul(data->camera.z_axis, cs),
				vsmul(vcross(data->camera.x_axis, data->camera.z_axis), -1 * sn)),
				(vsmul(vsmul(data->camera.x_axis,
					vdot(data->camera.x_axis, data->camera.z_axis)), 1 - cs)));
	}
	else if (direction == CAM_ROT_DOWN)
	{
		data->camera.z_axis = vadd(vadd(vsmul(data->camera.z_axis, cs),
				vsmul(vcross(data->camera.x_axis, data->camera.z_axis), sn)),
				(vsmul(vsmul(data->camera.x_axis,
					vdot(data->camera.x_axis, data->camera.z_axis)), 1 - cs)));
	}
}

void	zoom_camera(t_data *data, int direction)
{
	if (direction == CAM_ZOOM_IN)
		data->camera.fov -= CAM_ZOOM_RATIO;
	else if (direction == CAM_ZOOM_OUT)
		data->camera.fov += CAM_ZOOM_RATIO;
}
