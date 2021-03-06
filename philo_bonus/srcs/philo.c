#include "philo_bonus.h"

int	execute(t_vars *vars)
{
	int		i;

	i = -1;
	vars->time_start = get_time();
	while (++i < vars->philo_nbr)
	{
		vars->philo[i].pid = fork();
		vars->philo[i].pid >= 0 || (free_mem(vars) && exit_error("Fork error"));
		vars->philo[i].pid == 0 && do_routine(&vars->philo[i]);
		usleep(50);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		wstatus;
	t_vars	vars;

	(argc < 5 || argc > 6) && exit_error("Invalid number of arguments");
	init(argc, argv, &vars) || (free_mem(&vars) && exit_error(NULL));
	execute(&vars) || (free_mem(&vars) && exit_error("Pthread error"));
	waitpid(-1, &wstatus, 0);
	wstatus = WEXITSTATUS(wstatus);
	wstatus == 1 && kill_processes(&vars);
	if (wstatus == 2)
	{
		vars.eat_cntr++;
		if (vars.eat_cntr == vars.philo_nbr)
			kill_processes(&vars);
	}
	free_mem(&vars);
	return (0);
}
