/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negation_normal_form.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:12:01 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:14:52 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

std::string negation_normal_form(const std::string &formula) {
	std::unique_ptr<ASTNode> root = build_ast(formula);

	std::unique_ptr<ASTNode> nnf_root = root->clone();
	nnf_root						  = transform_to_nnf(nnf_root.get());
	std::string result				  = to_rpn(nnf_root.get());
	return result;
}

std::unique_ptr<ASTNode> transform_to_nnf(const ASTNode *node) {
	if (!node)
		throw InvalidFormulaException();

	if (node->is_leaf())
		return node->clone();

	if (node->type == NodeType::Not) {
		const ASTNode *child = node->left.get();
		if (!child)
			throw InvalidFormulaException();

		if (child->type == NodeType::Not) {
			if (!child->left)
				throw InvalidFormulaException();
			return transform_to_nnf(child->left.get());
		}
		if (child->type == NodeType::And) {
			auto left	  = child->left->clone();
			auto not_left = ASTNode::make_unary(NodeType::Not, std::move(left));
			auto right	  = child->right->clone();
			auto not_right =
				ASTNode::make_unary(NodeType::Not, std::move(right));
			auto new_node = ASTNode::make_binary(
				NodeType::Or, std::move(not_left), std::move(not_right));
			return transform_to_nnf(new_node.get());
		}
		if (child->type == NodeType::Or) {
			auto left	  = child->left->clone();
			auto not_left = ASTNode::make_unary(NodeType::Not, std::move(left));
			auto right	  = child->right->clone();
			auto not_right =
				ASTNode::make_unary(NodeType::Not, std::move(right));
			auto new_node = ASTNode::make_binary(
				NodeType::And, std::move(not_left), std::move(not_right));
			return transform_to_nnf(new_node.get());
		}

		if (child->type == NodeType::Implies) {
			auto left	  = child->left->clone();
			auto not_left = ASTNode::make_unary(NodeType::Not, std::move(left));
			auto right	  = child->right->clone();
			auto new_node = ASTNode::make_binary(
				NodeType::Or, std::move(not_left), std::move(right));
			auto new_not_node =
				ASTNode::make_unary(NodeType::Not, std::move(new_node));
			return transform_to_nnf(new_not_node.get());
		}

		if (child->type == NodeType::Iff) {
			auto left	  = child->left->clone();
			auto tmp_left = child->left->clone();
			auto not_left =
				ASTNode::make_unary(NodeType::Not, std::move(tmp_left));
			auto right	   = child->right->clone();
			auto tmp_right = child->right->clone();
			auto not_right =
				ASTNode::make_unary(NodeType::Not, std::move(tmp_right));
			auto new_left = ASTNode::make_binary(
				NodeType::Or, std::move(not_left), std::move(right));
			auto new_right = ASTNode::make_binary(NodeType::Or, std::move(left),
												  std::move(not_right));
			auto new_node  = ASTNode::make_binary(
				 NodeType::And, std::move(new_left), std::move(new_right));
			return transform_to_nnf(new_node.get());
		}

		auto new_child = transform_to_nnf(child);
		return ASTNode::make_unary(NodeType::Not, std::move(new_child));
	}

	if (node->type == NodeType::Implies) {
		auto left	  = node->left->clone();
		auto not_left = ASTNode::make_unary(NodeType::Not, std::move(left));
		auto right	  = node->right->clone();
		auto new_node = ASTNode::make_binary(NodeType::Or, std::move(not_left),
											 std::move(right));
		return transform_to_nnf(new_node.get());
	}

	if (node->type == NodeType::Iff) {
		auto left	  = node->left->clone();
		auto tmp_left = node->left->clone();
		auto not_left = ASTNode::make_unary(NodeType::Not, std::move(tmp_left));
		auto right	  = node->right->clone();
		auto tmp_right = node->right->clone();
		auto not_right =
			ASTNode::make_unary(NodeType::Not, std::move(tmp_right));
		auto new_left  = ASTNode::make_binary(NodeType::Or, std::move(not_left),
											  std::move(right));
		auto new_right = ASTNode::make_binary(NodeType::Or, std::move(left),
											  std::move(not_right));
		auto new_node = ASTNode::make_binary(NodeType::And, std::move(new_left),
											 std::move(new_right));
		return transform_to_nnf(new_node.get());
	}

	auto left_nnf  = transform_to_nnf(node->left.get());
	auto right_nnf = transform_to_nnf(node->right.get());
	return ASTNode::make_binary(node->type, std::move(left_nnf),
								std::move(right_nnf));
}

static void compare_truth_table_rpn_nnf(std::string s, int mode = NORMAL_MODE);

void test_negation_normal_form(void) {
	std::string answer;
	std::cout << "Enter interactive mode ? (y/n) ";
	std::cin >> answer;
	std::cin.ignore();

	if (answer == "n") {
		compare_truth_table_rpn_nnf("AB&!");
		compare_truth_table_rpn_nnf("AB=");
		compare_truth_table_rpn_nnf("AB|C=!D>");
	} else {
		std::cout << "p.s. enter 'n' to quit\n";
		while (1) {
			std::string s;

			std::cout << "> ";
			std::getline(std::cin, s);
			if (std::cin.eof()) {
				std::cout << std::endl;
				return;
			}
			if (s == "n")
				break;
			compare_truth_table_rpn_nnf(s, INTERACTIVE_MODE);
		}
	}
}

static void compare_truth_table_rpn_nnf(std::string s, int mode) {
	std::string nnf;
	try {
		nnf = negation_normal_form(s);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		if (mode == INTERACTIVE_MODE)
			std::cout << "p.s. enter 'n' to quit\n";
		return;
	}
	std::cout << s << std::endl;
	print_truth_table(s);
	std::cout << std::endl;
	print_truth_table(nnf);
}
