/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asnaji <asnaji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:28:46 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/14 16:32:46 by asnaji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	intlen(long long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*putitoa(size_t neg, size_t len, char *str, long long nb)
{
	if (nb < 0)
	{
		neg = 1;
		nb *= -1;
		str[0] = '-';
	}
	str[len] = '\0';
	while (len > neg)
	{
		str[len - 1] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long long	nb;
	size_t		len;
	size_t		neg;
	char		*str;

	neg = 0;
	nb = n;
	len = intlen(nb);
	if (nb < 0)
		len += 1;
	str = (char *)rad_malloc((len + 1) * sizeof(char), 0, OTHERS);
	if (!str)
		return (NULL);
	putitoa(neg, len, str, nb);
	return (str);
}