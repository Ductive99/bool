NAME = bool

SRCDIR = src
OBJDIR = build
INCDIR = include
TESTDIR = tests

SRCS = main.cpp \
	   adder.cpp \
	   multiplier.cpp \
	   gray_code.cpp \
	   boolean_evaluation.cpp \
	   truth_table.cpp \
	   negation_normal_form.cpp \
	   utils_to_rpn.cpp

TEST_SRCS = $(TESTDIR)/test_adder.cpp \
	   $(TESTDIR)/test_multiplier.cpp \
	   $(TESTDIR)/test_gray_code.cpp \
	   $(TESTDIR)/test_eval_formula.cpp \
	   $(TESTDIR)/test_print_truth_table.cpp \
	   $(TESTDIR)/test_negation_normal_form.cpp \

OBJS = $(SRCS:%.cpp=$(OBJDIR)/src/%.o)
TEST_OBJS = $(TEST_SRCS:$(TESTDIR)/%.cpp=$(OBJDIR)/tests/%.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g3
INCFLAGS = -I $(INCDIR)

.PHONY: all clean fclean re test

all: $(NAME)

test: $(NAME)

$(NAME): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(OBJS) $(TEST_OBJS) -o $(NAME)

$(OBJDIR)/src/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(OBJDIR)/tests/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
