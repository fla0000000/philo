/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviobiondo <flaviobiondo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:34:06 by flaviobiond       #+#    #+#             */
/*   Updated: 2023/06/26 17:25:10 by flaviobiond      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

int	check_input(int ac, char **av, t_matrix *mat)
{
	if (ac != 5 && ac != 6)
		return (write(1, "Error400\n", 9) - 8);
	mat->num_philo = ft_atoi(av[1]);
	mat->time_death = ft_atoi(av[2]);
	mat->time_eat = ft_atoi(av[3]);
	mat->time_sleep = ft_atoi(av[4]);
	mat->room = ((t_philo *)malloc(sizeof(t_philo) * mat->num_philo));
	if (pthread_mutex_init(&mat->lock, NULL) && (!mat->room))
		return (1);
	if (ac == 6)
		mat->time_max_eat = ft_atoi(av[5]);
	else
		mat->time_max_eat = -1;
	if (mat->num_philo < 1 || mat->num_philo > 200 || mat->time_death < 0
		|| mat->time_eat < 0 || mat->time_sleep < 0)
		return (write(1, "Error407\n", 9) - 8);
	return (0);
}

int	philo_init(t_matrix *mat)
{
	int	i;

	i = -1;
	mat->origin_time = get_time();
	while (++i < mat->num_philo)
	{
		if(init(mat, i))
		return(1);
	}
return (0);
}
int	init(t_matrix *mat, int id)
{
	mat->room[id].id = id;
	mat->room[id].life = 1;
	mat->room[id].eating = 0;
	mat->room[id].count_eat = 0;
	mat->room[id].mat = mat;
	if (id == mat->num_philo - 1)
		mat->room[id].next_fork = 0;
	else
		mat->room[id].next_fork = id + 1;
	if (pthread_mutex_init(&mat->room[id].fork, NULL))
		return (1);
	return (0);
}
