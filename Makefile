CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CC = gcc
files_c = cost.c graph.c dijkstra.c main.c
files_o = cost.o graph.o dijkstra.o main.o
files_star = cost.o graph.o dijkstra.o star.o

all: $(files_c)
	$(CC) $(CFLAGS) -c $(files_c)
	$(CC) $(CFLAGS) -o dijkstra set.o $(files_o)
	
clean: 
	rm -f dijkstra $(files_o)
	rm -f star $(files_star)

valgrind: all
	@read -p "Enter the name of a example.in:  " EXAMPLE; valgrind --leak-check=full ./dijkstra input/$$EXAMPLE
	
valgrind_star: all_star
	@read -p "Enter the name of a example.in:  " STAR; valgrind --leak-check=full ./star input/$$STAR

all_star: set.o $(files_o)
	$(CC) $(CFLAGS) -c star.c
	$(CC) $(CFLAGS) -o star set.o $(files_star)
