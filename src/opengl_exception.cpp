#include "../inc/opengl_exception.hpp"

OpenglException::OpenglException(const char *msg, unsigned int error_code)
{
    this->_msg_ = msg;
    this->_error_code_ = error_code;
}

const char *OpenglException::get_message() const
{
    return this->_msg_;
}

unsigned int OpenglException::get_error_code() const
{
    return this->_error_code_;
}

OpenglException::~OpenglException()
{

}
