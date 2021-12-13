/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 23:29:27 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/07 23:29:28 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(t_philo *philo, short code)
{
	pthread_mutex_lock(&philo->sim->console);
	if (philo->sim->ended)
	{
		pthread_mutex_unlock(&philo->sim->console);
		return ;
	}
	if (!philo->sim->ended)
		printf("❀ \e[38;5;6;1m%ld\e[0m\t\t\t",
			get_time() - philo->sim->started_t);
	if (code == FORK && !philo->sim->ended)
		printf("\e[38;5;78mphilo %d has taken a fork. °♥\e[0m\n", philo->id);
	else if (code == EATING && !philo->sim->ended)
		printf("\e[38;5;226mphilo %d is eating. °♥\e[0m\n", philo->id);
	else if (code == SLEEPING && !philo->sim->ended)
		printf("\e[38;5;171mphilo %d is sleeping. °♥\e[0m\n", philo->id);
	else if (code == THINKING && !philo->sim->ended)
		printf("\e[38;5;105mphilo %d is thinking. °♥\e[0m\n", philo->id);
	else if (code == DEAD && !philo->sim->ended)
		printf("\e[38;5;124mphilo %d is dead. °♥\e[0m\n", philo->id);
	else if (code == OVERATE && !philo->sim->ended)
		printf("\e[38;5;231mphilos ate %d time(s). °♥\e[0m\n",
			philo->sim->rules.meal_count);
	pthread_mutex_unlock(&philo->sim->console);
}
