/*
** program.h for  in /home/bazin_q/rendu/CPE/CPE_2015_corewar/corewar/include
** 
** Made by Quentin Bazin
** Login   <bazin_q@epitech.net>
** 
** Started on  Wed Mar 23 12:16:14 2016 Quentin Bazin
** Last update Wed Mar 23 12:16:14 2016 Quentin Bazin
*/
#ifndef PROGRAM_H_
# define PROGRAM_H_

# include "args.h"
# include "error.h"
# include "op.h"

struct s_application;

typedef struct		s_process
{
  int			cycles_left;
  int			carry;
  int			pc;
  unsigned char		registre[REG_SIZE][REG_NUMBER];
}			t_process;

typedef struct		s_program
{
  struct header_s	info;
  int			live;
  t_process		*processes;
  int			did_live;
}			t_program;

t_err	program_init(t_program *program, struct s_application *app,
		     t_info_list *list);

#endif /* !PROGRAM_H_ */
