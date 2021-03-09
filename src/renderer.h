#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <iostream>

#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();


//copy constructor
  Renderer(const Renderer& other);

//copy assignment
  Renderer &operator=(const Renderer &other);

//move constructor
  Renderer(Renderer &&other);

//move assignment
  Renderer& operator=(Renderer&& other);

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  //SDL_Window 
  std::shared_ptr<SDL_Window> sdl_window = nullptr;

  //SDL_Renderer 
  std::shared_ptr<SDL_Renderer> sdl_renderer = nullptr;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  
  mutable std::mutex mtx1;	

};

#endif
