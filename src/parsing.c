/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:44:36 by jfox              #+#    #+#             */
/*   Updated: 2026/06/20 17:20:30 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper Function to make a New Token Node
t_token make_new_token(t_token_type type, char *value)
{
    new_token = ft_calloc(1, sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->type = type;
    new_token->value = value;
    new_token->next = NULL;
    return (new_token);
}

// Used to create a linked list of tokens
t_token tokenize(char *input)
{
    t_token *head;
    t_token *tail;
    int i;

    head = NULL;
    tail = NULL;
    i = 0;
    while (input[i])
    {
        if (input[i] == " " || input[i] == '\t')
            i++;
        else
        {
        /*
            Inside Here is the logic for parsing the words;

            //First thing is we need to determine if we are looking at a:
            WORD ; SPECIAL ; 
            If Word:
                        We need to know the beginning and end of the word,
                        to pass it to our Helper Function
            If Special:
        */

        
        }

    }
    return (head);
} 