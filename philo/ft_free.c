/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonkang <sonkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:23:37 by sonkang           #+#    #+#             */
/*   Updated: 2021/11/23 20:50:15 by sonkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_info *info, t_ph *ph)
{
	int	idx;

	idx = -1;
	while (++idx < info->ph_num)
		pthread_mutex_destroy(&info->fork[idx]);
	pthread_mutex_destroy(&info->ifdie);
	free(info->fork);
	free(info);
	free(ph);
}

void	check_fin(t_info *info, t_ph *ph)
{
	int	idx;

	idx = -1;
	while (1)
	{
		if (ph[++idx].die == 1 || check_eatcount(ph))
		{
			idx = -1;
			while (++idx < info->ph_num)
				ph[idx].die = 1;
			ft_free(info, ph);
			return ;
		}
		if (idx == info->ph_num - 1)
			idx = -1;
	}
}

void	print_eatting(t_ph *ph)
{
	printf("%u %d has taken a fork\n", present(ph), ph->id);
	printf("%u %d is eating\n", present(ph), ph->id);
}
