title := pong

all: main

main: main.c
	eval cc main.c -I/opt/homebrew/Cellar/raylib/5.0/include -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib -o ${title} -Wall -Wextra

clean:
	rm $(title)
