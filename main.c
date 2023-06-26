/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviobiondo <flaviobiondo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:54:32 by flaviobiond       #+#    #+#             */
/*   Updated: 2023/06/26 20:59:15 by flaviobiond      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

int	main(int ac, char **av)
{
	t_matrix	mat;

	if (check_input(ac, av, &mat))
		return (ft_exit(&mat));
	if (philo_init(&mat))
		return (ft_exit(&mat));
	if (play(&mat))
		return (ft_exit(&mat));
	ft_exit(&mat);
	return (0);
}

int	play(t_matrix *mat)
{
	int	i;

	i = -1;
	while (++i < mat->num_philo)
	{
		if (pthread_create(&mat->room[i].philo, NULL, &philo_routine,
				(void *)&mat->room[i]))
			return (1);
	}
	i = -1;
	while (++i < mat->num_philo)
	{
		if (pthread_join(mat->room[i].philo, NULL))
			return (1);
	}
	free(mat->room);
	return (0);
}

void	*philo_routine(void *empty)
{
	t_philo	*philo;

	philo = (t_philo *)empty;
	philo->time_life = philo->mat->time_death + get_time();
	if (philo->id % 2 != 0)
		my_usleep(10);
	if (pthread_create(&philo->keeper, NULL, &ft_keeper, empty))
		return ((void *)1);
	pthread_detach(philo->keeper);
	while (philo->life)
	{
		if (philo->mat->num_philo == 1)
			caseone(philo->mat);
		else
		{
			eat(philo);
			message(philo, SLEEP);
			my_usleep(philo->mat->time_eat);
			message(philo, THINK);
		}
	}
	if (pthread_join(philo->keeper, NULL))
		return ((void *)1);
	return ((void *)0);
}

void	*ft_keeper(void *empty)
{
	t_philo	*philo;

	philo = (t_philo *)empty;
	while (get_time() < philo->time_life && (philo->mat->time_max_eat == -1
			|| philo->count_eat < philo->mat->time_max_eat))
		;
	if (philo->mat->time_max_eat > 0
		&& philo->count_eat >= philo->mat->time_max_eat)
		philo->life = 0;
	else
	{
		pthread_mutex_lock(&philo->mat->lock);
		message(philo, DIE);
		died(philo->mat);
		pthread_mutex_unlock(&philo->mat->lock);
	}
	return ((void *)0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	message(philo, FORK);
	pthread_mutex_lock(&philo->mat->room[philo->next_fork].fork);
	message(philo, FORK);
	philo->eating = 1;
	philo->time_life += philo->mat->time_death;
	message(philo, EAT);
	my_usleep(philo->mat->time_eat);
	philo->count_eat++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->mat->room[philo->next_fork].fork);
}
void	died(t_matrix *mat)
{
	int i;
	
	i = -1;
	while (++i < mat->num_philo)
		mat->room[i].life = 0;
}