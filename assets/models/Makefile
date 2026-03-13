LD_FLAGS = -lGL -lGLU -lglut -lm

all: explosion lem

explosion: explosion.c custom_preset.o
	gcc -Wall -Wextra explosion.c -o explosion custom_preset.o $(LD_FLAGS)

lem: lem.c custom_preset.o
	gcc -Wall -Wextra lem.c -o lem custom_preset.o $(LD_FLAGS)

custom_preset.o: custom_preset.c
	gcc -Wall -Wextra -c custom_preset.c -o custom_preset.o $(LD_FLAGS)

