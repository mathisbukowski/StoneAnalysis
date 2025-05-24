##
## EPITECH PROJECT, 2025
## StoneAnalysis
## File description:
## Makefile
##

SRC = src/main.cpp 				\
	src/Audio/AudioParser.cpp 	\
	src/Math.cpp 				\
	src/Analyzer/Analyzer.cpp 	\
	src/Factory/ToolFactory.cpp \
	src/Cypher/Cypher.cpp		\
	src/Decypher/Decypher.cpp

OBJ = $(SRC:.cpp=.o)

NAME = stone_analysis

CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -I include

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)
	@echo "Build complete"

clean:
	rm -f $(OBJ)
	@echo "Object files removed"

fclean: clean
	rm -f $(NAME)
	@echo "Executable removed"

re: fclean all

.PHONY: all clean fclean re
