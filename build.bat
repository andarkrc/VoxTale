gcc -Wall -Wextra -lglfw3 -lopengl32 -lgdi32 -lm -I ".\include" -L ".\lib" ^
main.c glad.c utils.c data_structures.c ^
.\engine\math\matrix.c ^
.\engine\shaders\shaders.c ^
-o t.exe
