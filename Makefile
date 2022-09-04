FLAGS = -Wall -Werror -Wextra

all: state_sort state_search clear_state

state_sort:
	gcc $(FLAGS) state_sort.c bin.c -o ../build/Quest_1

state_search:
	gcc $(FLAGS) state_search.c bin.c -o ../build/Quest_2

clear_state:
	gcc $(FLAGS) clear_state.c bin.c -o ../build/Quest_3

clean:
	rm -rf ../build/*

rebuild: all clean