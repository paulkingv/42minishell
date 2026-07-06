/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 15:44:36 by jfox              #+#    #+#             */
/*   Updated: 2026/07/05 19:59:37 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//goes thru the word until the end to find the last char
static int find_end_word(char *input, int i)
{
    while (input[i] && input[i] != ' ' && input[i] != '\t'
        && input[i] != '|' && input[i] != '<' && input[i] != '>')
        i++;
    return (i);
}

// Our Helper for get_type. Returns Enum. Single Char Checker. (!!!Other Specials Handled Later!!!)
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
t_token *make_new_token(t_token_type type, char *value)
{
   t_token *new_token;

    new_token = ft_calloc(1, sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->type = type;
    new_token->value = value;
    new_token->next = NULL;
    return (new_token);
}

// Used to create a linked list of tokens
        /*
            //First thing is we need to determine if we are looking at a:
             SPECIAL ; WORD;
            If Special:
                    It is either '|', '<', '>' (!!!Other Specials will be handled later!!!)
            If !Special:
                    WORD
        */
t_token *tokenize(char *input)
{
    t_token *head;
    t_token *tail;
    t_token *new;
    int word_start;
    int i;

    new = NULL;
    head = NULL;
    tail = NULL;
    word_start = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == ' ' || input[i] == '\t') // 9 - 13
            i++;
        else
        {
            word_start = i;
            if (input[i] == '|' || input[i] == '<' || input[i] == '>')
                i++;
            else
                i = find_end_word(input, i);
            new = make_new_token(get_type(input, word_start),
                    ft_substr(input, word_start, i - word_start));
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

