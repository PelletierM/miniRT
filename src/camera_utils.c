/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:47:59 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/18 09:38:51 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	cap_fov(float fov)
{
	if (fov < 0.00174533)
		fov = 0.00174533;
	if (fov > 3.1241394)
		fov = 3.1241394;
	return (fov);
}

float	cap_aperture(float aperture)
{
	if (aperture < 0.1)
		aperture = 0.1;
	if (aperture > 30)
		aperture = 30;
	return (aperture);
}

float	cap_exposure(float exposure)
{
	if (exposure < 0.1)
		exposure = 0.1;
	if (exposure > 10)
		exposure = 10;
	return (exposure);
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

t_ray	apply_dof(t_data *data, t_ray ray)
{
	t_vector	focus_point;
	float		diaph_radius;
	float		x_offset;
	float		y_offset;

	focus_point = vadd(ray.position, vsmul(ray.orientation, data->camera.focus_dist / data->camera.focal_len));
	diaph_radius = ((data->camera.focal_len * 1000) / (float)(data->camera.aperture / 4)) / 2000;
	x_offset = 1;
	y_offset = 1;
	while (pow(x_offset, 2) + pow(y_offset, 2) > pow(diaph_radius, 2))
	{
		x_offset = random_float_range(-1 * diaph_radius, diaph_radius);
		y_offset = random_float_range(-1 * diaph_radius, diaph_radius);
	}
	ray.position = vadd(ray.position, vsmul(data->camera.x_axis, x_offset));
	ray.position = vadd(ray.position, vsmul(data->camera.y_axis, y_offset));
	ray.orientation = vsub(focus_point, ray.position);
	return (ray);
}
