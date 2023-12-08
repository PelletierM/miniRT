/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:07:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/08 09:12:08 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_cylinders_disk(t_cylinder	*cy)
{
	cy->bottom.position = vcopy(cy->position);
	cy->bottom.orientation = vsmul(cy->orientation, -1);
	cy->top.orientation = vsmul(cy->orientation, 1);
	cy->top.position = translate_point(
			cy->position,
			cy->height,
			cy->orientation);
}
