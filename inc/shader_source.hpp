#ifndef SHADER_SOURCE_HPP
    #define SHADER_SOURCE_HPP
        #include <fstream>
        #include <iostream>

        using namespace std;

        class ShaderSource
        {
            private:
                char *source_code;

            public:
                ShaderSource();
                ShaderSource(const char *source);
                void set_shader_source(const char *source);
                void set_shader_sourcer_from_file(const char *filename);
                char *get_shader_source();
                ~ShaderSource();
        };
#endif
