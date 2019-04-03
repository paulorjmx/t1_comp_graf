#ifndef SHADER_PROGRAM_HPP
    #define SHADER_PROGRAM_HPP
        #include "shader.hpp"

        class ShaderProgram
        {
            private:
                unsigned int shader_program_id;

            public:
                ShaderProgram();
                void create_shader_program();
                int attach_shader(Shader shader);
                void link_program();
                void user_program();
                unsigned int get_shader_program_id();
                ~ShaderProgram();

        };
#endif
