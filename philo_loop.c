/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/29 13:51:46 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void *philo_loop(t_philo *philo, t_data *data)
{
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&data->printf_lock);
        printf("Philosopher %d took left fork\n", philo->id);
        pthread_mutex_unlock(&data->printf_lock);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&data->printf_lock);
        printf("Philosopher %d took right fork\n", philo->id);
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
    {
        philo_loop(philo, data);
    }
    return (NULL);
}


void *check_death(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!data->someone_died)  
    {
        i = 0;
        while(i < data->philo_count)
        {
            pthread_mutex_lock(&data->philos[i].meal_lock);
            if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
            {
                pthread_mutex_lock(&data->printf_lock);
                printf("%ld Philosophers %d  dead\n", (get_time() - data->start_time), data->philos[i].id);
                data->someone_died = 1;
                pthread_mutex_unlock(&data->printf_lock);
                pthread_mutex_unlock(&data->philos[i].meal_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&data->philos[i].meal_lock);
            i++;
        }
        usleep(500);
    }
    return (NULL);
}
