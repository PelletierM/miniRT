/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:40:42 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/18 15:08:21 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	mrt_check_argv(int argc, char *argv[])
{
	int	len;
	int	fd;

	if (argc != 2)
		return (mrt_error_message(ERR_ARGC, 0));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (mrt_error_message(ERR_NO_FILE, 0));
	}
	close(fd);
	len = ft_strlen(argv[1]);
	if (!(len > 3 && !ft_strcmp(&argv[1][len - 3], ".rt")))
		return (mrt_error_message(ERR_FILE_FORMAT, 0));
	return (0);
}
