/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:11:14 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/11 14:20:20 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "bool.h"

static vector<i32> complement(const std::unordered_set<i32> &universal_set,
							  const vector<i32>				&a);
static std::unordered_set<i32>
			get_universal_set(const vector<vector<i32>> &set);
vector<i32> set_union(const vector<i32> &A, const vector<i32> &B);
vector<i32> set_intersection(const vector<i32> &A, const vector<i32> &B);

vector<i32> eval_set(const std::string &formula, vector<vector<i32>> &set) {
	std::unique_ptr<ASTNode> root	  = build_ast(formula);
	std::unique_ptr<ASTNode> nnf_root = transform_to_nnf(root.get());
	std::unordered_set<i32>	 universal_set(get_universal_set(set));

	auto leaf = [&set, &universal_set](const ASTNode &n) -> vector<i32> {
		if (n.type == NodeType::Const) {
			if (!n.value)
				return {};
			else {
				vector<i32> result;
				result.reserve(universal_set.size());
				for (const auto &n : universal_set)
					result.push_back(n);
				return result;
			}
		}
		size_t set_pos = n.symbol - 'A';
		if (set_pos > set.size())
			throw InvalidFormulaException();
		return set[set_pos];
	};

	auto apply_not = [&universal_set](const vector<i32> &a) -> vector<i32> {
		return complement(universal_set, a);
	};

	auto apply_bin = [](NodeType t, const vector<i32> &a,
						const vector<i32> &b) -> vector<i32> {
		switch (t) {
		case NodeType::And:
			return set_intersection(a, b);
		case NodeType::Or:
			return set_union(a, b);
		default:
			throw InvalidFormulaException();
		}
	};

	return evaluate<vector<i32>>(nnf_root.get(), leaf, apply_not, apply_bin);
}

static std::unordered_set<i32>
get_universal_set(const vector<vector<i32>> &set) {
	std::unordered_set<i32> seen;

	for (const auto &numbers_set : set) {
		for (const auto n : numbers_set) {
			auto it = seen.find(n);
			if (it == seen.end())
				seen.insert(n);
		}
	}
	return seen;
}

static vector<i32> complement(const std::unordered_set<i32> &universal_set,
							  const vector<i32>				&a) {
	std::unordered_set<i32> set_a(a.begin(), a.end());
	vector<i32>				complement;

	for (const auto n : universal_set) {
		auto it = set_a.find(n);
		if (it == set_a.end())
			complement.push_back(n);
	}
	return complement;
}

vector<i32> set_union(const vector<i32> &A, const vector<i32> &B) {
	vector<i32>				result;
	std::unordered_set<i32> union_set;

	for (const auto n : A) {
		auto it = union_set.find(n);
		if (it == union_set.end()) {
			union_set.insert(n);
			;
			result.push_back(n);
		}
	}
	for (const auto n : B) {
		auto it = union_set.find(n);
		if (it == union_set.end()) {
			union_set.insert(n);
			;
			result.push_back(n);
		}
	}

	return result;
}

vector<i32> set_intersection(const vector<i32> &A, const vector<i32> &B) {
	vector<i32>				result;
	std::unordered_set<i32> set_a, set_b;

	for (const auto n : A)
		set_a.insert(n);
	for (const auto n : B)
		set_b.insert(n);
	for (const auto n : set_a) {
		auto it = set_b.find(n);
		if (it != set_b.end())
			result.push_back(n);
	}
	return result;
}
