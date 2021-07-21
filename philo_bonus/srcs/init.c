#include "philo_bonus.h"

static int	init_sem(t_vars *vars)
{
	sem_unlink("/forks_sem");
	sem_unlink("/eat_sem");
	sem_unlink("/write_sem");
	sem_unlink("/death_sem");
	if ((vars->forks_sem = sem_open("/forks_sem", O_CREAT, O_EXCL, 0644, vars->philo_nbr)) == SEM_FAILED)
		return (write_error("Sem open failed\n", 16));
	vars->eat_sem = sem_open("/eat_sem", O_CREAT, O_EXCL, 0644, vars->philo_nbr / 2);
	vars->write_sem = sem_open("/write_sem", O_CREAT, O_EXCL, 0644, 1);
	vars->death_sem = sem_open("/death_sem", O_CREAT, O_EXCL, 0644, 1);
	return (1);
}

static int	init_philo(t_vars *vars)
{
	int		i;

	vars->philo = malloc(sizeof(t_philo) * vars->philo_nbr);
	if (!vars->philo)
		return (write_error("Malloc error\n", 13));
	i = -1;
	while (++i < vars->philo_nbr)
	{
		memset(&vars->philo[i], 0, sizeof(t_philo));
		vars->philo[i].position = i + 1;
		vars->philo[i].vars = vars;
	}
	return (1);
}

int	init(int argc, char **argv, t_vars *vars)
{
	memset(vars, 0, sizeof(t_vars));
	vars->philo_nbr = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		vars->times_must_eat = ft_atoi(argv[5]);
		vars->each_ate = malloc(sizeof(int) * vars->philo_nbr);
		if (!vars->each_ate)
			return (0);
		memset(vars->each_ate, 0, sizeof(int) * vars->philo_nbr);
	}
	if (vars->philo_nbr > 200 || vars->philo_nbr <= 0 || vars->time_to_die < 60
		|| vars->time_to_eat < 60 || vars->time_to_sleep < 60)
		return (write_error("Invalid arguments\n", 18));
	return (init_philo(vars) && init_sem(vars));
}
