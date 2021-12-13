/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:55:48 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/07 18:55:49 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_num(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	atoi_pos(char *str)
{
	int	res;

	res = 0;
	if (!is_num(*str))
		return (0);
	while (*str)
	{
		if (is_num(*str))
			res = (res * 10) + (*str++ - 48);
		else
			return (0);
	}
	return (res);
}
