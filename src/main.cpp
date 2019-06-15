#include "../inc/shader.hpp"
#include "../inc/shader_program.hpp"
#include "../inc/shader_source.hpp"
#include "../inc/vertex_buffer.hpp"
#include "../inc/vertex_array.hpp"
#include "../inc/opengl_exception.hpp"
#include "../inc/graphic_math.hpp"
#include "../inc/vertex3d.hpp"
#include "../inc/vec3d.hpp"
#include "../inc/camera.hpp"
#include <vector>
#include <cmath>
#include <cstring>
#include <GLFW/glfw3.h>

void framebuffer_resize_callback(GLFWwindow *window, int width, int height); // Função callback utilizada para atulizar o ViewPort
void key_pressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void process_input(GLFWwindow *window); // Função utilizada para processar as entradas do teclado
void load_obj(const char *file_name, vector<Vertex3D> &vertexes, vector<Vertex3D> &uv, vector<Vertex3D> &normals); // Funcao utilizada para ler o arquivo que contem um model 3d de um .obj

GraphicMath matrix; // Matriz utilizada para as transformações

int main(int argc, char const *argv[])
{
    Vec3D viewUp(Point(0.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f)); // Cria um vetor para armazenar o vetor "view up"
    GraphicMath projection; // Variavel utilizada para guardar a transformacao de projecao perspectiva
    ShaderSource vertex_source; // ShaderSource é a classe criada com o intuito de conter código de shaders.
    ShaderSource fragment_source;

    Camera c(Point(5.0f, 5.0f, 5.0f), Point(0.0f, 0.0f, 0.0f), viewUp); // Cria um objeto do tipo camera, especificando o ponto de referencia e o lookat

    float *view = c.get_view_matrix(); // Retorna a transformacao da camera em um vetor de floats

    projection.perspective_matrix(45.0f, 0.1f, 100.0f); // Cria uma matriz de projecao perspectiva

    float vertices[] = { -1.0f,-1.0f,-1.0f, // triangle 1 : begin
                            -1.0f,-1.0f, 1.0f,
                            -1.0f, 1.0f, 1.0f, // triangle 1 : end
                            1.0f, 1.0f,-1.0f, // triangle 2 : begin
                            -1.0f,-1.0f,-1.0f,
                            -1.0f, 1.0f,-1.0f, // triangle 2 : end
                            1.0f,-1.0f, 1.0f,
                            -1.0f,-1.0f,-1.0f,
                            1.0f,-1.0f,-1.0f,
                            1.0f, 1.0f,-1.0f,
                            1.0f,-1.0f,-1.0f,
                            -1.0f,-1.0f,-1.0f,
                            -1.0f,-1.0f,-1.0f,
                            -1.0f, 1.0f, 1.0f,
                            -1.0f, 1.0f,-1.0f,
                            1.0f,-1.0f, 1.0f,
                            -1.0f,-1.0f, 1.0f,
                            -1.0f,-1.0f,-1.0f,
                            -1.0f, 1.0f, 1.0f,
                            -1.0f,-1.0f, 1.0f,
                            1.0f,-1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f,
                            1.0f,-1.0f,-1.0f,
                            1.0f, 1.0f,-1.0f,
                            1.0f,-1.0f,-1.0f,
                            1.0f, 1.0f, 1.0f,
                            1.0f,-1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f,-1.0f,
                            -1.0f, 1.0f,-1.0f,
                            1.0f, 1.0f, 1.0f,
                            -1.0f, 1.0f,-1.0f,
                            -1.0f, 1.0f, 1.0f,
                            1.0f, 1.0f, 1.0f,
                            -1.0f, 1.0f, 1.0f,
                            1.0f,-1.0f, 1.0f };

    try
    {
        vertex_source.set_shader_source_from_file("src/v_shader.shd"); // Pega o código do vertex shader
        fragment_source.set_shader_source_from_file("src/f_shader.shd"); // Pega o código do fragment shader


        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        GLFWwindow *window = glfwCreateWindow(800, 600, "Trabalho 1 - Computação Gráfica", NULL, NULL);
        if(window == NULL)
        {
            cout << "Failed to create window!" << endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            cout << "Failed to link functions" << endl;
            glfwTerminate();
            return -1;
        }

        Shader vertex_shader(GL_VERTEX_SHADER);
        Shader fragment_shader(GL_FRAGMENT_SHADER);
        ShaderProgram shader_program;

        vertex_shader.create_shader();
        fragment_shader.create_shader();
        vertex_shader.set_shader_source(vertex_source.get_shader_source(), 1);
        fragment_shader.set_shader_source(fragment_source.get_shader_source(), 1);
        vertex_shader.compile_shader();
        fragment_shader.compile_shader();

        shader_program.create_shader_program();
        shader_program.attach_shader(vertex_shader);
        shader_program.attach_shader(fragment_shader);
        shader_program.link_program();


        VertexBuffer vb(1); // Cria 1 VertexBuffer
        VertexArray va(1); // Cria 1 VertexArray

        va.gen_buffer();
        vb.gen_buffer();

        va.bind_vertex_array(0);

        vb.bind_buffer(GL_ARRAY_BUFFER, 0);
        vb.buffer_data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
        glfwSetKeyCallback(window, key_pressed_callback); // Verifica se a tecla foi pressionada (utilizada para a barra de espaço)
        while(!glfwWindowShouldClose(window))
        {
            process_input(window); // Processa a tecla pressionada, ou segurada, pelo usuário.
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader_program.use_program();

            unsigned int model_location = glGetUniformLocation(shader_program.get_shader_program_id(), "model");
            unsigned int view_location = glGetUniformLocation(shader_program.get_shader_program_id(), "view");
            unsigned int projection_location = glGetUniformLocation(shader_program.get_shader_program_id(), "proj");
            glUniformMatrix4fv(model_location, 1, GL_FALSE, matrix.get_transf_matrix());
            glUniformMatrix4fv(view_location, 1, GL_FALSE, view);
            glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.get_transf_matrix());
            va.bind_vertex_array(0);
            glDrawArrays(GL_TRIANGLES, 0, 12*3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
    catch(OpenglException &e)
    {
        cout << "Error " << e.get_error_code() << ": " << e.get_message() << endl;
        return -1;
    }
    return 0;
}

void process_input(GLFWwindow *window)
{

}

void key_pressed_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

}

void framebuffer_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void load_obj(const char *file_name, vector<Vertex3D> &vertexes, vector<Vertex3D> &uv, vector<Vertex3D> &normals)
{
    float x = 0.0, y = 0.0, z = 0.0;
    unsigned int vertex_index[4], normal_index[4], uv_index[4];
    vector<unsigned int> vertices_indexes, normals_indexes, uv_indexes;
    vector<Vertex3D> temp_vertices;
    vector<Vertex3D> temp_normals;
    vector<Vertex3D> temp_uv;
    char line_readed[500], *token = NULL;
    fstream model_file(file_name, ios_base::in);
    if(model_file.is_open())
    {
        while(1)
        {
            model_file.getline(line_readed, sizeof(line_readed));
            cout << line_readed << endl;
            if(model_file.eof())
            {
                break;
            }
            else
            {
                if(strncmp(line_readed, "v ", 2) == 0) // If the line begins with v (vertices)
                {
                    token = &line_readed[2];
                    sscanf(token, "%f %f %f", &x, &y, &z);
                    temp_vertices.push_back(Vertex3D(x, y, z));
                }
                else if(strncmp(line_readed, "vn", 2) == 0) // If the line begins with vn (normals)
                {
                    token = &line_readed[2];
                    sscanf(token, " %f %f %f", &x, &y, &z);
                    temp_normals.push_back(Vertex3D(x, y, z));
                }
                else if(strncmp(line_readed, "vt", 2) == 0) // If the line begins with vt (texture coordinate)
                {
                    token = &line_readed[2];
                    sscanf(token, " %f %f", &x, &y);
                    temp_uv.push_back(Vertex3D(x, y, 1.0));
                }
                else if(line_readed[0] == 'f')
                {
                    token = &line_readed[1];
                    sscanf(token, "%u/%u/%u %u/%u/%u %u/%u/%u", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
                    vertices_indexes.emplace_back(vertex_index[0]);
                    vertices_indexes.emplace_back(vertex_index[1]);
                    vertices_indexes.emplace_back(vertex_index[2]);
                    uv_indexes.emplace_back(uv_index[0]);
                    uv_indexes.emplace_back(uv_index[1]);
                    uv_indexes.emplace_back(uv_index[2]);
                    normals_indexes.emplace_back(normal_index[0]);
                    normals_indexes.emplace_back(normal_index[1]);
                    normals_indexes.emplace_back(normal_index[2]);
                }
            }
        }

        for(int i = 0; i < vertices_indexes.size(); i++)
        {
            Vertex3D v = temp_vertices[(vertices_indexes[i] - 1)];
            vertexes.emplace_back(v);
        }

        for(int i = 0; i < normals_indexes.size(); i++)
        {
            Vertex3D n = temp_normals[(normals_indexes[i] - 1)];
            normals.emplace_back(n);
        }

        for(int i = 0; i < uv_indexes.size(); i++)
        {
            Vertex3D _uv = temp_uv[uv_indexes[i] - 1];
            uv.emplace_back(_uv);
        }
    }
    else
    {
        cout << "Error: The model cannot be open" << endl;
    }
    model_file.close();
}
