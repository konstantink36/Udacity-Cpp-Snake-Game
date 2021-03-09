#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <future>
#include <mutex>

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;

  //void HandleInput(bool &running, Snake &snake, std::promise<Snake::Direction> &&prms) const;  
  void HandleInputp(bool &running, Snake &snake, std::promise<Snake::Direction> &&prms) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

mutable std::mutex mtx1;	


};

#endif
