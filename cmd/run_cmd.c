/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:15:09 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 14:11:39 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
bir pipe (boru) mekanizması için gerekli dosya tanımlayıcılarını (file descriptors) 
yapılandırır. Aşağıdaki adımları gerçekleştirir:

1.  Eğer işlem bir listenin başındaysa, verilerin yazılacağı dosya tanımlayıcısı 
process->fd[1] olarak yapılandırılır.
2.  Eğer işlem bir listenin sonundaysa, verilerin okunacağı dosya tanımlayıcısı 
process->prev->fd[0] olarak yapılandırılır.
3.  Eğer işlem listenin başında veya sonunda değilse, verilerin okunacağı dosya
tanımlayıcısı process->prev->fd[0], verilerin yazılacağı dosya tanımlayıcısı 
ise process->fd[1] olarak yapılandırılır.

Bu fonksiyon, pipe mekanizmasının farklı bölümlerinde verilerin nasıl yazılacağı
 ve okunacağı hakkında bilgi sağlar.
*/
void	pipe_route(t_process *process)
{
	if (process->prev == NULL)
		dup2(process->fd[1], 1);
	else if (process->next == NULL)
		dup2(process->prev->fd[0], 0);
	else
	{
		dup2(process->prev->fd[0], 0);
		dup2(process->fd[1], 1);
	}
}

/*
1.  Verilerin okunacağı dosya tanımlayıcısı process->heredoc_fd[0] olarak yapılandırılır.
2.  Eğer işlem bir listenin sonundaysa, verilerin yazılacağı dosya tanımlayıcısı 
process->fd[1] olarak yapılandırılır.

Bu fonksiyon, "heredoc" mekanizmasının nasıl çalışacağı hakkında bilgi sağlar ve işlemin 
verilerin nasıl okunacağı ve yazılacağı hakkında bilgi verir.
*/
void	heredoc_route(t_process *process)
{
	dup2(process->heredoc_fd[0], 0);
	if (process->next != NULL)
		dup2(process->fd[1], 1);
}

/*
1.  Eğer işlem tek bir işlem değilse ve içerisinde "heredoc" mekanizması bulunuyorsa, 
heredoc_route fonksiyonu çağrılır ve işlemin verilerin okunması ve yazılması için 
gerekli dosya tanımlayıcıları yapılandırılır.
2.  Eğer "heredoc" mekanizması bulunmuyorsa, pipe_route fonksiyonu çağrılır ve işlemin 
verilerin okunması ve yazılması için gerekli dosya tanımlayıcıları yapılandırılır.
3.  get_all_inputs ve set_all_outputs fonksiyonları çağrılır ve işlemin girdileri ve 
çıktıları yapılandırılır.
4.  Tüm dosya tanımlayıcıları kapatılır.

Bu fonksiyon, işlemin nasıl yapılandırılacağını belirler ve işlemin girdilerinin ve 
çıktılarının nasıl yapılandırılacağı hakkında bilgi verir.
*/
void	cmd_route(t_process *process)
{
	if (g_ms.process_count > 1)
	{
		if (contain_heredoc(process))
			heredoc_route(process);
		else
			pipe_route(process);
	}
	get_all_inputs(process);
	set_all_outputs(process);
	close_all_fd();
}

/*
"run_cmd" fonksiyonu, belirtilen süreç için bir çocuk süreci oluşturur ve çocuk sürecinde 
belirtilen komutun yürütülmesini sağlar. İşlem yapılacak komut, belirtilen girdi ve çıktılar 
aracılığıyla yapılır ve çocuk süreci beklenir. Eğer komut bir "built-in" komut ise çocuk 
süreci tarafından direk çalıştırılır, değilse PATH değişkeni aracılığıyla komutun yolu 
bulunur ve execve fonksiyonu ile çalıştırılır. Eğer komut bulunamaz veya başka bir hata 
oluşursa, hata mesajı görüntülenir ve çocuk süreci sonlandırılır.
*/
void	run_cmd(t_process *process)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		cmd_route(process);
		run_builtin(process->execute);
		path = get_path(process->execute[0]);
		execve(path, process->execute, g_ms.env);
		command_err(process->execute[0]);
		exit(errno);
	}
	else
		process->pid = pid;
}
