/*
** init.c for  in /blinux_home/huot_b/rendus/CPE/CPE_2015_corewar/corewar/source/launch
** 
** Made by Flora Huot
** Login   <huot_b@epitech.net>
** 
** Started on  Tue Mar 22 14:41:29 2016 Flora Huot
** Last update Tue Mar 22 17:03:30 2016 Jakob Kellendonk
*/

#include "application.h"
#include "error.h"
#include "flag.h"
#include "my_mem.h"

int	create_prog_info(t_info_list **new)
{
  *new = malloc(sizeof(t_info_list));
  if (*new == NULL)
    return (print_error(ERROR_MALLOC_FAILED, NULL));
  (*new)->file_name = NULL;
  (*new)->live_code = -1;
  (*new)->address = -1;
  (*new)->next = NULL;
  return (0);
}

int		handle_option_flag(t_args *args, char **flags)
{
  int		*target;

  if (!my_strcmp(*flags, "-a"))
    target = &args->program_list->address;
  else if (!my_strcmp(*flags, "-n"))
    target = &args->program_list->live_code;
  else if (!my_strcmp(*flags, "-dump"))
    target = &args->constants->dump_cycle;
  else
    return (print_error(ERROR_UNKNOWN_OPTION, *flags));
  if (!flags[1])
    return (print_error(ERROR_MISSING_NUMBER, *flags));
  return (set_option_flag(args, flags, target));
}
