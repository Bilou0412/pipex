#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
typedef struct s_data
{
	char	***cmds_args;
	char	**cmds_path;
	char	nb_cmd;
}			t_data;

typedef struct s_raw_data
{
	char	**argv;
	char	**envp;
	char	**dir_path;
}			t_raw_data;

int		init_data(t_data *data, int nb_cmd, char **argv, char **envp);

#endif