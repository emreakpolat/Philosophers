/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:55:18 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/02 20:55:41 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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