/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:34:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/06 12:45:19 by eguefif          ###   ########.fr       */
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
	printf("Focal length: %f\nSensor height: %f\nSensor width: %f\n", data->camera.focal_len, data->camera.vp_vert_len, data->camera.vp_horiz_len);
}
