/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaazaa <yzaazaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:28:46 by asnaji            #+#    #+#             */
/*   Updated: 2024/02/19 19:11:40 by yzaazaa          ###   ########.fr       */
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
		ft_exit(NULL);
	putitoa(neg, len, str, nb);
	return (str);
}

static int	check_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;
	long	tmp;

	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = check_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = (res * 10) + (str[i] - '0');
		if (res > tmp && sign == 1)
			return (-1);
		else if (res > tmp && sign == -1)
			return (0);
		res = tmp;
		i++;
	}
	return (res * sign);
}