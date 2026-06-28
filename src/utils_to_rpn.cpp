/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_rpn.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:07:00 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:13:24 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

inline void to_rpn(const ASTNode *node, std::string &out) {
	if (node->is_leaf()) {
		out += (node->type == NodeType::Const) ? (node->value ? '1' : '0')
											   : node->symbol;
		return;
	}

	to_rpn(node->left.get(), out);
	if (!node->is_unary())
		to_rpn(node->right.get(), out);

	switch (node->type) {
	case NodeType::Not:
		out += '!';
		break;
	case NodeType::And:
		out += '&';
		break;
	case NodeType::Or:
		out += '|';
		break;
	case NodeType::Xor:
		out += '^';
		break;
	case NodeType::Implies:
		out += '>';
		break;
	case NodeType::Iff:
		out += '=';
		break;
	default:
		break;
	}
}

std::string to_rpn(const ASTNode *node) {
	std::string out;
	to_rpn(node, out);
	return out;
}
