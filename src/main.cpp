/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:25:21 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/13 16:39:10 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

int main(void) {
	std::cout << "\n===         Adder         ===\n";
	test_adder();
	std::cout << "\n===       Multiplier      ===\n";
	test_multiplier();
	std::cout << "\n===       Gray Code       ===\n";
	test_gray_code();

	return (0);
}
