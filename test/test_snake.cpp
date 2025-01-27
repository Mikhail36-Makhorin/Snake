#include <gtest/gtest.h>
#include "../include/Snake.hpp"

// Тест: проверяем начальное состояние змейки
TEST(SnakeTest, InitialState) {
    // Создаём змею с позицией (5,5)
    Snake s(5, 5);
    // Проверяем, что длина 1
    EXPECT_EQ(s.getBody().size(), 1u);
    // И координаты равны (5,5)
    EXPECT_EQ(s.getBody().front(), std::make_pair(5, 5));
}

// Тест: проверяем движение змейки
TEST(SnakeTest, MoveSnake) {
    Snake s(5, 5);
    // По умолчанию dx=1, dy=0 (движется вправо)
    s.move();
    // Новая голова должна быть (6,5)
    EXPECT_EQ(s.getBody().front(), std::make_pair(6, 5));
    // Длина не меняется (1)
    EXPECT_EQ(s.getBody().size(), 1u);
}

// Тест: проверяем функцию grow()
TEST(SnakeTest, GrowSnake) {
    Snake s(5, 5);
    // Увеличиваем змею
    s.grow();
    // Теперь длина 2
    EXPECT_EQ(s.getBody().size(), 2u);
    // Хвост совпадает с предыдущей позицией
    EXPECT_EQ(s.getBody().back(), std::make_pair(5, 5));
}

// Тест: проверяем самопересечение
TEST(SnakeTest, SelfCollision) {
    Snake s(5, 5);
    // Движемся вправо (по умолчанию)
    s.move(); // теперь голова (6,5)
    s.grow(); // длина 2
    s.move(); // голова (7,5), хвост (6,5), ещё один сегмент (6,5) в конце
    // Сделаем специальное движение, чтобы вернуться на (6,5)
    s.setDirection(-1, 0); // влево
    s.move(); // голова (6,5)
    // Теперь голова совпадает с одним из сегментов
    EXPECT_TRUE(s.checkSelfCollision());
}