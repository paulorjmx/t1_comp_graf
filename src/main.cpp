#include "../inc/shader.hpp"
#include "../inc/shader_program.hpp"
#include "../inc/shader_source.hpp"
#include "../inc/vertex_buffer.hpp"
#include "../inc/vertex_array.hpp"
#include "../inc/opengl_exception.hpp"
#include "../inc/graphic_math.hpp"
#include <GLFW/glfw3.h>

void framebuffer_resize_callback(GLFWwindow *window, int width, int height); // Função callback utilizada para atulizar o ViewPort
void process_input(GLFWwindow *window, GraphicMath *mat); // Função utilizada para processar as entradas do teclado

// Constantes utilizadas
const float POSITION_RATE = 0.0025f; // Taxa na qual o objeto realiza a translação
float VELOCITY = 0.00001f; // Velocidade na qual o objeto se move
float ACCELERATION = 0.0015f; // Taxa de variação da velocidade
char ROTATE_FLAG = 0x00; // Flag utilizada para saber se o objeto está rodando.

int main(int argc, char const *argv[])
{

    ShaderSource vertex_source; // ShaderSource é a classe criada com o intuito de conter código de shaders.
    ShaderSource fragment_source;
    GraphicMath matrix; // Matriz utilizada para as transformações

    float vertices[36] = {0.0f, 0.0f, 0.0f,
                 		0.25f, 0.0f, 0.0f,
                 		0.25f, 0.25f, 0.0f,

                 		0.0f, 0.0f, 0.0f,
                 		0.0f, 0.25f, 0.0f,
                 		-0.25f, 0.25f, 0.0f,

                 		0.0f, 0.0f, 0.0f,
                 		-0.25f, 0.0f, 0.0f,
                 		-0.25f, -0.25f, 0.0f,

                 		0.0f, 0.0f, 0.0f,
                 		0.0f, -0.25f, 0.0f,
                 		0.25f, -0.25f, 0.0f,
    };
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
        while(!glfwWindowShouldClose(window))
        {
            process_input(window, &matrix); // Processa a tecla pressionada pelo usuário.
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader_program.use_program();
            if(ROTATE_FLAG == 0x01) // Checa se o botao para rodar foi ativado
            {
                matrix.rotate_matrix(0.0f, 0.0f, 0.0f, VELOCITY);
            }
            else
            {
                matrix.stop_rotate();
            }

            unsigned int transform_location = glGetUniformLocation(shader_program.get_shader_program_id(), "transform");
            glUniformMatrix4fv(transform_location, 1, GL_FALSE, matrix.get_transf_matrix());
            va.bind_vertex_array(0);
            glDrawArrays(GL_TRIANGLES, 0, 12);

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

void process_input(GLFWwindow *window, GraphicMath *mat)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mat->translate_matrix(0.0f, POSITION_RATE, 0.0f);
    }
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        mat->translate_matrix(-POSITION_RATE, 0.0f, 0.0f);
    }
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        mat->translate_matrix(0.0f, -POSITION_RATE, 0.0f);
    }
    else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        mat->translate_matrix(POSITION_RATE, 0.0f, 0.0f);
    }
    else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if(ROTATE_FLAG == 0x00)
        {
            ROTATE_FLAG = 0x01;
        }
        else
        {
            ROTATE_FLAG = 0x00;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        if(ROTATE_FLAG == 0x01) // So modifica a velocidade se o objeto esta girando
        {
            VELOCITY -= 0.0015f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        if(ROTATE_FLAG == 0x01) // So modifica a velocidade se o objeto esta girando
        {
            VELOCITY += 0.0015f;
        }
    }
    else if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        if(ROTATE_FLAG == 0x01)
        {
            ROTATE_FLAG = 0x00;
        }
    }
}

void framebuffer_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
