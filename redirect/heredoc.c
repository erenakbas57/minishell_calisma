/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:10:19 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:11:50 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
"close_heredoc" fonksiyonu bir signal handler fonksiyonu olarak görünüyor ve 
SIGINT sinyalini yakaladığında çalışır. İşlevi, g_ms değişkeninin "ignore" 
özelliğini TRUE yapmak ve bir satır sonu eklemek için STDIN_FILENO için 
ioctl çağrısı yapmaktır.
*/
void	close_heredoc(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

/*
"heredoc" adında bir fonksiyon tanımlanmış. Bu fonksiyon, verilen bir son satır 
metni (endline) kadar kullanıcıdan girdi alır ve bu girdileri bir pipe üzerinden 
bir dosyaya yazdırır. Kullanıcı, herhangi bir zaman bu girdi işlemini sonlandırmak 
için son satır metnini girene kadar girdi almaya devam eder. Bu girdiler "heredoc>> " 
yazısıyla kullanıcıya gösterilir ve SIGINT sinyalini yakalandığında fonksiyon sonlanır.
*/
void	heredoc(int *fd, char *endline)
{
	char		*input;
	static int	start = 0;

	if (start)
	{
		start = 1;
		close(fd[0]);
		close(fd[1]);
	}
	if (pipe(fd) < 0)
		return (perror("minishell"));
	while (1)
	{
		signal(SIGINT, &close_heredoc);
		input = readline("heredoc>> ");
		if (!input || ft_strcmp(input, endline) || g_ms.ignore)
		{
			free(input);
			break ;
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
	close(fd[1]);
}
