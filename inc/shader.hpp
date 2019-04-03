#ifndef SHADER_HPP
    #define SHADER_HPP
        #include <inc/glad/glad.h>

        class Shader
        {
            private:
                GLenum shader_type;
                unsigned int shader_id;
                bool created, sourced, compiled;

            public:
                Shader();
                Shader(GLenum shader_type);
                bool is_created();
                bool is_compiled();
                void compile_shader();
                int create_shader();
                int set_shader_source(const char **source, unsigned int count);
                void set_shader_type(GLenum shader_type);
                unsigned int get_shader_id();
                GLenum get_shader_type();
                ~Shader();

        };
#endif
