#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <stdexcept>
#include <string>

/**
 * BaseException — базовое исключение для проекта.
 *        Наследует от std::runtime_error.
 */
class BaseException : public std::runtime_error {
public:
    explicit BaseException(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif 