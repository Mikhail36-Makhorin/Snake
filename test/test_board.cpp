#include <gtest/gtest.h>
#include "../include/Board.hpp"

// Тест, проверяющий корректность инициализации Board
TEST(BoardTest, Initialization) {
    Board b(20, 10);

    // Проверяем ширину и высоту
    EXPECT_EQ(b.getWidth(), 20);
    EXPECT_EQ(b.getHeight(), 10);
}

// Тест, проверяющий граничные значения
TEST(BoardTest, ZeroDimensions) {
    Board b(0, 0);
    EXPECT_EQ(b.getWidth(), 0);
    EXPECT_EQ(b.getHeight(), 0);
}