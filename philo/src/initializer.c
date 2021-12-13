/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:56:07 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/07 18:56:08 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	release_forks(t_sim *sim, unsigned int i)
{
	int	n;

	n = i;
	while (--n && n >= 0)
		pthread_mutex_destroy(&sim->forks[i]);
	free(sim->forks);
}

static int	get_forks(t_sim *sim)
{
	unsigned int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->rules.philo_count);
	if (!sim->forks)
		return (1);
	i = -1;
	while (++i < sim->rules.philo_count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
		{
			release_forks(sim, i);
			return (1);
		}
	}
	return (0);
}

static void	release_meal_locks(t_sim *sim, unsigned int i)
{
	int	n;

	n = i;
	while (--n && n >= 0)
		pthread_mutex_destroy(&sim->philos[i].meal_lock);
	free(sim->philos);
}

static int	get_philos(t_sim *sim)
{
	unsigned int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->rules.philo_count);
	if (!sim->philos)
		return (1);
	i = -1;
	while (++i < sim->rules.philo_count)
	{
		sim->philos[i].sim = sim;
		sim->philos[i].id = i;
		sim->philos[i].meals = 0;
		if (pthread_mutex_init(&sim->philos[i].meal_lock, NULL))
		{
			release_meal_locks(sim, i);
			return (1);
		}
	}
	return (0);
}

int	init_sim(t_sim *sim)
{
	if (pthread_mutex_init(&sim->console, NULL))
		return (print_error("console mutex wasn't initialized"));
	if (get_forks(sim))
	{
		pthread_mutex_destroy(&sim->console);
		return (print_error("error during forks initialization"));
	}
	if (get_philos(sim))
	{
		pthread_mutex_destroy(&sim->console);
		release_forks(sim, sim->rules.philo_count);
		return (print_error("error during philos initialization"));
	}
	return (0);
}
