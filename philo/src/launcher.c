/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:18:04 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/07 19:18:05 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	meal_count(t_philo	*philo)
{
	unsigned int	i;

	i = -1;
	while (++i < philo->sim->rules.philo_count)
	{
		if (philo->sim->philos[i].meals < philo->sim->rules.meal_count)
			return (0);
	}
	status(philo, OVERATE);
	philo->sim->ended = 1;
	return (1);
}

static void	*routine(void	*phil)
{
	t_philo	*philo;

	philo = phil;
	if (philo->id % 2 == 0 && philo->sim->rules.philo_count != 1)
		usleep(100 * (philo->sim->rules.time_to_eat / 2));
	while (!philo->sim->ended)
	{
		eaty(philo);
		if (philo->sim->rules.meal_count != -1 && meal_count(philo))
			break ;
		if (philo->sim->ended)
			break ;
		sleepy(philo);
		if (philo->sim->ended)
			break ;
		thinky(philo);
		if (philo->sim->ended)
			break ;
	}
	return (NULL);
}

static void	*overseeing(void	*phil)
{
	t_philo	*philo;

	philo = phil;
	while (!philo->sim->ended)
	{
		usleep_ms(philo->sim->rules.time_to_die);
		pthread_mutex_lock(&philo->meal_lock);
		if (get_time() - philo->last_meal_t >= philo->sim->rules.time_to_die)
		{
			status(philo, DEAD);
			philo->sim->ended = 1;
			pthread_mutex_unlock(&philo->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_lock);
	}
	return (NULL);
}

int	launch_sim(t_sim *sim)
{
	unsigned int	i;

	sim->started_t = get_time();
	i = -1;
	while (++i < sim->rules.philo_count)
	{
		sim->philos[i].last_meal_t = get_time();
		if (pthread_create(&sim->philos[i].thread, NULL, routine,
				&sim->philos[i]))
			return (1);
		if (pthread_create(&sim->philos[i].overseer, NULL, overseeing,
				&sim->philos[i]))
			return (1);
	}
	i = -1;
	while (++i < sim->rules.philo_count)
	{
		if (pthread_join(sim->philos[i].thread, NULL))
			return (1);
		if (pthread_join(sim->philos[i].overseer, NULL))
			return (1);
	}
	return (0);
}
