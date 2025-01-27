#include "../include/Game.hpp"
#include <iostream> 


Game::Game(int width, int height, int startX, int startY)
    : board(width, height),   // Инициализируем объект Board
      snake(startX, startY),  // Инициализируем змею
      gameOver(false),        // Игра ещё не окончена
      window(nullptr),        // Пока нет окна
      renderer(nullptr),      // Пока нет рендерера
      cellSize(20)            // Размер клетки в пикселях
{
    // Инициализируем (генератор случайных чисел)
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Создаём первое "яблоко" (еду)
    generateFood();

    // Инициализируем SDL (создаём окно, рендерер)
    initSDL();
}

Game::~Game() {
    // Закрываем SDL, освобождаем ресурсы
    closeSDL();
}

// Инициализация и завершение SDL
void Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: "
                  << SDL_GetError() << std::endl;
        exit(1);
    }

    // Создаём окно
    window = SDL_CreateWindow(
        "SnakeGame",                        // Заголовок окна
        SDL_WINDOWPOS_CENTERED,             // X-позиция
        SDL_WINDOWPOS_CENTERED,             // Y-позиция
        board.getWidth() * cellSize,        // Ширина окна в пикселях
        board.getHeight() * cellSize,       // Высота окна в пикселях
        SDL_WINDOW_SHOWN                    // Флаги (показать окно)
    );
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        exit(1);
    }

    // Создаём рендерер 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Game::closeSDL() {
    // Уничтожаем рендерер, если он есть
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    // Уничтожаем окно, если оно есть
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    // Выключаем SDL
    SDL_Quit();
}

// Главный цикл игры
void Game::run() {
    while (!gameOver) {
        processInput(); // Обработка нажатий
        update();       // Обновляем логику (движение змейки, проверка столкновений)
        render();       // Отрисовка

        // Задержка ~100 мс = 10 кадров в секунду
        SDL_Delay(100);
    }
    std::cout << "Game Over!" << std::endl;
}

// Вспомогательные методы
void Game::generateFood() {
    // Случайные координаты внутри поля
    int x = std::rand() % board.getWidth();
    int y = std::rand() % board.getHeight();
    food = {x, y};
}

void Game::processInput() {
    SDL_Event e;
    // Считываем все события (клавиатура, закрытие окна и т.д.)
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            // Если нажали на крестик в окне
            gameOver = true;
        } else if (e.type == SDL_KEYDOWN) {
            // Обрабатываем клавиши
            switch (e.key.keysym.sym) {
                case SDLK_w: snake.setDirection(0, -1); break;
                case SDLK_s: snake.setDirection(0,  1); break;
                case SDLK_a: snake.setDirection(-1, 0); break;
                case SDLK_d: snake.setDirection(1,  0); break;
                case SDLK_ESCAPE:
                    gameOver = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::update() {
    // Двигаем змею
    snake.move();

    // Координаты головы после move()
    auto head = snake.getBody().front();

    // Тороидальное обёртывание 
    // Если вышли за левый край - появляемся справа
    if (head.first < 0) {
        head.first = board.getWidth() - 1;
    } else if (head.first >= board.getWidth()) {
        head.first = 0;
    }
    // Если вышли за верх - появляемся снизу
    if (head.second < 0) {
        head.second = board.getHeight() - 1;
    } else if (head.second >= board.getHeight()) {
        head.second = 0;
    }

    // Так как move() уже добавил новую голову,
    // заменяем её на "обёрнутую" версию.
    snake.getMutableBody().pop_front();
    snake.getMutableBody().push_front(head);

    // Проверяем самопересечение
    if (snake.checkSelfCollision()) {
        gameOver = true;
        return; // сразу выходим
    }

    // Проверяем, не съели ли еду
    if (head == food) {
        // Растём
        snake.grow();
        // Генерируем новую еду
        generateFood();
    }
}

void Game::render() {
    // Очищаем экран (чёрный фон)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Рисуем еду (красным)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect foodRect;
    foodRect.x = food.first  * cellSize;
    foodRect.y = food.second * cellSize;
    foodRect.w = cellSize;
    foodRect.h = cellSize;
    SDL_RenderFillRect(renderer, &foodRect);

    // Рисуем змею (зелёным)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (auto segment : snake.getBody()) {
        SDL_Rect r;
        r.x = segment.first  * cellSize;
        r.y = segment.second * cellSize;
        r.w = cellSize;
        r.h = cellSize;
        SDL_RenderFillRect(renderer, &r);
    }

    // Показываем кадр
    SDL_RenderPresent(renderer);
}