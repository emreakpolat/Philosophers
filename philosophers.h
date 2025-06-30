/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:34 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/30 21:00:17 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct s_data
{
    int     philo_count;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     meal_count;
    long    start_time;
    int     someone_died;

    pthread_mutex_t *forks;
    pthread_mutex_t printf_lock;
    pthread_mutex_t death_mutex;

    struct s_philo *philos;
} t_data;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    pthread_t       thread;

    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t meal_lock;

    t_data          *data;

} t_philo;


size_t  ft_strlen(char *str);
long get_time(void);
void *check_death(void *arg);  
int	ft_atoi(const char *str);
int init_philosophers(t_data *philo);
void *philo_live(void *turn);
int     get_someone_died(t_data *data);

#endif