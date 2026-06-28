/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truth_table.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 23:49:40 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:44:18 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

void collect_variables(const ASTNode *node, std::set<char> &vars) {
	if (!node)
		return;
	if (node->type == NodeType::Variable)
		vars.insert(node->symbol);
	collect_variables(node->left.get(), vars);
	collect_variables(node->right.get(), vars);
}

bool eval_with_assignment(const ASTNode				 *root,
						  const std::map<char, bool> &assignment) {
	return evaluate<bool>(
		root,

		[&assignment](const ASTNode &node) -> bool {
			if (node.type == NodeType::Const)
				return node.value;
			return assignment.at(node.symbol);
		},

		[](bool a) { return !a; },

		[](NodeType type, bool a, bool b) -> bool {
			switch (type) {
			case NodeType::And:
				return a && b;
			case NodeType::Or:
				return a || b;
			case NodeType::Xor:
				return a != b;
			case NodeType::Implies:
				return !a || b;
			case NodeType::Iff:
				return a == b;
			default:
				throw InvalidFormulaException();
			}
		});
}

void print_truth_table(const std::string &formula) {
	auto root = build_ast(formula);

	std::set<char> var_set;
	collect_variables(root.get(), var_set);
	std::vector<char> vars(var_set.begin(), var_set.end());
	int				  n = vars.size();

	for (char v : vars)
		std::cout << "| " << v << " ";
	std::cout << "| = |\n";

	for (int i = 0; i <= n; i++)
		std::cout << "|---";
	std::cout << "|\n";

	for (int i = 0; i < (1 << n); i++) {
		std::map<char, bool> assignment;

		for (int j = 0; j < n; j++) {
			bool bit			= (i >> (n - 1 - j)) & 1;
			assignment[vars[j]] = bit;
			std::cout << "| " << bit << " ";
		}

		bool result = eval_with_assignment(root.get(), assignment);
		std::cout << "| " << result << " |\n";
	}
}
