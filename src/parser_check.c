/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:40:42 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/01 11:13:34 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	mrt_check_argv(int argc, char *argv[])
{
	int	len;
	int	fd;

	if (argc != 2)
		return (mrt_error_message(ERR_ARGC));
	len = ft_strlen(argv[1]);
	if (!(len > 3 && ft_strcmp(&argv[1][len - 3], ".rt")))
		return (mrt_error_mesage(ERR_FILE_FORMAT));
	fd = open(argv[1]);
	if (fd < 0)
		return (mrt_error_message(ERR_NO_FILE));
	return (0);
}
