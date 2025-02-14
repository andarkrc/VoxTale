gcc -Wall -Wextra -lglfw3 -lopengl32 -lgdi32 -lm -I ".\include" -L ".\lib" ^
main.c glad.c utils.c data_structures.c stb_image.c ^
.\engine\math\matrix.c ^
.\engine\shaders\shaders.c ^
.\engine\models\models.c ^
.\engine\textures\textures.c ^
-o t.exe
