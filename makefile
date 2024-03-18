main: main.c
	sudo apt install libncurses5-dev
	gcc main.c -o main -lncurses
