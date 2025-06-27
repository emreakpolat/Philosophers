/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:34 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/26 14:23:41 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>


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
    pthread_mutex_t print_lock;

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


int	ft_atoi(const char *str);


#endif