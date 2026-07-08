/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:26:49 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/08 18:17:13 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

bool sat(const std::string &formula) {
	std::unique_ptr<ASTNode> root = build_ast(formula);
	std::set<char>			 var_set;
	collect_variables(root.get(), var_set);
	std::vector<char> vars(var_set.begin(), var_set.end());
	int				  n = vars.size();

	for (int i = 0; i < (1 << n); i++) {
		std::map<char, bool> assignment;

		for (int j = 0; j < n; j++) {
			bool bit			= (i >> (n - 1 - j)) & 1;
			assignment[vars[j]] = bit;
		}
		if (eval_with_assignment(root.get(), assignment) == 1)
			return true;
	}
	return false;
}
