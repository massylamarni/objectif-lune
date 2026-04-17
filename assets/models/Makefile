LD_FLAGS = -lGL -lGLU -lglut -lm -L../../libs/libpng12/lib -Wl,-rpath,../../libs/libpng12/lib -lpng

all: explosion_model_editor lem_model_editor moon_model_editor

explosion_model_editor: explosion_model_editor.c explosion.o custom_preset.o 
	g++ -Wall -Wextra explosion_model_editor.c -o explosion_model_editor explosion.o custom_preset.o $(LD_FLAGS)
	
explosion.o: explosion.cpp
	g++ -Wall -Wextra -c explosion.cpp -o explosion.o   $(LD_FLAGS)

lem_model_editor: lem_model_editor.c lem.o custom_preset.o
	g++ -Wall -Wextra lem_model_editor.c -o lem_model_editor lem.o custom_preset.o color_palette.o polyface_object.o ../../build/libs/PNG/ChargePngFile.o ../../build/libs/PNG/Espace3UC.o ../../build/libs/PNG/Image.o ../../build/libs/PNG/ImageUtils.o ../../build/libs/PNG/PngFile.o  $(LD_FLAGS)

lem.o: lem.c color_palette.o polyface_object.o
	g++ -Wall -Wextra -c lem.c -o lem.o   $(LD_FLAGS)

moon_model_editor: moon_model_editor.c moon.o custom_preset.o
	g++ -Wall -Wextra moon_model_editor.c -o moon_model_editor moon.o custom_preset.o color_palette.o polyface_object.o ../../build/libs/PNG/ChargePngFile.o ../../build/libs/PNG/Espace3UC.o ../../build/libs/PNG/Image.o ../../build/libs/PNG/ImageUtils.o ../../build/libs/PNG/PngFile.o  $(LD_FLAGS)

moon.o: moon.c
	g++ -Wall -Wextra -c moon.c -o moon.o   $(LD_FLAGS)

color_palette.o: color_palette.c
	g++ -Wall -Wextra -c color_palette.c -o color_palette.o $(LD_FLAGS)

polyface_object.o: polyface_object.c
	g++ -Wall -Wextra -c polyface_object.c -o polyface_object.o $(LD_FLAGS)

custom_preset.o: custom_preset.c
	g++ -Wall -Wextra -c custom_preset.c -o custom_preset.o $(LD_FLAGS)

clean:
	rm *_model_editor *.o
 
