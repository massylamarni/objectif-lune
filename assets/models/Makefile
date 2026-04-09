LD_FLAGS = -lGL -lGLU -lglut -lm

all: explosion lem_model_editor moon_model_editor

explosion: explosion.c custom_preset.o
	gcc -Wall -Wextra explosion.c -o explosion custom_preset.o $(LD_FLAGS)

lem_model_editor: lem_model_editor.c lem.o custom_preset.o
	gcc -Wall -Wextra lem_model_editor.c -o lem_model_editor lem.o custom_preset.o color_palette.o polyface_object.o $(LD_FLAGS)

lem.o: lem.c color_palette.o polyface_object.o
	gcc -Wall -Wextra -c lem.c -o lem.o   $(LD_FLAGS)

moon_model_editor: moon_model_editor.c moon.o custom_preset.o
	gcc -Wall -Wextra moon_model_editor.c -o moon_model_editor moon.o custom_preset.o color_palette.o polyface_object.o $(LD_FLAGS)

moon.o: moon.c
	gcc -Wall -Wextra -c moon.c -o moon.o   $(LD_FLAGS)

color_palette.o: color_palette.c
	gcc -Wall -Wextra -c color_palette.c -o color_palette.o $(LD_FLAGS)

polyface_object.o: polyface_object.c
	gcc -Wall -Wextra -c polyface_object.c -o polyface_object.o $(LD_FLAGS)

custom_preset.o: custom_preset.c
	gcc -Wall -Wextra -c custom_preset.c -o custom_preset.o $(LD_FLAGS)

clean:
	rm lem explosion custom_preset.o color_palette.o polyface_object.o moon.o
