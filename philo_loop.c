/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/29 17:58:35 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void philo_print(t_data *data, int id, const char *str)
{
    pthread_mutex_lock(&data->printf_lock);
    printf("%ld Philosopher %d %s\n", get_time() - data->start_time, id, str);
    pthread_mutex_unlock(&data->printf_lock);
}



void *philo_loop(t_philo *philo, t_data *data)
{

        pthread_mutex_lock(philo->left_fork);
        if (data->someone_died)
            return( pthread_mutex_unlock(philo->left_fork), (void *)1);
        philo_print(data, philo->id, "took left fork");
        pthread_mutex_lock(philo->right_fork);
        if (data->someone_died)
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return(pthread_mutex_unlock(philo->left_fork), (void *)1);
        }
        philo_print(data, philo->id, "took right fork");
        philo->last_meal_time = get_time();
        philo->meals_eaten++;
        philo_print(data, philo->id, "is eating");
        usleep(data->time_to_eat * 1000);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        if (data->someone_died) return ((void *)1);
        philo_print(data, philo->id, "is sleeping");
        usleep(data->time_to_sleep * 1000);
        if (data->someone_died) return ((void *)1);
        philo_print(data, philo->id, "is thinking");
    return (NULL);
}

void *philo_live(void *turn)
{
    t_philo *philo = (t_philo *)turn;
    t_data *data = philo->data;

    if ((philo->id % 2) != 0)
        usleep(1000);
    while (!data->someone_died)
    {
        philo_loop(philo, data);
    }
    return (NULL);
}

