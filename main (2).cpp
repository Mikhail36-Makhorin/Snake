#include <iostream>
#include "include/Game.hpp"
#include "exceptions/OutOfRangeException.hpp"


int main() {
    try {
        // Создаём игру на поле 20x10, змея начинает в (10,5)
        Game game(20, 10, 10, 5);
        game.run();
    }
    catch (const OutOfRangeException& e) {
        // Если вдруг будет использовано в логике
        std::cerr << "OutOfRangeException: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Любые другие стандартные исключения
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }
    catch (...) {
        // Если что-то совсем непредвиденное
        std::cerr << "Unknown exception occurred!" << std::endl;
    }
    return 0;
}