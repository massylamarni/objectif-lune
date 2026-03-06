LD_FLAGS = -lGL -lGLU -lglut -lm

all: Explosion LEM

Explosion: Explosion.cpp customPreset.o
	gcc -Wall -Wextra Explosion.cpp -o Explosion customPreset.o $(LD_FLAGS)

LEM: LEM.c customPreset.o
	gcc -Wall -Wextra LEM.c -o LEM customPreset.o $(LD_FLAGS)

customPreset.o: customPreset.c
	gcc -Wall -Wextra -c customPreset.c -o customPreset.o $(LD_FLAGS)

