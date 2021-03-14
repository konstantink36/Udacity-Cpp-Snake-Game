#include "poison2.h"
#include <iostream>
#include <random>


Poison::Poison(std::size_t grid_width, std::size_t grid_height)
    : engine_p(dev_p()),
      random_w_p(1, static_cast<int>(grid_width-1)),
      random_h_p(1, static_cast<int>(grid_height-1))
       {
       } 

//Place poison at random points and put in vector
void Poison::PlacePoison(Snake & snake, SDL_Point & food) {
      SDL_Point point;
      poison_vector.clear();
      for(std::size_t i=0; i<3; i++){
      bool looping = true;
      while (looping == true) {    
      point.x =  random_w_p(engine_p);
      point.y =  random_h_p(engine_p);
      if (!snake.SnakeCell(point.x, point.y)  && (!Poison::FoodCell(food.x, food.y))) {
      poison_vector.push_back(point);
      looping = false;
        }  
       } 
      } 
} 

//check if cell is occupied by poison
bool Poison::PoisonCell (int x, int y){
  bool status = false;
  for (auto const &cell : poison_vector) {
    if ( cell.x == x && cell.y == y) {
      status = true;
    }
  }
  return status;
}

//check if cell is occupied by food
bool Poison::FoodCell (int x, int y){
  bool status = false;
  for (auto const &cell : poison_vector) {
    if ( cell.x == x && cell.y == y) {
      status = true;
    }
  }
  return status;
}

//getter function for poison vector 
std::vector <SDL_Point> Poison::GetPoison(){
  return poison_vector;
}
