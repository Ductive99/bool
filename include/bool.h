/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:22:12 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/08 15:46:03 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOL_H_
#define BOOL_H_

#include <cstdint>
#include <iostream>
#include <string>


#define i32	int32_t
#define u32	uint32_t

// Adds `a + b` using only bitwise ops (`&`, `|`, `^`, `<<`, `>>`).
u32	adder(u32 a, u32 b);
// Multiplies `a * b` using only bitwise ops.
u32	multiplier(u32 a, u32 b);
// Converts integer `n` to its Gray code equivalent.
u32 gray_code(u32 n);
// Evaluates a propositional formula in **Reverse Polish Notation**.
bool	eval_formula(std::string &formula);
// Prints the truth table for a formula with variables `A-Z`
void		print_truth_table(std::string &formula);
// ...

#endif /* BOOL_H_ */
