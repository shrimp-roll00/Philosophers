/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:43:21 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/11 15:43:22 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_args(t_sim *sim, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (print_error("wrong argument count"));
	memset(sim, 0, sizeof(t_sim));
	sim->rules.philo_count = atoi_pos(argv[1]);
	sim->rules.time_to_die = atoi_pos(argv[2]);
	sim->rules.time_to_eat = atoi_pos(argv[3]);
	sim->rules.time_to_sleep = atoi_pos(argv[4]);
	if (argv[5])
		sim->rules.meal_count = atoi_pos(argv[5]);
	else
		sim->rules.meal_count = -1;
	if (!sim->rules.philo_count || !sim->rules.time_to_eat
		|| !sim->rules.time_to_sleep || !sim->rules.time_to_die
		|| !sim->rules.meal_count)
		return (print_error("some of the arguments aren't positive integers"));
	return (0);
}

void	cleanup_sim(t_sim *sim)
{
	unsigned int	i;
	char			*name;

	i = -1;
	while (++i < sim->rules.philo_count)
	{
		name = strjoin_free("/lock", itoa_pos(i));
		sem_unlink(name);
		free(name);
	}
	free(sim->philos);
	sem_unlink("/forks");
	sem_unlink("/console");
	sem_unlink("/death");
	sem_unlink("/full");
	sem_unlink("/finished");
}

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (parse_args(&sim, argc, argv))
		return (1);
	if (init_sim(&sim))
		return (1);
	if (launch_sim(&sim))
	{
		cleanup_sim(&sim);
		return (1);
	}
	cleanup_sim(&sim);
	return (0);
}
