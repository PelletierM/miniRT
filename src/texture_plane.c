/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:12:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/15 14:52:10 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_plane_uv(t_data *data, t_hit *hit, t_ray ray)
{
	t_vector	position;
	int			coef;

	coef = 250;
	get_normal_hit(data, ray, hit);
	position = vsub(vmul(hit->position, data->camera.z_axis), ray.position);
	position = vnormalize(position);
	if (hit->normal.z == 1 || hit->normal.z == -1)
	{
		hit->u = hit->position.x * coef;
		hit->v = hit->position.y * coef;
	}
	else if (hit->normal.x == 1 || hit->normal.x == -1)
	{
		hit->u = hit->position.z * coef;
		hit->v = hit->position.y * coef;
	}
	else
	{
		hit->u = hit->position.x * coef;
		hit->v = hit->position.z * coef;
	}
}

t_vector	get_color_plane_texture(t_data *data, t_hit *hit)
{
	mlx_texture_t	*texture;
	int				u;
	int				v;

	texture = get_texture_img(data, hit);
	u = (int) hit->u % texture->width;
	v = (int) hit->v % texture->height;
	return (get_img_pixel(texture, u, v));
}
