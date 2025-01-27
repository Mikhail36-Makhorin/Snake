#ifndef OUTOFRANGEEXCEPTION_H
#define OUTOFRANGEEXCEPTION_H

#include "BaseException.h"

/**
 * OutOfRangeException — исключение выхода за допустимые границы
 *        (например, для координат или индексов).
 *        В текущей версии «Змейки» не используется, потому что у нас
 *        «тороидальное» поле, но может пригодиться в будущем.
 */
class OutOfRangeException : public BaseException {
public:
    explicit OutOfRangeException(const std::string& msg)
        : BaseException(msg) {}
};

#endif 