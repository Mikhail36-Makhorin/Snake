#include <gtest/gtest.h>
#include "../include/Game.hpp"

// Тест: Проверка, что конструктор Game не выбрасывает исключений
TEST(GameTest, Creation) {
    // Создаём игру с размером поля 20x10, старт (10,5)
    EXPECT_NO_THROW(Game(20, 10, 10, 5));
}

// Тест: Проверка граничных значений поля
TEST(GameTest, SmallField) {
    // Поле 1x1, старт (0,0) — довольно экстремальный случай
    EXPECT_NO_THROW(Game(1, 1, 0, 0));
}