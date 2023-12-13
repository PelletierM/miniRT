/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:10:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/12 17:26:26 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	miss(void);
void	perpixel(int x, int y, t_data *data);
void	get_range(int id, t_data *data, int *range);

void	*render_thread(void *param)
{
	t_thread	*thread;
	t_data		*data;
	int			range[2];
	int			i;

	thread = (t_thread *) param;
	data = thread->data;
	get_range(thread->id, data, range);
	i = range[0];
	while (i < range[1])
	{
		perpixel((i % data->width), (i / data->width), data);
		i++;
	}
	return (NULL);
}

void	get_range(int id, t_data *data, int *range)
{
	int			div;
	int			remaining;

	div = 1;
	if (THREAD_MAX > 0)
		div = (int)((data->width * data->height) / THREAD_MAX);
	remaining = (int)((data->width * data->height) % THREAD_MAX);
	mrt_create_cam(data);
	range[0] = id * div;
	if (remaining > id)
		range[0] += id;
	range[1] = range[0] + div;
	if (remaining > id)
		range[1] += 1;
}
