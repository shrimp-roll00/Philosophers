/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:43:50 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/11 15:43:51 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	strlength(char *s)
{
	int	res;

	res = 0;
	while (*s++)
		res++;
	return (res);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*str;
	char	*s2_init;
	int		c;

	if (!s1 || !s2)
		return (0);
	str = malloc((strlength(s1) + strlength(s2)) + 1);
	if (!str)
		return (0);
	c = 0;
	s2_init = s2;
	while (*s1)
		str[c++] = *s1++;
	while (*s2)
		str[c++] = *s2++;
	str[c] = 0;
	free(s2_init);
	return (str);
}
