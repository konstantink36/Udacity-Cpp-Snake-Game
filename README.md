## Snake Game Project



## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Project description

The base code from CppND-Capstone-Snake-Game GitHub repository is modified to add new game features to the snake game. 
Poison pallets (red) are randomly placed on the field, the snake dies if it hits one of them. The poison pallets change position whenever the snake eats food (yellow).
Another added feature is multithreading, see details below.

## 10 C++ features have been implemented in this project:

1. A variety of control structures are used in the project. The project code is organized into functions.
3. Appropriate data and functions are grouped into classes. Data is accessed via member functions.
5. All class data members are explicitly specified as public, protected, or private.
7. Class constructors utilize member initialization lists.
9. The project makes use of references in function declarations.
11. The project follows the Rule of 5
13. The project uses move semantics to move data.
15. The project uses smart pointers. 
17. The project uses multithreading.
19. Mutexes and locks are used in the project.



Feature 1. is implemented in poison2.cpp lines 14 through 55

Feature 2. is implemented that the Snake game code consists of 5 main classes: Game, Snake, Controller, Renderer and Poison.
           Member getter function e.g. poison2.cpp lines 52 -55

Feature 3. is implemented in poison2.h lines 8 through 28

Feature 4. is implemented in poison2.cpp lines 6 through 11

Feature 5. is implemented in poison2.cpp line 11

Feature 6. is implemented in renderer.cpp lines 50 through 90

Feature 7. is implemented in main.cpp line 20

Feature 8. is implemented in renderer.cpp line 24 and 34

Feature 9. is implemented in game.cpp line 34 through 47

Feature 10. is implemented in controller.cpp line 24, renderer.cpp line 104, 132



## Multithreading: 

The game runs on 3 threads within the game loop. Various mutexes and locks are used to protect data which is shared across threads.

Thread 1 (started in game.cpp, line 36) runs controller.Handleinput. This requires a mutex/lock (in controller.cpp line 24) to avoid a data race with thread 2. The mutex/lock protects variable Snake::Direction.
 
Thread 2 (started in game.cpp, line 39) runs Game Update. 

Thread 3 (started in game.cpp, line 43) runs Renderer. This requires a mutex/lock (in renderer.cpp line 104) to avoid a data race with thread 2. 












