#include "inc/shader.hpp"
#include "inc/shader_program.hpp"
#include "inc/vertex_buffer.hpp"
#include "inc/vertex_array.hpp"
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>

using namespace std;

void framebuffer_resize_callback(GLFWwindow *window, int width, int height);
char *get_content_from_file(const char *filename);

int main(int argc, char const *argv[])
{

    const char *vertexshader_source = get_content_from_file("v_shader.shd");
    const char *fragmentshader_source = get_content_from_file("f_shader.shd");

    float vertices[] = {0.0f, 0.5f, 0.0f,
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f
                        };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Triangle", NULL, NULL);
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
    vertex_shader.set_shader_source(&vertexshader_source, 1);
    fragment_shader.set_shader_source(&fragmentshader_source, 1);
    vertex_shader.compile_shader();
    fragment_shader.compile_shader();

    shader_program.create_shader_program();
    shader_program.attach_shader(vertex_shader);
    shader_program.attach_shader(fragment_shader);
    shader_program.link_program();


    VertexBuffer vb(1);
    VertexArray va(1);
    // unsigned int VBO, VAO;
    va.gen_buffer();
    vb.gen_buffer();

    va.bind_vertex_array(0);

    vb.bind_buffer(GL_ARRAY_BUFFER, 0);
    vb.buffer_data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw our first triangle
        shader_program.user_program();
        va.bind_vertex_array(0); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);

    glfwTerminate();
    delete[] vertexshader_source;
    delete[] fragmentshader_source;
    return 0;
}

void framebuffer_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

char *get_content_from_file(const char *filename)
{
    char *buffer = NULL;
    if(filename != NULL)
    {
        fstream input_file(filename, ios::in);
        if(input_file.is_open() != true)
        {
            cout << "Failed to open the file!" << endl;
        }
        else
        {
            input_file.seekg(0, input_file.end);
            unsigned int lenght = input_file.tellg();
            buffer = new char[lenght];
            input_file.seekg(0, input_file.beg);
            if(!input_file.read(buffer, lenght))
            {
                cout << "An error ocurred on read file!" << endl;
            }
        }
        input_file.close();
    }
    else
    {
        cout << "Error: empty filename!" << endl;
    }
    return buffer;
}
