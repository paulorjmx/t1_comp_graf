#ifndef OPENGL_EXCEPTION_HPP
    #define OPENGL_EXCEPTION_HPP
        #include <iostream>

        class OpenglException
        {
            private:
                const char *_msg_;
                unsigned int _error_code_;

            public:
                // OpenglException(const char *msg, unsigned int error_code) : _msg_(msg), _error_code_(error_code) { }
                //
                // const char *get_message() const { return _msg_; }
                // unsigned int get_error_code() const { return _error_code_; }
                // ~OpenglException() { }
                OpenglException(const char *msg, unsigned int error_code);
                const char *get_message() const;
                unsigned int get_error_code() const;
                ~OpenglException();
        };
#endif
