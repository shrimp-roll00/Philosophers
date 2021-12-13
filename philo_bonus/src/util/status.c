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

#include "philo_bonus.h"

void	status(t_philo *philo, short code)
{
	sem_wait(philo->sim->console);
	printf("❀ \e[38;5;6;1m%ld\e[0m\t\t\t", get_time() - philo->sim->started_t);
	if (code == FORK)
		printf("\e[38;5;78mphilo %d has taken a fork. °♥\e[0m\n", philo->id);
	else if (code == EATING)
		printf("\e[38;5;226mphilo %d is eating. °♥\e[0m\n", philo->id);
	else if (code == SLEEPING)
		printf("\e[38;5;171mphilo %d is sleeping. °♥\e[0m\n", philo->id);
	else if (code == THINKING)
		printf("\e[38;5;105mphilo %d is thinking. °♥\e[0m\n", philo->id);
	else if (code == DEAD)
		printf("\e[38;5;124mphilo %d is dead. °♥\e[0m\n", philo->id);
	else if (code == OVERATE)
		printf("\e[38;5;231mphilos ate %d time(s). °♥\e[0m\n",
			philo->sim->rules.meal_count);
	sem_post(philo->sim->console);
}
