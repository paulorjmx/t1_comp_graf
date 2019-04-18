all:
	@g++ main.cpp glad.c shader_source.cpp shader_program.cpp shader.cpp vertex_array.cpp vertex_buffer.cpp opengl_exception.cpp graphic_math.cpp -I. -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o main
