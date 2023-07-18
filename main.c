/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:23 by fkaratay          #+#    #+#             */
/*   Updated: 2023/07/18 19:48:56 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_ms;

void	init_app(char **env)
{
	errno = 0;
	g_ms.paths = NULL;
	g_ms.parent_pid = getpid();
	set_env(env);
	set_paths();
}

void	set_env(char **env)
{
	size_t	i;
	size_t	len;
	char	**head;

	head = env; // env'i head (char **) dizisine attık
	while (*head) 
		head++;
	// "head" işaretçisini "env" dizisinde son elemandan bir sonraki hücreye taşır. 
	// Bu, "env" dizisinin sonunu belirlemek için kullanılır.
	
	len = head - env; // len'e env'deki çevre değişkeni sayısını atar.

	// len + 1 boyutunda bir char ** (iki boyutlu char dizisi) 
	//için bellek tahsis edin ve g_ms.env'ye atayın
	g_ms.env = ft_calloc(sizeof(char **), len + 1);
	
	i = -1;
	while (++i < len)
		g_ms.env[i] = ft_strdup(env[i]);
	// Bu döngüde, "env" dizisini dolaşarak her çevre değişkeni için 
	// bellek tahsis edilir ve değerleri kopyalanır. 
}

void	set_paths(void)
{
	char	*path;

	if (g_ms.paths)
		free_array(g_ms.paths);
	path = get_env("PATH");
	if (!(*path))
		g_ms.paths = NULL;
	else
		g_ms.paths = ft_split(path, ':');
	free(path);
}

void	init_shell(char *input)
{
	g_ms.token = NULL;
	g_ms.process = NULL;
	g_ms.process_count = 0;
	tokenize(input);
	if (!lexer())
		return ;
	start_cmd();
	free_process();
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_d(char *input){
	if (!input)
	{
		printf("exit\n");
		exit(errno);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_app(env); //(çevre değişkenlerini struct yapımıza almak için)
	
	while (ac && av)
	{
		g_ms.ignore = FALSE;
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		write(1, "\033[32m", 5);
		input = readline("minishell_> ");
		write(1, "\033[0m", 4);
		ctrl_d(input);
		if (g_ms.ignore)
		{
			free(input);
			input = malloc(1);
		}
		if (*input)
		{
			init_shell(input);
			add_history(input);
		}
		free(input);
	}
	exit(errno);
}
