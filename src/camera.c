/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:34:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/06 11:13:24 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	mrt_set_camera(t_data *data)
{
	t_vector	ref_y;

	// We should not allow a camera orientation vector (normalized) that is 0,1,0
	// If we get such an input, it could be changed to 0,0.99,0 and then normalized
	ref_y.x = 0;
	ref_y.y = 1;
	ref_y.z = 0;
	data->camera.z_axis = v_normalize(data->camera.z_axis);
	data->camera.x_axis = v_cross(data->camera.z_axis, ref_y);
	data->camera.x_axis = v_normalize(data->camera.x_axis);
	data->camera.y_axis = v_cross(data->camera.y_axis, data->camera.z_axis);
	data->camera.y_axis = v_normalize(data->camera.y_axis);

	// We should not allow and FOV of 0 (focal length becomes infinite)
	// or of 180 (focal length becomes 0), it should be 0 < FOV < 180
	data->camera.focal_len = VP_DIAG / ((float) tan(data->camera.fov) * 2);
	data->vp_vert_len = sqrt(pow(VP_DIAG, 2) / (pow(data->ratio, 2) + 1));
	data->vp_horiz_len = data->vp_vert_len * data->ratio;
}
