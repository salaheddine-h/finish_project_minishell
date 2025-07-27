/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/27 16:52:32 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_non_empty_args(t_cmd *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd->array[i])
	{
		if (ft_strlen(cmd->array[i]) > 0)
			count++;
		i++;
	}
	return (count);
}
void	copy_non_empty_args(t_cmd *cmd, char **filtered)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->array[i])
	{
		if (ft_strlen(cmd->array[i]) > 0)
		{
			filtered[j] = cmd->array[i];
			j++;
		}
		i++;
	}
	filtered[j] = NULL;
}
char	**filter_empty_args(t_cmd *cmd)
{
	char	**filtered;
	int		count;

	if (cmd->qflag == 0 || cmd->array == NULL)
		return (cmd->array);
	count = count_non_empty_args(cmd);
	filtered = malloc(sizeof(char *) * (count + 1));
	if (!filtered)
		return (cmd->array);
	copy_non_empty_args(cmd, filtered);
	return (filtered);
}

void execute_cmds(t_cmd *clist, t_shell *shell)
{
    int in_fd = 0;
    int pipe_fd[2];
    pid_t pids[100];
    int i = 0;
    char *cmd_path;
    char **filtered_args;
    char **envp = generate_envp_from_envlist(shell);

    while (clist)
    {
        if (clist->next)
            pipe(pipe_fd);

        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (in_fd != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            if (clist->next)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            setup_redirections(clist , shell);
            if (is_builtin(clist))
            {
                printf("Executing builtin command from exetuce_cmds : %s\n", clist->cmd);
                exit(execute_builtin(clist, shell));
            }
            cmd_path = find_path(clist->array[0], envp);
            if (!cmd_path)
            {
                printf("Command not found: %s\n", clist->array[0]);
                exit(127);
            }
            filtered_args = filter_empty_args(clist);
            execve(cmd_path, filtered_args, envp);
            exit(127);
        }
        if (in_fd != 0)
            close(in_fd);
        if (clist->next)
        {
            close(pipe_fd[1]);
            in_fd = pipe_fd[0];
        }
        clist = clist->next;
        i++;
    }

    int j = 0;
    while (j < i)
    {
        waitpid(pids[j], NULL, 0);
        j++;
    }
    ft_free_2d_array(envp);
}

