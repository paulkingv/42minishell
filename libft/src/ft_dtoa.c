/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pking <pking@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 18:35:17 by pking             #+#    #+#             */
/*   Updated: 2026/08/23 19:00:51 by pking            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// double to ascii

static int num_size(int n)
{
        int n_len;

		n_len = 0;
        if (n <= 0)
                n_len++;
        while(n != 0)
        {
                n_len++;
                n = n / 10;
        }
        return (n_len);
}

static void fill_itoa(int n, int len, char *nb)
{
        while (n != 0)
        {
                nb[len] = ((n % 10) + '0');
                n /= 10;
                len--;
        }
}

char	*ft_itoa(int n)
{
	char	*ascii_num;
	int		n_len;

	if (n == -2147483648)
		ft_strdup("-2147483648");
	n_len = num_size(n);
	ascii_num = malloc(sizeof(char) * (n_len + 1));
	if (!ascii_num)
		return (NULL);
	ascii_num[n_len] = '\0';
	else if (n < 0) 
	{
		n *= -1;
		fill_itoa(n, n_len - 1, ascii_num);
		ascii_num[0] = '-';
	}
	else 
		fill_itoa(n, n_len - 1, ascii_num);
	return (ascii_num);
}