/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviobiondo <flaviobiondo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:18:47 by flaviobiond       #+#    #+#             */
/*   Updated: 2023/06/28 16:42:11 by flaviobiond      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

void caseone(t_matrix *mat)
{
	message(&mat->room[0], FORK);
	my_usleep(mat->time_death);	
	mat->room[0].life = 0;
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / (u_int64_t)1000));
}

int	ft_exit(t_matrix *mat)
{
	int	i;

	i = -1;
	while (++i < mat->num_philo)
		pthread_mutex_destroy(&mat->room[i].fork);
	pthread_mutex_destroy(&mat->lock);
	return (1);
}

void	my_usleep(int ms)
{
	u_int64_t start;

	start = get_time();
	while ((get_time() - start) < (u_int64_t)ms)
		usleep(ms / 10);
}


void	message(t_philo *philo, char *str)
{
	u_int64_t	time;

	time = get_time() - philo->mat->origin_time;
	if (philo->life || philo->mat->num_philo == 1)
		printf("%llu %d %s\n", time, philo->id + 1, str);
}