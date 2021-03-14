#include "snake.h"
#include <vector>
#include <random>

class Poison {
public:
Poison(std::size_t grid_width, std::size_t grid_height);
void PlacePoison(Snake & snake, SDL_Point food);

bool PoisonCell(int x, int y);
bool FoodCell(int x, int y);
std::vector <SDL_Point> GetPoison();

private:
SDL_Point point;
std::vector <SDL_Point> poison_vector;

//random device for poison
std::random_device dev_p;
std::mt19937 engine_p;
std::uniform_int_distribution<int> random_w_p;
std::uniform_int_distribution<int> random_h_p;
};

#endif
