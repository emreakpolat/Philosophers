/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:33:27 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/27 17:45:50 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return((time.tv_sec* 1000) + (time.tv_usec / 1000));
}

int init_philosophers(t_data *philo)
{
    int i;

    philo->philos = malloc(sizeof(t_philo) *philo->philo_count);
    if (!philo->philos)
        return(printf("Malloc error\n"), 1);
    i = 0;
    while (i <philo->philo_count)
    {
        philo->philos[i].id = i + 1;
        philo->philos[i].meals_eaten = 0;
        philo->philos[i].last_meal_time = get_time();
        philo->philos[i].left_fork = &philo->forks[i];
        philo->philos[i].right_fork = &philo->forks[(i + 1) % philo->philo_count];
        philo->philos[i].data = philo;
        if (pthread_mutex_init(&philo->philos[i].meal_lock, NULL) != 0)
            return(printf("Mutex Error\n"), 1);
        i++;
    }
    return (0);
}



size_t  ft_strlen(char *str)
{
    size_t  i;

    i = 0;
    while(str[i])
        i++;
    return (i); 
}




static int	char_check(const char *str)
{
    int i = 0;

    while (str[i])
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            return(1);
        }
        i++;
    }
    return (0);
}

int	ft_atoi(const char *str)
{
	long	k;
	int		sign;

	k = char_check(str);
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+' || k == 1)
        return(printf("Wrong argument\n"), -1);

	while (*str >= '0' && *str <= '9')
	{
		if (*str == '-' || *str == '+')
			return(printf("Wrong argument\n"), -1);
		k = k * 10 + (*str - 48);
		if ((k > 2147483647) || (k < -2147483648))
            return(printf("Wrong argument use integer\n"), -1);
		str++;
	}
	return (sign * k);

}
