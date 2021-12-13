/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:42:31 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/11 15:42:32 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	*semphr_open(char *name, int val)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, val));
}

static void	get_meal_lock(t_philo *philo)
{
	char	*name;

	name = strjoin_free("/lock", itoa_pos(philo->id));
	philo->meal_lock = semphr_open(name, 1);
	free(name);
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
		get_meal_lock(&sim->philos[i]);
	}
	return (0);
}

int	init_sim(t_sim *sim)
{
	sim->forks = semphr_open("/forks", sim->rules.philo_count);
	sim->console = semphr_open("/console", 1);
	sim->death = semphr_open("/death", 1);
	sim->full = semphr_open("/full", 0);
	sim->finished = semphr_open("/finished", 0);
	if (get_philos(sim))
	{
		sem_unlink("/forks");
		sem_unlink("/console");
		sem_unlink("/death");
		sem_unlink("/full");
		sem_unlink("/finished");
		return (print_error("error during philos initialization"));
	}
	return (0);
}
