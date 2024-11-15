/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:00:30 by tbarret           #+#    #+#             */
/*   Updated: 2024/03/08 12:41:37 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	args(int i, char *arg)
{
	int	nb;

	nb = ft_atoi(arg);
	if (i == 1 && (nb < 1 || nb > PHILO_MAX))
		return (printf("Error !\nInvalid number of philosophers.\n"), 0);
	if (i == 2 && nb < 1)
		return (printf("Error !\nInvalid die time.\n"), 0);
	if (i == 3 && nb < 1)
		return (printf("Error !\nInvalid eating time.\n"), 0);
	if (i == 4 && nb < 1)
		return (printf("Error !\nInvalid sleeping time.\n"), 0);
	if (i == 5 && nb < 1)
		return (printf("Error !\nInvalid eat limit.\n"), 0);
	return (1);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!args(i, argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc < 5 || argc > 6)
	{
		printf("Error !\nYou must indicate between 4 and 5 arguments.\n");
		return (0);
	}
	if (!check_args(argv))
		return (0);
	ctx.prop.total = ft_atoi(argv[1]);
	ctx.prop.dead = 0;
	ctx.prop.t_dead = ft_atoi(argv[2]);
	ctx.prop.t_eat = ft_atoi(argv[3]);
	ctx.prop.t_sleep = ft_atoi(argv[4]);
	ctx.prop.max_eat = -1;
	if (ctx.prop.total == 1)
		return (only_one(&ctx));
	if (argv[5])
		ctx.prop.max_eat = ft_atoi(argv[5]);
	init_mutex(&ctx);
	init_philo(&ctx);
	init_thread(&ctx);
	exit_program(&ctx);
}
