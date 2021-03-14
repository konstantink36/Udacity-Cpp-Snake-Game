#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "poison2.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Poison poison(kGridWidth, kGridHeight);
  Game game(kGridWidth, kGridHeight, poison);
  
  game.Run(controller, std::move(renderer), poison, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  
  if(game.gameover == true) {std::cout << "Game over.You ate the poison! \n";}

  return 0;
}
