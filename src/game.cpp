#include "game.h"
#include "poison2.h"
#include <iostream>
#include <thread>
#include <future>
#include <string>

Game::Game(std::size_t grid_width, std::size_t grid_height, Poison &poison )
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(1, static_cast<int>(grid_width-1)),
      random_h(1, static_cast<int>(grid_height-1))
       { 
  PlaceFood();
  poison.PlacePoison(snake, food);
}

void Game::Run(Controller  &controller, Renderer renderer, Poison &poison,
               std::size_t target_frame_duration) {


  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;


  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.

    //Thread 1 runs controller.HandleInput(running, snake)
    //Note: this requires a lock in Controller::Changedirection 
    std::future<void> ftr1 = std::async(&Controller::HandleInput,&controller,std::ref(running),std::ref(snake));
    
    //Thread 2 runs Game::Update()
    std::future<void> ftr2 = std::async(&Game::Update, this, std::ref(poison));
    
    //Thread 3 runs renderer.Render(snake,food)
    // Note: this requires a lock in Renderer::Render
    std::future<void> ftr3 = std::async(&Renderer::Render, &renderer, std::ref(snake), std::ref(food), poison.GetPoison());
    
    ftr1.wait();
    ftr2.wait();
    ftr3.wait();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

//Update the game
void Game::Update(Poison &poison) {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    poison.PlacePoison(snake, food);
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.01;
  }
    //else if (poison.point.x == new_x && poison.point.y == new_y) {
    else if (poison.PoisonCell(new_x, new_y)) {
    snake.alive = false;
    gameover = true;
  }
}  

//check if cell is occupied by food
bool Game::FoodCell(int x, int y) {
  if (x == static_cast<int>(food.x) && y == static_cast<int>(food.y)) {
    return true;
  }
  return false;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
