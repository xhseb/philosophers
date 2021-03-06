/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonkang <sonkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:23:28 by sonkang           #+#    #+#             */
/*   Updated: 2021/11/23 20:16:32 by sonkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_atoi(const char *str)
{
	int				idx;
	long long int	num;

	idx = 0;
	num = 0;
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		num = num * 10 + (str[idx] - 48);
		idx++;
		if (num > 2147483647)
			return (0);
	}
	if (str[idx])
		return (0);
	return (num);
}
