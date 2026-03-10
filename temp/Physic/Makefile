LD_FLAGS = -lGL -lGLU -lglut -lm

all: moon_test

moon_test: moon_test.c moon_gravity.o customPreset.o
	gcc -Wall -Wextra moon_test.c -o moon_test moon_gravity.o customPreset.o $(LD_FLAGS)

moon_gravity.o: moon_gravity.c
	gcc -Wall -Wextra -c moon_gravity.c -o moon_gravity.o $(LD_FLAGS)
	
customPreset.o: customPreset.c
	gcc -Wall -Wextra -c customPreset.c -o customPreset.o $(LD_FLAGS)

