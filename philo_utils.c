/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:14:03 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/26 14:11:22 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int char_check(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            return (-1);       
        i++;   
    }
    return (0);
}

int	ft_atoi(const char *str)
{
	long	k;
	int		sign;

	sign = 1;
    k = char_check(str);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return(printf("Cannot enter a negative value\n"), -1);
		str++;
	}
    if (*str == '0' || k == -1)
    {
        return(printf("invalid argument\n"), -1);
    }
	while (*str >= '0' && *str <= '9')
	{
		k = k * 10 + (*str - 48);
		if (k > 2147483647)
            return(printf("Number entered is greater than max integer\n"), -1);
		str++;
	}
	return (sign * k);
}
