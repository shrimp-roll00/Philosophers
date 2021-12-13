/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:55:08 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/07 17:55:10 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK 111
# define EATING 4
# define SLEEPING 777
# define THINKING 99
# define DEAD 666
# define OVERATE 444

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	t_sim			*sim;
	pthread_t		thread;
	pthread_t		overseer;
	unsigned int	id;
	int				meals;
	unsigned long	last_meal_t;
	pthread_mutex_t	meal_lock;
}	t_philo;

typedef struct s_rules
{
	unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				meal_count;
}	t_rules;

struct s_sim
{
	t_rules			rules;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	console;
	unsigned long	started_t;
	short			ended;
};

int				init_sim(t_sim *sim);

int				launch_sim(t_sim *sim);

void			eaty(t_philo *philo);
void			sleepy(t_philo *philo);
void			thinky(t_philo *philo);

void			status(t_philo *philo, short code);

int				print_error(char *msg);

unsigned long	get_time(void);
void			usleep_ms(unsigned long time);

int				atoi_pos(char *str);

#endif
