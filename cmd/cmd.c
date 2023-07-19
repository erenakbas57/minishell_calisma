/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:58:46 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 14:10:03 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Fonksiyon, çalıştırılacak dahili bir komutun girdi ve çıktı dosyalarını geçici olarak değiştirerek, 
dahili komutun çalışmasını ve sonrasında orijinal girdi ve çıktı dosyalarının geri yüklenmesini sağlar. 
Bu işlemler şunları içerir:

1.  Girdi ve çıktı dosyalarını yedekler (in ve out değişkenlerinde).
2.  İşlem için girdi ve çıktı dosyalarını ayarlar (get_all_inputs ve set_all_outputs fonksiyonları).
3.  İçin belirlenen dahili komutu çalıştırır (run_builtin fonksiyonu).
4.  Girdi ve çıktı dosyalarını eski haline geri yükler (dup2 ile).
5.  Yedek dosyaları kapatır (close).

Bu fonksiyon, dahili bir komutun çalışması sırasında girdi ve çıktı dosyalarının geçici olarak 
değiştirilmesini ve dahili komutun tamamlanmasından sonra orijinal durumlarına geri döndürülmesini 
sağlar.
*/
void	get_builtin(t_process *process)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	get_all_inputs(process);
	set_all_outputs(process);
	run_builtin(process->execute);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

/*
1.  Tüm dosya tanımlayıcılarını kapatır (close_all_fd fonksiyonu).
2.  Bağlantı noktalarının listesi taranır (g_ms.process).
3.  Her işlem için (process), eğer pid -1 değilse, işlem tamamlanana kadar beklenir (waitpid).
4.  İşlem durumunun değerinin alınması ve errno değişkenine atanması (WEXITSTATUS).
5.  Sonraki işlem (process->next) taranır.

Bu fonksiyon, shell programı tarafından başlatılan tüm işlemlerin tamamlanmasını bekler 
ve errno değişkeninde her işlem için çıkış durumunu tutar.
*/
void	wait_cmd(void)
{
	t_process	*process;

	process = g_ms.process;
	close_all_fd();
	while (process)
	{
		if (process->pid != -1)
		{
			waitpid(process->pid, &errno, 0);
			errno = WEXITSTATUS(errno);
		}
		process = process->next;
	}
}

/*
1.  Bağlantı noktalarının listesi taranır (g_ms.process).
2.  Eğer liste boşsa, fonksiyon dönüş yapar.
3.  Tüm heredoc (g_ms.process) doldurulur (fill_all_heredoc fonksiyonu).
4.  Eğer g_ms.ignore true ise, tüm dosya tanımlayıcıları kapatılır ve fonksiyon dönüş yapar (close_all_fd).
5.  Eğer tek işlem varsa ve bu işlem bir built-in komut ise (is_builtin fonksiyonu), get_builtin fonksiyonu çalıştırılır.
6.  Bağlantı noktalarının listesi taranır ve her işlem için run_cmd fonksiyonu çalıştırılır.
7.  Tüm işlemlerin beklenmesi için wait_cmd fonksiyonu çalıştırılır.

Bu fonksiyon, shell programı tarafından verilen komutları çalıştırır ve sonuçları bekler. İşlem durumlarını wait_cmd 
fonksiyonu tarafından tutulur.
*/
void	start_cmd(void)
{
	t_process	*process;

	process = g_ms.process;
	if (!process)
		return ;
	fill_all_heredoc();
	if (g_ms.ignore)
		return (close_all_fd());
	if (is_builtin(process->execute[0]) && g_ms.process_count == 1)
	{
		get_builtin(process);
		process = process->next;
	}
	while (process)
	{
		run_cmd(process);
		process = process->next;
	}
	wait_cmd();
}
