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

#include "philo_bonus.h"

void	eaty(t_philo *philo)
{
	sem_wait(philo->sim->forks);
	status(philo, FORK);
	sem_wait(philo->sim->forks);
	status(philo, FORK);
	sem_wait(philo->meal_lock);
	status(philo, EATING);
	philo->last_meal_t = get_time();
	usleep_ms(philo->sim->rules.time_to_eat);
	philo->meals++;
	sem_post(philo->meal_lock);
	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);
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
