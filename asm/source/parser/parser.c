/*
** parser.c for asm in /home/grange_c/rendu/cpe/CPE_2015_corewar/asm/source/parser/
**
** Made by Benjamin Grange
** Login   <grange_c@epitech.net>
**
** Started on  Tue Feb 23 23:29:49 2016 Benjamin Grange
** Last update Fri Mar 25 15:42:11 2016 Benjamin Grange
*/

#include "parser.h"
#include "lexer.h" /* FIXME */

void			create_parser(t_parser *parser,
				      t_file_reader *fr,
				      t_token_list *list)
{
  my_memset(parser, 0, sizeof(t_parser));
  parser->tokenlist = list;
  parser->tkn = list;
  parser->reader = fr;
  parser->is_empty = true;
  parser->program.is_valid = true;
  parser->program.file_name = fr->file->name;
}

t_bool			parse_current_token(t_parser *parser)
{
  t_token		*tkn;
  t_parseres		res;

  tkn = get_next_token(parser);
  if (tkn->type != TOKEN_TYPE_EOL)
    {
      res = parse_all_token(parser, tkn);
      if (res.type == RESULT_PARSE_ERROR)
	{
	  print_syntax_error(parser->reader, &res.syntax_error, NULL);
	  return (true);
	}
      return (verify_EOL(parser));
    }
  return (false);
}

t_program		parser(t_token_list *token_list,
			       t_program_file *fr,
			       t_bool parse)
{
  t_parser		parser;
  t_file_reader		file_reader;

  my_putstr("Let's parse !\n");
  if (parse)
    {
      delete_all_comments(&token_list);
      file_reader = generate_file_reader(fr);
      create_parser(&parser, &file_reader, token_list);
      if (!pre_compile_label_declaration(&parser))
	return (parser.program);
      while (has_next_token(&parser) && parser.program.is_valid)
	{
	  parse_whitespace(&parser);
	  if (!has_next_token(&parser)
	      || parse_current_token(&parser))
	    parser.program.is_valid = false;
	  parse_whitespace(&parser);
	}
      raise_final_warnings_errors(&parser);
      my_putstr("Done !\n");
    }
  free_token_list(token_list);
  return (parser.program);
}
