/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:34:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/19 11:06:11 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

float		cap_fov(float fov);
float		cap_aperture(float aperture);
t_vector	cap_axis_y(t_vector v);
float		cap_exposure(float exposure);

void	mrt_create_cam(t_data *data)
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
	data->camera.aperture = cap_aperture(data->camera.aperture);
	data->camera.exposure = cap_exposure(data->camera.exposure);
	data->camera.focal_len = (float) VP_DIAG / (tanf(data->camera.fov / 2) * 2);
	data->camera.vp_vert_len = sqrt(pow(VP_DIAG, 2)
			/ (pow(data->ratio, 2) + 1));
	data->camera.vp_horiz_len = data->camera.vp_vert_len * data->ratio;
}
