/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 04:42:22 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/15 22:52:15 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H_
#define AST_H_

#include <cctype>
#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>

enum class NodeType : char {
	Const,	  // leaf: boolean constant (0 or 1)
	Variable, // leaf: A-Z
	Not,	  // unary:  !
	And,	  // binary: &
	Or,		  // binary: |
	Xor,	  // binary: ^
	Implies,  // binary: >
	Iff		  // binary: =
};

inline int arity(NodeType t) {
	switch (t) {
	case NodeType::Const:
	case NodeType::Variable:
		return 0;
	case NodeType::Not:
		return 1;
	default:
		return 2;
	}
}

struct InvalidFormulaException : public std::runtime_error {
	InvalidFormulaException() : std::runtime_error("invalid formula") {}
};

struct EmptyFormulaException : public std::runtime_error {
	EmptyFormulaException() : std::runtime_error("empty formula") {}
};

struct MissingOperandException : public std::runtime_error {
	MissingOperandException(char op)
		: std::runtime_error(std::string("missing operand for operator '") +
							 op + "'") {}
};

struct MissingOperatorException : public std::runtime_error {
	MissingOperatorException()
		: std::runtime_error("missing operator (too many operands)") {}
};

struct InvalidTokenException : public std::runtime_error {
	InvalidTokenException(char token)
		: std::runtime_error(std::string("invalid token '") + token + "'") {}
};

struct ASTNode {
	NodeType type = NodeType::Const;

	bool value	= false;
	char symbol = 0;

	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;

	bool is_leaf() const { return arity(type) == 0; }
	bool is_unary() const { return arity(type) == 1; }
	bool is_binary() const { return arity(type) == 2; }

	static std::unique_ptr<ASTNode> make_const(bool v) {
		auto node	= std::make_unique<ASTNode>();
		node->type	= NodeType::Const;
		node->value = v;
		return node;
	}

	static std::unique_ptr<ASTNode> make_variable(char symbol) {
		auto node	 = std::make_unique<ASTNode>();
		node->type	 = NodeType::Variable;
		node->symbol = symbol;
		return node;
	}

	static std::unique_ptr<ASTNode> make_unary(NodeType					type,
											   std::unique_ptr<ASTNode> child) {
		auto node  = std::make_unique<ASTNode>();
		node->type = type;
		node->left = std::move(child);
		return node;
	}

	static std::unique_ptr<ASTNode>
	make_binary(NodeType type, std::unique_ptr<ASTNode> left,
				std::unique_ptr<ASTNode> right) {
		auto node	= std::make_unique<ASTNode>();
		node->type	= type;
		node->left	= std::move(left);
		node->right = std::move(right);
		return node;
	}

	std::unique_ptr<ASTNode> clone() const {
		auto node	 = std::make_unique<ASTNode>();
		node->type	 = type;
		node->value	 = value;
		node->symbol = symbol;
		if (left)
			node->left = left->clone();
		if (right)
			node->right = right->clone();
		return node;
	}
};

inline NodeType operator_node_type(char c) {
	switch (c) {
	case '!':
		return NodeType::Not;
	case '&':
		return NodeType::And;
	case '|':
		return NodeType::Or;
	case '^':
		return NodeType::Xor;
	case '>':
		return NodeType::Implies;
	case '=':
		return NodeType::Iff;
	default:
		throw InvalidFormulaException();
	}
}

inline std::unique_ptr<ASTNode> build_ast(const std::string &formula) {
	if (formula.empty())
		throw EmptyFormulaException();

	std::stack<std::unique_ptr<ASTNode>> stack;
	bool								 has_token = false;

	for (char c : formula) {
		if (std::isspace(static_cast<unsigned char>(c)))
			continue;

		has_token = true;

		if (c == '0' || c == '1') {
			stack.push(ASTNode::make_const(c == '1'));
		} else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			stack.push(ASTNode::make_variable(static_cast<char>(
				std::toupper(static_cast<unsigned char>(c)))));
		} else if (c == '!' || c == '&' || c == '|' || c == '^' || c == '>' ||
				   c == '=') {
			NodeType type	= operator_node_type(c);
			int		 needed = arity(type);

			if (static_cast<int>(stack.size()) < needed)
				throw MissingOperandException(c);

			if (needed == 1) {
				auto child = std::move(stack.top());
				stack.pop();
				stack.push(ASTNode::make_unary(type, std::move(child)));
			} else {
				auto right = std::move(stack.top());
				stack.pop();
				auto left = std::move(stack.top());
				stack.pop();
				stack.push(ASTNode::make_binary(type, std::move(left),
												std::move(right)));
			}
		} else {
			throw InvalidTokenException(c);
		}
	}

	if (!has_token)
		throw EmptyFormulaException();

	if (stack.size() != 1)
		throw MissingOperatorException();

	return std::move(stack.top());
}

/**
 * Generic recursive evaluator
 *
 * T			: result type
 * leaf			: how to interpret a leaf node in type T
 * apply_not	: how to negate in T
 * apply_bin	: how to apply the operator NodeType to two T values
 */
template <typename T, typename LeafFn, typename NotFn, typename BinaryFn>
T evaluate(const ASTNode *node, const LeafFn &leaf, const NotFn &apply_not,
		   const BinaryFn &apply_bin) {
	if (node->is_leaf())
		return leaf(*node);

	if (node->type == NodeType::Not)
		return apply_not(
			evaluate<T>(node->left.get(), leaf, apply_not, apply_bin));

	T l = evaluate<T>(node->left.get(), leaf, apply_not, apply_bin);
	T r = evaluate<T>(node->right.get(), leaf, apply_not, apply_bin);
	return apply_bin(node->type, l, r);
}

#endif /* AST_H_ */
