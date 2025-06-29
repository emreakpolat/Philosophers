/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/29 16:44:09 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void philo_print(t_data *data, int id, const char *action)
{
    pthread_mutex_lock(&data->printf_lock);
    printf("%ld Philosopher %d %s\n", get_time() - data->start_time, id, action);
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

// void *check_death(void *arg)
// {
//     t_data *data = (t_data *)arg;
//     int i;

//     while (!data->someone_died)  
//     {
//         i = 0;
//         while(i < data->philo_count)
//         {
//             pthread_mutex_lock(&data->philos[i].meal_lock);
//             if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
//             {
//                 pthread_mutex_lock(&data->printf_lock);
//                 printf("%ld Philosophers %d  dead\n", (get_time() - data->start_time), data->philos[i].id);
//                 data->someone_died = 1;
//                 pthread_mutex_unlock(&data->printf_lock);
//                 pthread_mutex_unlock(&data->philos[i].meal_lock);
//                 return (NULL);
//             }
//             pthread_mutex_unlock(&data->philos[i].meal_lock);
//             i++;
//         }
//         usleep(500);
//     }
//     return (NULL);
// }
