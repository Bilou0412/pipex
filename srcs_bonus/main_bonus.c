/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:59:59 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/01 04:16:55 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5 || argc > 1024)
		return (ft_printf("parse error near `|'"), 0);
	if (check_files(&data, argc, argv, envp))
		return (0);
	if (check_cmds(&data))
		return (0);
	if (exec(&data))
		return (free_all(&data), 0);
	error_handler(&data);
	return (free_close(&data), 0);
}
