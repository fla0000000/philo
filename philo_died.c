/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_died.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviobiondo <flaviobiondo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 01:41:18 by flaviobiond       #+#    #+#             */
/*   Updated: 2023/06/29 01:42:18 by flaviobiond      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosofer.h"

void	died(t_matrix *mat)
{
	int	i;

	i = -1;
	while (++i < mat->num_philo)
		mat->room[i].life = 0;
}
