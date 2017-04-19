/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:05:02 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/23 09:27:01 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

extern char **g_environ;

void	uninit(t_mini *env, char ***all)
{
	if (env->path)
		ft_strdel(&env->path);
	if (env->my_environ)
		del_old_env(env);
	if (all)
		del_split(all);
	ft_memdel((void *)env);
}

void	p_arse(t_mini *env, char ***all, char **split)
{
	if (ft_strcmp(split[0], "exit") == 0)
	{
		del_split(all);
		ft_printf("[.blue.Goodbye.][.red. :).]");
		exit(0);
	}
	if (ft_strcmp(split[0], "cd") == 0)
		cd_main(env, split);
	else if (ft_strcmp(split[0], "env") == 0)
		display_env(env);
	else if (env_check(split))
		env_main(env, split);
	else if (split && split[0])
		run_program(env, split);
	else if (split && split[0])
		ft_printf("[.blue.rsh: command not found:.] %s\n", split[0]);
}

t_mini	*init_env(int argc, char **argv, char **environ)
{
	t_mini	*env;

	argv = 0;
	argc = 0;
	env = (t_mini *)ft_memalloc(sizeof(t_mini));
	env->my_environ = get_env(environ);
	env->path = ft_strdup("/bin/");
	env->pat = get_index(environ, "PATH", 4);
	env->pwd = get_index(environ, "PWD", 3);
	env->home = get_index(environ, "HOME", 4);
	env->old_pwd = get_index(environ, "OLDPWD", 6);
	env->stdo_fd = dup(1);
	env->stdi_fd = dup(0);
	return (env);
}

int	main(int argc, char **argv, char **environ)
{
	char	*line;
	char	***formatted_input;
	t_mini	*env;
	int 	x;

	x = 0;
	env = init_env(argc, argv, environ);	
	ft_printf("[.cyan.%s$> .]", env->my_environ[env->pwd] + 4);
	while (get_next_line(0, &line))
	{
		formatted_input = input_management(line);
		ft_strdel(&line);
		while (formatted_input[x])
		{
			if (redirect_present(formatted_input[x]))
				process_redirect(env, formatted_input[x]);
			else if (formatted_input[x] && formatted_input[x][0])
				(p_arse(env, formatted_input, formatted_input[x]));
			x++;
		}
		del_split(formatted_input);
		x = 0;
		ft_printf("[.green.%s$> .]", env->my_environ[env->pwd] + 4);
	}
	return (0);
}
