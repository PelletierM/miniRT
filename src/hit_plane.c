/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_planes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:16:34 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 09:51:56 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	check_hit_planes(t_plane plane, t_ray ray)
{
	float	denominator;
	float	numerator;

	denominator = vdot(ray.orientation, plane.orientation);
	if (denominator == 0)
		return (0);
	numerator = vdot(plane.orientation, vsub(vsmul(
					plane.position, 1), ray.position));
	return (numerator / denominator);
}
