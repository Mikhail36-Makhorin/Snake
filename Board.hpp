// Зачем нужен: класс Board описывает игровое поле (ширину/высоту). Код ниже с подробными комментариями.

#pragma once 

/**
 * Класс Board хранит размеры игрового поля (в клетках).
 */
class Board {
private:
    int width;   // Ширина поля (в клетках)
    int height;  // Высота поля (в клетках)

public:
    Board(int w, int h);
    int getWidth() const;
    int getHeight() const;
};