/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/30 18:42:52 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void philo_print(t_data *data, int id, const char *str)
{
    if (get_someone_died(data) != 1)
    {
        pthread_mutex_lock(&data->printf_lock);
        printf("%ld %d %s\n", get_time() - data->start_time, id, str);
        pthread_mutex_unlock(&data->printf_lock);
    }
}

void    check_meal(t_philo *philo)
{
    int count;
    int i;
    int meals_eaten;

    i = 0;
    count = 0;
    while (i < philo->data->philo_count)
    {
        pthread_mutex_lock(&philo->data->philos[i].meal_lock);
        meals_eaten = philo->data->philos[i].meals_eaten;
        pthread_mutex_unlock(&philo->data->philos[i].meal_lock);
        if (meals_eaten >= philo->data->meal_count)
            count++;
        i++;
    }
    if (count == philo->data->meal_count)
    {
        pthread_mutex_lock(&philo->data->death_mutex);
        philo->data->someone_died = 1;
        pthread_mutex_unlock(&philo->data->death_mutex);
    }
}

void *philo_loop(t_philo *philo, t_data *data)
{

    pthread_mutex_lock(philo->left_fork);
    philo_print(data, philo->id, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    philo_print(data, philo->id, "has taken a fork");
    philo_print(data, philo->id, "is eating");
    usleep(data->time_to_eat * 1000);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->meal_lock);
    philo->meals_eaten++;
    philo_print(data, philo->id, "is sleeping");
    usleep(data->time_to_sleep * 1000);
    philo_print(data, philo->id, "is thinking");
    return (NULL);
}

int     get_someone_died(t_data *data)
{
    int someone_died;

    pthread_mutex_lock(&data->death_mutex);
    someone_died = data->someone_died;
    pthread_mutex_unlock(&data->death_mutex);
    return (someone_died);
}

void *philo_live(void *turn)
{
    t_philo *philo = (t_philo *)turn;
    t_data *data = philo->data;

    if ((philo->id % 2) != 0)
        usleep(1000);
    while (!get_someone_died(data))
    {
        philo_loop(philo, data);
    }
    return (NULL);
}

