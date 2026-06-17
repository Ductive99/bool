NAME = bool

SRCDIR = src
OBJDIR = build
INCDIR = include

SRCS = main.cpp \
	   adder.cpp \
	   multiplier.cpp \
	   gray_code.cpp \
	   boolean_evaluation.cpp \
	   truth_table.cpp

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g3
INCFLAGS = -I $(INCDIR)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
