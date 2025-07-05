/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/05 14:48:21 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void philo_state(t_philo *philo)
{
    if ((philo->id % 2) == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        printf_function("has taken a fork", philo);
        pthread_mutex_lock(philo->right_fork);
        printf_function("has taken a fork", philo);
        
    }
    else
    {
        usleep(50);
        pthread_mutex_lock(philo->right_fork);
        printf_function("has taken a fork", philo);
        pthread_mutex_lock(philo->left_fork);
        printf_function("has taken a fork", philo);
    }


}

static void philo_eating(t_philo *philo)
{
    if(get_end_flag(philo->t_data) == false)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal_time = get_time();
    printf_function("is eating", philo);
    pthread_mutex_unlock(&philo->meal_lock);
    wait_function(philo->t_data, philo->t_data->time_to_eat);
    pthread_mutex_lock(&philo->meal_lock);
    philo->meal_count++;
    pthread_mutex_unlock(&philo->meal_lock);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

static void philo_sleep_and_thinking(t_philo *philo)
{
    if(get_end_flag(philo->t_data) == false)
        return ;
    printf_function("is sleeping", philo);
    wait_function(philo->t_data, philo->t_data->time_to_sleep);
    printf_function("is thinking", philo);
}

void *philo_loop(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (get_end_flag(philo->t_data))
    {
        philo_state(philo);
        philo_eating(philo);
        philo_sleep_and_thinking(philo);
    }
    return (NULL);
}

void check_death(t_philo *philo)
{
    int i;
    
    i = 0;
    while (i < philo->t_data->philo_count)
    {
        pthread_mutex_lock(&philo[i].meal_lock);
        if((get_time() - philo[i].last_meal_time) > philo->t_data->time_to_die)
        {
            pthread_mutex_lock(&philo->t_data->dead);
            philo->t_data->end_flag = false;
            pthread_mutex_unlock(&philo->t_data->dead);
            pthread_mutex_unlock(&philo[i].meal_lock);
            printf_function("is died", &philo[i]);
            return ;
        }
        pthread_mutex_unlock(&philo[i].meal_lock);
        i++;
    }
    usleep(100);
}

void check_meals(t_philo *philo)
{
    int count = 0;
    int i = 0;
    if (philo->t_data->total_meal_count == -2)
        return ;
    while (i < philo->t_data->philo_count)
    {
        pthread_mutex_lock(&philo[i].meal_lock);
        if (philo[i].meal_count >= philo->t_data->total_meal_count)
            count++;
        pthread_mutex_unlock(&philo[i].meal_lock);
        i++;
    }
    if (count == philo->t_data->philo_count)
    {
        pthread_mutex_lock(&philo->t_data->dead);
        philo->t_data->end_flag = false;
        pthread_mutex_unlock(&philo->t_data->dead);
    }
}

void *check_simulation(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (get_end_flag(philo->t_data) == true)
    {
        check_death(philo);
        check_meals(philo);       
    }
    return (NULL);
}
void creat_thread(t_philo *philo)
{
    int i = 0;

    while (i < philo->t_data->philo_count)
    {
        if (pthread_create(&philo[i].philo, NULL, philo_loop, &philo[i]) != 0)
            return ;
        i++;
    }
    if (pthread_create(&philo->t_data->check_simulation, NULL, check_simulation, philo) != 0)
        return ;
    i = 0;    
    while (i < philo->t_data->philo_count)
    {
        pthread_join(philo[i].philo, NULL);
        i++;
    }
    pthread_join(philo->t_data->check_simulation, NULL);
}
