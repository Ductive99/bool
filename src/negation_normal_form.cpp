/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negation_normal_form.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:12:01 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/26 20:08:02 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
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

inline std::string to_rpn(const ASTNode *node) {
	std::string out;
	to_rpn(node, out);
	return out;
}

std::string negation_normal_form(const std::string &formula) {
	std::unique_ptr<ASTNode> root = build_ast(formula);

	std::unique_ptr<ASTNode> nnf_root = root->clone();
	nnf_root						  = transform_to_nnf(nnf_root.get());
	std::string result				  = to_rpn(nnf_root.get());
	std::cout << result << std::endl;
	return result;
}

std::unique_ptr<ASTNode> transform_to_nnf(const ASTNode *node) {
	if (!node)
		throw InvalidFormulaException();

	if (node->is_leaf())
		return node->clone();

	if (node->is_unary()) {
		const ASTNode *child = node->left.get();
		if (!child)
			throw InvalidFormulaException();

		if (child->type == NodeType::Not) {
			if (!child->left)
				throw InvalidFormulaException();
			return transform_to_nnf(child->left.get());
		}

		auto new_child = transform_to_nnf(child);
		return ASTNode::make_unary(NodeType::Not, std::move(new_child));
	}

	if (node->type == NodeType::Implies) {
		auto left = node->left->clone();
		auto not_left = ASTNode::make_unary(NodeType::Not, std::move(left));
        auto right = node->right->clone();
        auto newf = ASTNode::make_binary(NodeType::Or, std::move(not_left), std::move(right));
        return transform_to_nnf(newf.get());
	}

	/*
	 * (A <=> B)	<=>	(A => B) & (B => A)
	 * 				<=>	(!A | B) & (A | !B)
	 */
    if (node->type == NodeType::Iff) {
    	auto left = node->left->clone();
    	auto tmp_left	= node->left->clone();
		auto not_left = ASTNode::make_unary(NodeType::Not, std::move(tmp_left));
		auto right = node->right->clone();
    	auto tmp_right = node->right->clone();
		auto not_right = ASTNode::make_unary(NodeType::Not, std::move(tmp_right));
		auto new_left = ASTNode::make_binary(NodeType::Or, std::move(not_left), std::move(right));
		auto new_right = ASTNode::make_binary(NodeType::Or, std::move(left), std::move(not_right));
		auto new_node = ASTNode::make_binary(NodeType::And, std::move(new_left), std::move(new_right));
		return transform_to_nnf(new_node.get());
    }
    
	// TODO: use De Morgan's laws and distributivity

	
	auto left_nnf  = transform_to_nnf(node->left.get());
	auto right_nnf = transform_to_nnf(node->right.get());
	return ASTNode::make_binary(node->type, std::move(left_nnf),
								std::move(right_nnf));
}

void	test_negation_normal_form(void)
{
	std::string answer;
	std::cout << "Enter interactive mode ? (y/n) ";
	std::cin >> answer;
	std::cin.ignore();

	if (answer == "n") {
		// TODO: write generic tests
		std::cout << "TODO: write tests" << std::endl;
	} else {
		std::cout << "p.s. enter 'n' to quit\n";
		while (1) {
			try {
				std::string s;

				std::getline(std::cin, s);
				if (s == "n")
					break;
				print_truth_table(s);
				print_truth_table(negation_normal_form(s));
			} catch (const std::exception &e) {
				std::cout << e.what() << std::endl;
				std::cout << "p.s. enter 'n' to quit\n";
			}
		}
	}
	
}
