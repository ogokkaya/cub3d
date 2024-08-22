#include "../inc/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"

t_block	*malloc_starter(void)
{
	t_block	*block;

	block = ft_calloc(1, sizeof(t_block));
	if (!block)
		return (perror(MALLOC), exit(EXIT_FAILURE), NULL);
	return (block);
}

void	ft_lstadd_back_memory(t_block **lst, t_block *new)
{
	t_block	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_block	*ft_lstnew_memory(void *content)
{
	t_block	*new;

	new = malloc(sizeof(t_block));
	if (!new)
		return (0);
	new->allocate = content;
	new->next = NULL;
	return (new);
}

void	ft_lstdelone_memory(t_block *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->allocate);
	lst->allocate = NULL;
	free(lst);
}

void	ft_lstclear_memory(t_block **lst, void (*del)(void *))
{
	t_block	*ptr;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		ft_lstdelone_memory(*lst, del);
		*lst = ptr;
	}
	*lst = NULL;
}

int	my_malloc(t_block *block, void *address)
{
	t_block	*new_block;

	if (address != NULL)
	{
		if (block == NULL)
			return (free(address), FALSE);
		new_block = ft_lstnew_memory(address);
		if (new_block != NULL)
		{
			ft_lstadd_back_memory(&block, new_block);
			return (TRUE);
		}
		return (free(address), FALSE);
	}
	return (FALSE);
}
