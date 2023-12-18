/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:00:56 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 13:58:32 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	get_sphere_normal_texture(mlx_texture_t *texture,
				t_hit hit, t_ray ray);
t_vector	transform_to_sphere(t_vector normal,
				t_vector hit_normal, t_ray ray);

t_vector	get_color_sphere_texture(t_data *data, t_hit *hit)
{
	t_vector		color;
	mlx_texture_t	*texture;
	int				u;
	int				v;

	texture = get_texture_img(data, hit);
	if (!texture)
		return (data->spheres[hit->i].color);
	u = hit->u * texture->width;
	v = hit->v * texture->height;
	u = texture->width - u - 1;
	v = texture->height - v - 1;
	color = get_img_pixel(texture, u, v);
	return (color);
}

void	set_sphere_uv(t_data *data, t_hit *hit, t_ray ray)
{
	float		theta;
	float		phi;

	get_normal_hit(data, ray, hit);
	theta = acosf(-hit->normal.y);
	phi = atan2f(-hit->normal.z, hit->normal.x) + M_PI;
	hit->u = phi / (2 * M_PI);
	hit->v = theta / M_PI;
}

t_vector	get_texture_normal(t_data *data, t_hit hit, t_ray ray)
{
	t_vector		normal;
	mlx_texture_t	*texture;
	int				x;
	int				y;

	texture = get_norm_texture_img(data, hit);
	if (!texture)
		return (hit.normal);
	if (hit.shape == OBJ_SPHERE)
	{
		normal = get_sphere_normal_texture(texture, hit, ray);
	}
	else 
	{
		x = (int) hit.u % texture->width;
		y = (int) hit.v % texture->height;
		normal = get_img_pixel(texture, x, y);
		normal = vnormalize(vssub(vsmul(normal, 2.0), 1.0));
	}
	return (normal);
}

t_vector	get_sphere_normal_texture(mlx_texture_t *texture, t_hit hit,
				t_ray ray)
{
	int			x;
	int			y;
	t_vector	normal;

	x = (int) hit.u * texture->width;
	y = (int) hit.v * texture->height;
	x = texture->width - x - 1;
	y = texture->height - y - 1;
	normal = get_img_pixel(texture, x, y);
	normal = vnormalize(vssub(vsmul(normal, 2.0), 1.0));
	normal = transform_to_sphere(normal, hit.normal, ray);
	return (normal);
}

t_vector	transform_to_sphere(t_vector normal, t_vector hit_normal, t_ray ray)
{
	t_vector	x_axis;
	t_vector	y_axis;
	t_vector	z_axis;
	t_vector	new_normal;

	z_axis = vcopy(hit_normal);
	y_axis = vnormalize(vcross(vsmul(ray.orientation, -1), hit_normal));
	x_axis = vnormalize(vcross(y_axis, z_axis));
	new_normal = black_color();
	new_normal = vadd(new_normal, vsmul(x_axis, normal.x));
	new_normal = vadd(new_normal, vsmul(y_axis, normal.y));
	new_normal = vadd(new_normal, vsmul(z_axis, normal.z));
	return (vnormalize(new_normal));
}
