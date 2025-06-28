/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/28 16:07:39 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void *philo_loop(t_philo *philo, t_data *data)
{
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&data->printf_lock);
        printf("Philosopher %d took fork\n", philo->id);
        pthread_mutex_unlock(&data->printf_lock);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&data->printf_lock);
        printf("Philosopher%d took fork\n", philo->id);
        pthread_mutex_unlock(&data->printf_lock);
        philo->last_meal_time = get_time();
        philo->meals_eaten++;
        pthread_mutex_lock(&data->printf_lock);
        printf("Philosopher %d eats meals\n", philo->id);
        pthread_mutex_unlock(&data->printf_lock);
        usleep(data->time_to_eat * 1000);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_lock(&data->printf_lock);
        printf("Philosopher %d is sleeping\n", philo->id);
        pthread_mutex_unlock(&data->printf_lock);
        usleep(data->time_to_sleep * 1000);
        pthread_mutex_lock(&data->printf_lock);
        printf("Philosophers %d is Thinking\n", philo->id);
        pthread_mutex_unlock(&data->printf_lock);
    return (NULL);
}




void *philo_live(void *turn)
{
    t_philo *philo = (t_philo *)turn;
    t_data *data = philo->data;
    
    if ((philo->id % 2) !=0)
        usleep(1000);
    while (!data->someone_died)
        philo_loop(philo, data);
    return (NULL);
    
}


