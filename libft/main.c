/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 08:11:18 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/25 11:35:32 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <limits.h>

int main()
{
	system("clear");
	long *p;
	long number;

	number = 150000;
	p = &number;

	/*
ft_printf("%+c<--\n", 0);
printf("%+c<--\n", 0);
*/	ft_printf("%o\n", 42);
	printf("%o\n\n", 42);
/*	ft_printf("before %o after\n", 42);
	printf("before %o after\n\n", 42);
	ft_printf("%o%o%o%o%o\n", 1, 100, 999, 42, 999988888);
	printf("%o%o%o%o%o\n\n", 1, 100, 999, 42, 999988888);
	ft_printf("a%ob%oc%od\n", 0, 55555, 100000);
	printf("a%ob%oc%od\n\n", 0, 55555, 100000);
	ft_printf("LONG_MAX O:%o<--\n", LONG_MAX);
	printf("LONG_MAX O:%o<--\n\n", LONG_MAX);
	ft_printf("{%3c}<--\n", 0);
	printf("{%3c}<--\n\n", 0);
	  ft_printf("zd-1:%zd<--\n", -1);
	  printf("zd-1:%zd<--\n\n", -1);
	  ft_printf(".2c:%.2c<--\n", NULL);
	  printf(".2c:%.2c<--\n\n", NULL);
	  ft_printf("@moulitest c: %c<--\n", 0);
	  printf("@moulitest c: %c<--\n\n", 0);
	  ft_printf("2c:%2c<--\n", 0);
	  printf("2c:%2c<--\n\n", 0);
	  ft_printf("null %c and text<--\n", 0);
 	  printf("null %c and text<--\n\n", 0);
	  ft_printf(" c:% c<--\n", 0);
	  printf(" c:% c<--\n", 0);
	*//*printf("u: %050u\n", 65);
	printf("x: %050x\n", 65);
	printf("o: %050o\n", 65);
	printf("c: %050c\n", 65);
	printf("s: %050s\n", "hello");
	printf("p: %050p\n", p);
*/
// precision makes sure to keep precision, but only allocates new memory if if needs to
// 0s don't care about changing 0s
	return (0);
}

// precision reigns over 0
// precision doesn't work with %c
// 0 in the beginning fills it with 0s
// space in the beginning puts a space
// space only works with %d
// + adds the sign to the number. can't be after 0
// + and space don't go together
// + only works with d
// + and - signs are added before numbers
// - switches tabulation
// - and 0 don't go together
// # on x and X keeps 
// more than one '.' is error
// 0 is always in position 0 or 1
// x, X and o ar all unsigned
// add n as well, returns how many characters have been written
// 
// precision: d, o, x, u
//
//
// plus:
// - works with: d
//
// zero: 
// -works with: d
// - ignored with - and .
//
// hashtag:
// -works with: o, x
// 
// minus:
// - works with all types
// - doesn't go with 0
