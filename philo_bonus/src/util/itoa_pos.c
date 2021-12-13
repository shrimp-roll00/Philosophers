/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:43:32 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/11 15:43:33 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	numlen(int n)
{
	int	c;

	if (n < 0)
		c = 1;
	else
		c = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

static int	strlength(char *s)
{
	int	res;

	res = 0;
	while (*s++)
		res++;
	return (res);
}

static void	reverse_str(char *str)
{
	char	*res;
	char	temp;

	res = str + strlength(str) - 1;
	if (*str == '-')
		str++;
	while (res > str)
	{
		temp = *res;
		*res-- = *str;
		*str++ = temp;
	}
}

char	*itoa_pos(int n)
{
	char	*str;
	char	*res;
	long	l;

	l = n;
	str = malloc(numlen(n) + 1);
	res = str;
	if (!str)
		return (0);
	while (l != 0)
	{
		*str++ = l % 10 + '0';
		l /= 10;
	}
	*str = 0;
	reverse_str(res);
	return (res);
}
