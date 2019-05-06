all: src/database.c
	clang -Wall -Werror -o bin/database src/database.c
