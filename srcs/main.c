#include "../include/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data data;
	int i;

	i = 0;
	if (init_data(&data, argc - 3, argv, envp))
		return (-1);
	while (data.cmds_path[i])
	{
		ft_printf("%s\n", data.cmds_path[i]);
		i++;
	}
}