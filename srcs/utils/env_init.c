/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:29:32 by myokono           #+#    #+#             */
/*   Updated: 2025/04/16 21:54:31 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_env_str(char *env_str, char **key, char **value)
{
	char	*equals_pos;

	equals_pos = ft_strchr(env_str, '=');
	if (!equals_pos)
	{
		*key = ft_strdup(env_str);
		*value = ft_strdup("");
		return ;
	}
	*key = ft_substr(env_str, 0, equals_pos - env_str);
	*value = ft_strdup(equals_pos + 1);
}

static t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	char	*key;
	char	*value;

	split_env_str(env_str, &key, &value);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env_list(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	t_env	*last_node;
	int		i;

	env_list = NULL;
	last_node = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_env_list(env_list);
			return (NULL);
		}
		if (!env_list)
			env_list = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
		i++;
	}
	return (env_list);
}

static int	count_env_nodes(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env_list)
{
	t_env	*current;
	char	**env_array;
	int		i;
	char	*tmp;

	env_array = malloc(sizeof(char *) * (count_env_nodes(env_list) + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		if (!tmp)
			return (free_array(env_array), NULL);
		env_array[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!env_array[i])
			return (free_array(env_array), NULL);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
