/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:27:12 by oabdelka          #+#    #+#             */
/*   Updated: 2025/01/04 17:35:10 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	merge_token_content(t_tokens **tmp, const char *data)
// {
// 	/* 
// 	 * Merge 'data' into the existing (*tmp)->content.
// 	 * Make sure ft_strjoingnl handles freeing old content internally 
// 	 * or is otherwise leak-free.
// 	 */
// 	(*tmp)->content = ft_strjoingnl((*tmp)->content, data);
// }

// void	append2(t_tokens **tmp, char *data, int type)
// {
// 	/*
// 	** We only create a new token with " " if 
// 	** we have a WORD/COMMAND -> space -> WORD/COMMAND scenario.
// 	*/
// 	if ((*tmp)->id == TOKEN_SPACE && type == TOKEN_SPACE)
// 	{
// 		/* Double space scenario - do nothing */
// 		return;
// 	}

// 	/* 
// 	 * If we have WORD/COMMAND merging with another WORD/COMMAND, 
// 	 * we just merge them in the same token content.
// 	 */
// 	if (((*tmp)->id == TOKEN_COMMAND || (*tmp)->id == TOKEN_WORD)
// 		&& (type == TOKEN_WORD || type == TOKEN_COMMAND))
// 	{
// 		merge_token_content(tmp, data);
// 	}
// 	/*
// 	 * Else if we’re transitioning from a non-space token (WORD/COMMAND) 
// 	 * to another WORD/COMMAND, but the old token is not space, 
// 	 * we insert an explicit space token in between, 
// 	 * then add the new token (like "ls" + " " + "something").
// 	 */
// 	else if ((type != TOKEN_SPACE)
// 		&& (type == TOKEN_WORD || type == TOKEN_COMMAND)
// 		&& (*tmp)->id != TOKEN_SPACE)
// 	{
// 		t_tokens *space_token = newnode(ft_strdup(" "), TOKEN_SPACE);
// 		space_token->error = 0;

// 		/* Link the space token after (*tmp) */
// 		(*tmp)->next = space_token;
// 		space_token->previous = (*tmp);

// 		/* Move '(*tmp)' to this newly created space token */
// 		(*tmp) = (*tmp)->next;

// 		/* Now append the actual 'data' token after that space token */
// 		addnode(tmp, data, type);
// 	}
// 	else
// 	{
// 		/* In any other scenario, just add a new node with 'data'. */
// 		addnode(tmp, data, type);
// 	}
// }

// void	append(t_tokens **cmds, char *data, int type)
// {
// 	t_tokens *tmp;
// 	t_tokens *new_node;
// 	char	 *dup_data = NULL;

// 	new_node = NULL;

// 	/* 
// 	** 1. Special case for '' or "" tokens with length 2 => 
// 	**    transform them into an empty string
// 	*/
// 	if ((!ft_strcmp(data, "\'\'") || !ft_strcmp(data, "\"\""))
// 		&& ft_strlen(data) == 2)
// 	{
// 		dup_data = ft_strdup("");
// 		if (!dup_data)
// 			return;
// 		data = dup_data;
// 	}

// 	/* 
// 	** 2. If the list is empty, we create the first token plus a "START" token
// 	*/
// 	if (*cmds == NULL)
// 	{
// 		new_node = newnode(data, type);
// 		new_node->previous = newnode("START", TOKEN_START);
// 		new_node->error = 0;
// 		*cmds = new_node; /* The main list now points to new_node */

// 		if (dup_data)
// 		{
// 			free(dup_data);
// 			dup_data = NULL;
// 		}
// 		return;
// 	}

// 	/*
// 	** 3. Otherwise, find the end of the token list
// 	*/
// 	tmp = *cmds;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;

// 	/*
// 	** 4. Call append2 to handle merging or adding tokens
// 	*/
// 	append2(&tmp, data, type);

// 	/* 
// 	** 5. If we allocated a dup_data, free it now 
// 	**    because 'data' has been used or merged 
// 	*/
// 	if (dup_data)
// 	{
// 		free(dup_data);
// 		dup_data = NULL;
// 	}
// }

void	append2(t_tokens **tmp, char *data, int type)
{
	t_tokens	*new_node;

	new_node = NULL;
	if ((*tmp)->id == TOKEN_SPACE && type == TOKEN_SPACE)
		return ; //for double space
	if (((*tmp)->id == TOKEN_COMMAND || (*tmp)->id == TOKEN_WORD)
		&& (type == TOKEN_WORD || type == TOKEN_COMMAND))
		(*tmp)->content = ft_strjoingnl((*tmp)->content, data); //Merge if same type
	else if ((type != TOKEN_SPACE && (type == TOKEN_WORD
				|| type == TOKEN_COMMAND) && (*tmp)->id != TOKEN_SPACE))
	{
		new_node = newnode(ft_strdup(" "), TOKEN_SPACE);
		new_node->error = 0;
		(*tmp)->next = new_node;
		new_node->previous = (*tmp);
		(*tmp) = (*tmp)->next;
		addnode(tmp, data, type);
	}
	else
		addnode(tmp, data, type);
}

void	append(t_tokens **cmds, char *data, int type)
{
	t_tokens	*tmp;
	t_tokens	*new_node;
	char* 		dup_data= NULL;
	new_node = NULL;
	if ((!ft_strcmp(data, "\'\'") || !ft_strcmp(data, "\"\""))
		&& ft_strlen(data) == 2)
		{
 		    dup_data = ft_strdup("");
    		if (!dup_data)
        		return;
    		data = dup_data;
		}
		// printf("Command %s not found\n",data);
		// return;

	if (*cmds == NULL)
	{
		new_node = newnode(data, type);
		new_node->previous = newnode("START", TOKEN_START);
		new_node->error = 0;
		*cmds = new_node;
		if (dup_data)
			{
    			free(dup_data);
    			dup_data = NULL;
			}
		return ;
	}
	tmp = *cmds;
	while (tmp->next != NULL)
		tmp = tmp->next;
	append2(&tmp, data, type);
	if (dup_data)
			{
    			free(dup_data);
    			dup_data = NULL;
			}
}

t_tokens	*newnode(char *data, int type)
{
	t_tokens	*ptr;

	ptr = malloc(sizeof(t_tokens));
	if (ptr == NULL)
		return (NULL);
	ptr->content = ft_strdup(data);
	if (ptr->content == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptr->id = type;
	ptr->next = NULL;
	ptr->previous = NULL;
	ptr->error = 0;
	return (ptr);
}

void	addnode(t_tokens **tmp, char *data, int type)
{
	t_tokens	*new_node;

	new_node = newnode(data, type);
	new_node->error = 0;
	(*tmp)->next = new_node;
	new_node->previous = (*tmp);
}

