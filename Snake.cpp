#include "../include/Snake.hpp"

// Конструктор
Snake::Snake(int startX, int startY)
    : dx(1), // По умолчанию движемся вправо
      dy(0)
{
    // Начинаем с одного сегмента (голова) в (startX, startY)
    body.push_back({startX, startY});
}

void Snake::setDirection(int newDx, int newDy) {
    // Устанавливаем новое направление
    dx = newDx;
    dy = newDy;
}

void Snake::move() {
    // Берём координаты головы
    auto head = body.front();
    int newHeadX = head.first + dx;
    int newHeadY = head.second + dy;

    // Добавляем новую голову в начало
    body.push_front({newHeadX, newHeadY});
    // Убираем последний сегмент (хвост)
    body.pop_back();
}

void Snake::grow() {
    // Удлиняемся: дублируем последний сегмент
    if (!body.empty()) {
        body.push_back(body.back());
    }
}

bool Snake::checkSelfCollision() const {
    // Если в змее меньше 2 сегментов, столкновения быть не может
    if (body.size() < 2) return false;

    // Голова
    auto head = body.front();
    // Смотрим, встречается ли голова в остальных сегментах
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i] == head) {
            return true;
        }
    }
    return false;
}

const std::deque<std::pair<int,int>>& Snake::getBody() const {
    // Возвращаем константную ссылку на тело
    return body;
}

std::deque<std::pair<int,int>>& Snake::getMutableBody() {
    // Возвращаем неконстантную ссылку, чтобы можно было модифицировать (для "обёртывания")
    return body;
}