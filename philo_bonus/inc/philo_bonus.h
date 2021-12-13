/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunday <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:42:23 by bsunday           #+#    #+#             */
/*   Updated: 2021/12/11 15:42:25 by bsunday          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>

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
	pid_t			pid;
	pthread_t		overseer;
	unsigned int	id;
	int				meals;
	unsigned long	last_meal_t;
	sem_t			*meal_lock;
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
	sem_t			*forks;
	sem_t			*console;
	sem_t			*death;
	sem_t			*full;
	unsigned long	started_t;
	short			ended;
	sem_t			*finished;
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
char			*itoa_pos(int n);
char			*strjoin_free(char *s1, char *s2);

#endif
