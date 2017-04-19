#include "../includes/sh.h"

char	*get_put(char **input, int in_n_out)
{
	int		x;
	char	*new;

	x = 0;
	new = NULL;
	while (input[x])
	{
		if (in_n_out == 0 && input[x][0] == '<' && input[x + 1])
			new = ft_strdup(input[x + 1]);
		else if (in_n_out == 1 && input[x][0] == '>' && input[x + 1])
			new = ft_strdup(input[x + 1]);
		x++;
	}
	return (new);
}

t_pipe 	*new_list(char **input, int start, int end)
{
	t_pipe	*new;

	new = (t_pipe *)ft_memalloc(sizeof(t_pipe));
	new->argv = ft_strndup2d(input, start, end);
	new->type = ft_strdup("0");
	new->input_arg = get_put(input, 0);
	new->output_arg = get_put(input, 1);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void 	add_list(t_pipe *pi, char **input, int start, int end)
{
	t_pipe	*tmp;

	tmp = pi;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_pipe *)ft_memalloc(sizeof(t_pipe));
	tmp->next->argv = ft_strndup2d(input, start, end);
	tmp->next->type = ft_strdup("0");
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
	tmp->next->input_arg = get_put(input, 0);
	tmp->next->output_arg = get_put(input, 1);
}

void	delete_list(t_pipe *pi)
{
	t_pipe	*tmp;

	tmp = pi;
	while (tmp)
	{
		pi = pi->next;
		if (tmp->type)
			ft_strdel(&tmp->type);
		if (tmp->argv)
		{
			ft_strdel2d(tmp->argv);
			ft_memdel((void*)&tmp->argv);
			tmp->argv = NULL;
		}
		tmp->next = NULL;
		tmp->prev = NULL;
		ft_memdel((void*)&tmp);
		tmp = pi;
	}
}
