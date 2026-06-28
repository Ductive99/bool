/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:22:12 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:44:06 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOL_H_
#define BOOL_H_

#include "ast.h"
#include "tests.h"
#include <bitset>
#include <set>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

#define i32 int32_t
#define u32 uint32_t

#define INTERACTIVE_MODE 1
#define NORMAL_MODE 0
 
// Adds `a + b` using only bitwise ops (`&`, `|`, `^`, `<<`, `>>`).
u32 adder(u32 a, u32 b);
// Multiplies `a * b` using only bitwise ops.
u32 multiplier(u32 a, u32 b);
// Converts integer `n` to its Gray code equivalent.
u32 gray_code(u32 n);
// Evaluates a propositional formula in **Reverse Polish Notation**.
bool eval_formula(const std::string &formula);
// Prints the truth table for a formula with variables `A-Z`
void print_truth_table(const std::string &formula);
// Converts a propositional formula to its negation normal form
std::string negation_normal_form(const std::string &formula);


// Utility functions
std::unique_ptr<ASTNode> transform_to_nnf(const ASTNode* node);
std::string	to_rpn(const ASTNode *node);

#endif /* BOOL_H_ */
