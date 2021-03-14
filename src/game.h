#ifndef GAME_H
#define GAME_H

#include <random>
#include <future>
#include <thread>
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "poison2.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Poison &poison);
  void Run(Controller &controller, Renderer renderer, Poison &poison,
           std::size_t target_frame_duration);

  int GetScore() const;
  int GetSize() const;
  bool gameover = false;

 private:
  Snake snake;
  SDL_Point food;

//random device for food
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  mutable std::mutex mtx_food;	

  void PlaceFood();
  void Update(Poison &poison);
  bool FoodCell(int x, int y);

};

#endif
