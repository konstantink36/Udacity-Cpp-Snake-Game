#include "renderer.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
      {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  } 

  // Create Window
sdl_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN), SDL_DestroyWindow);         

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  } 

  // Create renderer
sdl_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);


  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}  

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window.get());
 
 
  SDL_Quit();
}

// copy constructor
Renderer::Renderer(const Renderer& source)
    : screen_width(source.screen_width),
      screen_height(source.screen_height),
      grid_width(source.grid_width),
      grid_height(source.grid_height)
 {
sdl_window = source.sdl_window; 
sdl_renderer = source.sdl_renderer;  
}  

//copy assignment 
Renderer& Renderer::operator=(const Renderer &source)
 {
sdl_window = source.sdl_window; 
sdl_renderer = source.sdl_renderer;  
return *this;
}  

// move constructor
Renderer::Renderer(Renderer &&source)
    : screen_width(source.screen_width),
      screen_height(source.screen_height),
      grid_width(source.grid_width),
      grid_height(source.grid_height) 
 {
sdl_window = source.sdl_window; 
sdl_renderer = source.sdl_renderer;

image = source.image;
texture = source.texture;
}  

//move assignment
Renderer& Renderer::operator=(Renderer&& source)
 {
sdl_window = source.sdl_window; 
sdl_renderer = source.sdl_renderer; 
source.sdl_window = nullptr;
source.sdl_renderer = nullptr;
return *this;
}  

    void Renderer::Render(Snake const snake, SDL_Point const &food, std::vector<SDL_Point> const &body ) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer.get());

  // Render food
  // put lock on rendering of food, poison, snake, which is shared across thread 2 and 3
  std::unique_lock<std::mutex> lck1(mtx1);  

  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer.get(), &block);

 //Render poison
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0x00);
  for (auto const &item : body) {
  block.x = item.x * block.w;
  block.y = item.y * block.h;
  SDL_RenderFillRect(sdl_renderer.get(), &block); 
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;

  lck1.unlock();  //unlock

  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);
   

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}
