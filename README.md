Snake Game in C++
=================

A simple snake game written in C++ using Data structures and OOPS concepts.

***Idea Behind The Code***

**Components**

* **Board**: The game board where the snake moves.
* **Snake**: A series of characters represented as an array.
* **Food**: A point on the board that the snake can eat to increase its score.

**Variables outline**

* **Point**: A structure to represent a point on the board.
	+ `x_cord`: The x-coordinate of the point (int).
	+ `y_cord`: The y-coordinate of the point (int).
* **Snake**: A class to represent the snake.
	+ `length`: The length of the snake (int).
	+ `Direction`: The direction of the snake (char, one of 'W', 'S', 'A', 'D').

**Board**: A class to represent the game board.
	+ `snake`: An instance of the Snake class.
	+ `score`: The current score of the game (int).
	+ `food`: A point on the board where the food is located (Point struct).

**Rules**

* If the snake is moving up (`Direction = 'W'`) and the user presses down (`Keypress = 'S'`), the game stops.
* If the snake is moving down (`Direction = 'S'`) and the user presses up (`Keypress = 'W'`), the game stops.
* If the snake is moving right (`Direction = 'A'`) and the user presses left (`Keypress = 'D'`), the game stops.
* If the snake is moving left (`Direction = 'D'`) and the user presses right (`Keypress = 'A'`), the game stops.


**How to Play**

1. Clone the repository and compile the code using a C++ compiler.
2. Run the executable file.
3. Use W,A,S,D to control the snake.
4. Eat food to increase your score.
5. Avoid hitting the walls or yourself.

**Contributing**

If you'd like to contribute to this project, please fork the repository and submit a pull request.

**License**

This project is licensed under the MIT License.
