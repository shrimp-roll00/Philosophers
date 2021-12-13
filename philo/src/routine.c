/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 23:29:44 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/07 23:29:45 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eaty(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->id]);
	status(philo, FORK);
	if (philo->sim->rules.philo_count == 1)
	{
		while (!philo->sim->ended)
			usleep(100);
		pthread_mutex_unlock(&philo->sim->forks[philo->id]);
		return ;
	}
	pthread_mutex_lock(&philo->sim->forks[(philo->id + 1)
		% philo->sim->rules.philo_count]);
	status(philo, FORK);
	pthread_mutex_lock(&philo->meal_lock);
	status(philo, EATING);
	philo->last_meal_t = get_time();
	usleep_ms(philo->sim->rules.time_to_eat);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	pthread_mutex_unlock(&philo->sim->forks[(philo->id + 1)
		% philo->sim->rules.philo_count]);
}

void	sleepy(t_philo *philo)
{
	status(philo, SLEEPING);
	usleep_ms(philo->sim->rules.time_to_sleep);
}

void	thinky(t_philo *philo)
{
	status(philo, THINKING);
}
