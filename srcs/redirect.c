#include "../includes/sh.h"

t_pipe	*make_list(char **input)
{
	int 	x;
	int 	start;
	int		end;
	t_pipe	*pipe;

	x = 0;
	start = 0;
	pipe = NULL;
	while (input[x] != 0)
	{
		if (input[x][0] == '|' || input[x + 1] == 0)
		{
			end = x - 1;
			if (!pipe)
				pipe = new_list(input, start, end);
			else
				add_list(pipe, input, start, end);
			start = x + 1;
		}
		x++;
	}
	return (pipe);
}

int		redirect_present(char **input)
{
	int x;

	x = 0;
	while (input[x])
	{
		if (input[x][0] == '>' || input[x][0] == '<')
			return (1);
		else if (input[x][0] == '|')
			return (1);
		x++;
	}
	return (0);
}

void	redirect_out(t_pipe *tmp)
{
	int		fd;
	int		rval;

	fd = 1;
	rval = access(tmp->output_arg, R_OK);
	if (tmp->type[1] == '\0' && rval == 0)
		fd = open(tmp->output_arg, O_WRONLY | O_TRUNC);
	else if (tmp->type[1] == '\0')
		fd = open(tmp->output_arg, O_WRONLY | O_CREAT | O_EXCL);
	else if (tmp->type[1] == '>' && rval == 0)
		fd = open(tmp->output_arg, O_WRONLY | O_APPEND);
	else if (tmp->type[1] == '>')
		fd = open(tmp->output_arg, O_WRONLY | O_CREAT | O_EXCL);
	dup2(fd, 1);
}

void	redirect_in(t_pipe *tmp)
{
	int		fd;

	if (tmp->input_arg)
	{
		fd = open(tmp->input_arg, O_RDONLY);
		dup2(fd, 0);
	}/*
	else if (tmp->type[1] == '<' && tmp->next && tmp->next->argv && tmp->next->argv[0])
	{
	Work on this after you eat some food.	
	}*/
}

void	execute_cmd(t_mini *env, t_pipe *tmp)
{
	if (tmp->input_arg)
		redirect_in(tmp);
	if (tmp->output_arg)
		redirect_out(tmp);
	run_program(env, tmp->argv);
	dup2(env->stdo_fd, 1);
	dup2(env->stdi_fd, 0);
}

void	process_redirect(t_mini *env, char **input)
{
	t_pipe	*redirect;
	t_pipe	*tmp;

	redirect = make_list(input);
	tmp = redirect;
	while (tmp)
	{
		if (tmp->argv && tmp == redirect)
			execute_cmd(env, tmp);
		tmp = tmp->next;
	}
	delete_list(redirect);
}
