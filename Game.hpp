// Зачем нужен: класс Game управляет всем игровым процессом — хранит поле, змею, еду, обрабатывает ввод, отрисовывает, и т.д.

#pragma once

#include "Board.hpp"      
#include "Snake.hpp"      
#include "../exceptions/OutOfRangeException.hpp" 

// Подключаем SDL2
#include <SDL2/SDL.h>
#include <utility>   
#include <cstdlib>   
#include <ctime>     


class Game {
private:
    Board board;                   // объект "игровое поле"
    Snake snake;                   // объект "змейка"
    std::pair<int,int> food;      // координаты еды (x,y)
    bool gameOver;                 // флаг окончания игры

    // SDL
    SDL_Window* window;           // окно SDL
    SDL_Renderer* renderer;       // рендерер SDL
    const int cellSize;           // размер одной клетки (в пикселях)

public:
    /**
     * Конструктор
     * width  ширина поля (в клетках)
     * height высота поля (в клетках)
     * startX начальная позиция змейки (x)
     * startY начальная позиция змейки (y)
     */
    Game(int width, int height, int startX, int startY);

    /**
     * Деструктор, освобождает ресурсы SDL.
     */
    ~Game();

    /**
     * Запускает главный цикл игры.
     */
    void run();

private:
    /**
     * Инициализация SDL, создание окна и рендерера.
     */
    void initSDL();

    /**
     * Закрытие SDL, освобождение ресурсов.
     */
    void closeSDL();

    /**
     * Генерация "еды" в случайной точке на поле.
     */
    void generateFood();

    /**
     * Обработка ввода (клавиатура, события SDL).
     */
    void processInput();

    /**
     * Обновление логики (движение змейки, проверка на столкновение и т.д.).
     */
    void update();

    /**
     * Отрисовка (очистка окна, рисование змейки, еды, вывод кадра).
     */
    void render();
};