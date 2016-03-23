/*
** flag_handler.c for  in /home/kellen_j/rendu/CPE_2015_corewar/corewar
** 
** Made by Jakob Kellendonk
** Login   <kellen_j@epitech.net>
** 
** Started on  Mon Feb 29 12:51:47 2016 Jakob Kellendonk
** Last update Tue Mar 22 16:59:05 2016 Jakob Kellendonk
*/

#include "application.h"
#include "my_mem.h"

int	set_option_flag(t_args *args, char **flags, int *target)
{
  int	error;

  *target = my_getnbr_error(flags[1], &error);
  if (*target <= 0 && target == &args->constants->dump_cycle)
    return (print_error(ERROR_POSITIVE_NUMBER_EXPECTED, *flags));
  if (error)
    return (print_error(ERROR_INTEGER_EXPECTED, *flags));
  return (0);
}

int	set_default_values(t_args *args)
{
  args->constants = malloc(sizeof(t_constants));
  if (!args->constants)
    return (1);
  args->constants->dump_cycle = -1;
  args->cycle_to_die = CYCLE_TO_DIE;
  args->constants->cycle_delta = CYCLE_DELTA;
  args->constants->nbr_live = NBR_LIVE;
  return (0);
}

int	validate_args_state(t_args *args)
{
  if (args->program_list->live_code != -1 || args->program_list->address != -1)
    {
      my_putstr_out("Error: specified program's ", 2);
      if (args->program_list->live_code != -1)
	my_putstr_out("live number ", 2);
      if (args->program_list->live_code != -1
	  && args->program_list->address != -1)
	my_putstr_out("and ", 2);
      if (args->program_list->address != -1)
	my_putstr_out("starting address ", 2);
      my_putstr_out("but didn't specifie program's file.\n", 2);
      return (1);
    }
  return (0);
}
