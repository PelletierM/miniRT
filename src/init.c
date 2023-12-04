/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:42:07 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 13:48:52 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	mrt_init_data(t_data *data)
{
	data->ambient.ratio = 0;
	data->ambient.color.x = 0;
	data->ambient.color.y = 0;
	data->ambient.color.z = 0;
	data->camera.position.x = 0;
	data->camera.position.y = 0;
	data->camera.position.z = 0;
	data->camera.orientation.x = 0;
	data->camera.orientation.y = 0;
	data->camera.orientation.z = 0;
	data->camera.fov = 55;
	data->light.position.x = 0;
	data->light.position.y = 0;
	data->light.position.z = 0;
	data->light.ratio = 0;
	data->light.color.x = 0;
	data->light.color.y = 0;
	data->light.color.z = 0;
	data->flag = 0;
	data->num_spheres = 0;
	data->num_planes = 0;
	data->num_cylinders = 0;
}