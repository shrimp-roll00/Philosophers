/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:42:38 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/11 15:42:55 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*overseeing(void	*phil)
{
	t_philo	*philo;

	philo = phil;
	while (!philo->sim->ended)
	{
		usleep_ms(philo->sim->rules.time_to_die);
		sem_wait(philo->meal_lock);
		if (get_time() - philo->last_meal_t >= philo->sim->rules.time_to_die)
		{
			sem_wait(philo->sim->death);
			status(philo, DEAD);
			philo->sim->ended = 1;
			sem_post(philo->meal_lock);
			sem_post(philo->sim->finished);
			break ;
		}
		sem_post(philo->meal_lock);
	}
	return (NULL);
}

static int	routine(t_philo *phil)
{
	t_philo	*philo;

	philo = phil;
	philo->last_meal_t = get_time();
	if (pthread_create(&philo->overseer, NULL, &overseeing, philo) != 0)
		return (1);
	pthread_detach(philo->overseer);
	while (!philo->sim->ended)
	{
		eaty(philo);
		if (philo->sim->rules.meal_count != -1
			&& philo->meals == philo->sim->rules.meal_count)
			sem_post(philo->sim->full);
		if (philo->sim->ended)
			break ;
		sleepy(philo);
		if (philo->sim->ended)
			break ;
		thinky(philo);
		if (philo->sim->ended)
			break ;
	}
	return (0);
}

void	*waiter(void *arg)
{
	t_sim			*sim;
	unsigned int	c;

	sim = arg;
	c = 0;
	if (sim->rules.meal_count == -1)
		return (NULL);
	while (!sim->ended)
	{
		if (sim->ended)
			return (NULL);
		sem_wait(sim->full);
		if (sim->ended)
			return (NULL);
		c++;
		if (c == sim->rules.philo_count)
			break ;
	}
	sim->ended = 1;
	sem_post(sim->finished);
	status(&sim->philos[0], OVERATE);
	return (NULL);
}

int	launch_sim(t_sim *sim)
{
	unsigned int	i;
	pthread_t		meals;

	if (pthread_create(&meals, NULL, &waiter, sim) != 0)
		return (1);
	pthread_detach(meals);
	sim->started_t = get_time();
	i = -1;
	while (++i < sim->rules.philo_count)
	{
		sim->philos[i].pid = fork();
		if (sim->philos[i].pid < 0)
			return (1);
		else if (sim->philos[i].pid == 0)
		{
			routine(&sim->philos[i]);
			exit(0);
		}
	}
	sem_wait(sim->finished);
	i = -1;
	while (++i < sim->rules.philo_count)
		kill(sim->philos[i].pid, SIGKILL);
	return (0);
}
