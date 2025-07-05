/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:34 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/05 14:57:22 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					total_meal_count;
	long				start_time;
	pthread_mutex_t		dead;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	pthread_t			check_simulation;
	bool				end_flag;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long			last_meal_time;
	pthread_t		philo;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*t_data;
}	t_philo;

long	get_time(void);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
bool	get_end_flag(t_data *data);
void	*philo_loop(void *arg);
void	*one_philo(void *arg);
void	philo_state(t_philo *philo);
void	creat_thread(t_philo *philo);
void	*check_simulation(void *arg);
void	wait_function(t_data *data, long time);
void	free_philo(t_philo *philo, t_data *data);
void	printf_function(char *str, t_philo *philo);
#endif