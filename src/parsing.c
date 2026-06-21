/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:44:36 by jfox              #+#    #+#             */
/*   Updated: 2026/06/21 18:01:40 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//goes thru the word until the end to find the last char
static int find_end_word(char *value, int i)
{
    while (value[i] && value[i] != ' ' && value[i] != '\t'
        && input[i] != '|' && input[i] != '<' && input[i] != '>')
        i++;
}

// Our Helper for get_type. Returns Enum. (!!!Other Specials Handled Later!!!)
static t_token_type get_type(char *value, int i)
{
    if (value[i] == '|')
        return (PIPE);
    if (value[i] == '<')
        return (REDIR_IN);
    if (value[i] == '>')
        return (REDIR_OUT);
    return (WORD);
}

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
    int word_start;
    int i;


    head = NULL;
    tail = NULL;
    word_start = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == ' ' || input[i] == '\t')
            i++;
        else
        {
        /*
            //First thing is we need to determine if we are looking at a:
             SPECIAL ; WORD;
            If Special:
                    It is either '|', '<', '>' (!!!Other Specials will be handled later!!!)
            If !Special:
                    WORD
        */
            word_start = i;
            if (input[i] == '|' || input[i] == '<' || input[i] == '>')
                i++;
            else
                i = find_end_word(input, i);
            new = make_new_token(get_type(input, word_start),
                    ft_substr(input, start, i - start));
            if (!new)
                return (NULL);  // ! TO-DO: Free tokens list on error
            if (!head)
            {
                head = new;
                tail = new;
            }
            else
            {
                tail->next = new;
                tail = tail->next;
            }   
        }
    }
    return (head);
} 

