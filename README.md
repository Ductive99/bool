# bool
A from-scratch implementation of Boolean algebra and set theory fundamentals, covering bitwise arithmetic, propositional logic evaluation, normal form transformations, and space-filling curves.

### Exercises

## Chapter 1 - Warmup

#### 00 - Adder

Write a function that takes two natural numbers `a` and `b` and returns the sum `a + b`. Using only the following operations:
- & (bitwise AND) 
- | (bitwise OR) 
- ^ (bitwise XOR) 
- << (left shift) 
- \>\> (right shift) 
- = (assignment)
- ==, !=, >, <=, >= (comparison operators)

> there are multiple ways to do this, I chose to simulate a full adder logic. Which most resambles the ALU's actual computation (but not always).

#### 01 - Multiplier

Write a function that takes two natural numbers `a` and `b` and returns the product `a * b`. Using the same operations as the previous exercise.

> having implemented the adder, it is easier to implement the multiplier using a shift-and-add logic like how most students do.

#### 02 - Gray code

Write a function that takes an integer `n` and returns its equivalent in Gray code.

## Chapter 2 - Boolean Algebra
Chapter 2 has all to do with boolean algebra, and is composed of multiple exercises around the topic. Exercises quickly increase in complexity and if the code isn't well designed, exercise can easily become impossible.<br>
An AST tree is probably necessary to solve all the problems. Which is the most complicated part of the project.
```c++
enum class NodeType : char {
	Const,	  // leaf: boolean constant (0 or 1)
	Variable, // leaf: A-Z
	Not,	  // unary:  !
	And,	  // binary: &
	Or,		  // binary: |
	Xor,	  // binary: ^
	Implies,  // binary: >
	Iff		  // binary: = (equivalence)
};
```

### 03 - Boolean evaluation

Given a propositional formula in reverse polish notation, return the result of the formula.

### 04 - Truth table

Given a propositional formula, that uses variables (A-Z), print its truth table

### 05 - Negation normal form

Given a formula, rewrite in negation normal form.

> **NNF (Negation Normal Form)**<br>formula = AND / OR of sub-formulas<br>literal = $x_i$ / NOT $x_i$

### 06 - Conjunctive normal form

Rewrite a given formula in conjunctive normal form (CNF).

> **CNF (Conjunctive Normal Form)**<br>formula = AND of clauses<br>clause = OR of literals<br>literal = $x_i$ / NOT $x_i$

### 07 - Boolean Satisfiability Problem

The first NP-complete. The goal is to check if a given formula is satisfiable, meaning it can be true.

## Chapter 3 - Set Theory

### 08 - Powerset

Return the powerset of a set. The powerset is the set that contains all possible sets from the elements of the first set. *(that's a lot of sets)*

> hint: backtracking

### 09 - Set evaluation

Using the boolean algebra rules, apply them to sets. instead of 1's and 0's we have sets.