#include "../include/Board.hpp"

// Конструктор
Board::Board(int w, int h)
    : width(w),   // Инициализируем поле заданной шириной
      height(h)   // И высотой
{}

// Возвращает ширину
int Board::getWidth() const {
    return width;
}

// Возвращает высоту
int Board::getHeight() const {
    return height;
}