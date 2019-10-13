Dependencies 

You will need OpenGL and freeglut installed to run the game

Q-Learning algorithm is used to solve Snake game - the snake will need approximately 10 minutes of training for a good result

Steps-

  1. Get current state of the game S
  2. Get best action for state S 
  3. The snake gets the relevant award for the chosen action 
  4. Get next state of the game and update Q-table 
  
Representation of the game\
  1. The state S of the game is represented as 11 booleans\
    1.1 3 booleans representing potential danger in front of the snake
    ![alt text](https://github.com/stoychos/SnakeGame/blob/master/danger.png)    
    1.2 4 booleans representing the position of the food relative to snake's head
    ![alt text](https://github.com/stoychos/SnakeGame/blob/master/position_of_food.png)
    1.3 4 booleans representing the current direction of movement
    ![alt text](https://github.com/stoychos/SnakeGame/blob/master/direction.png)
  2. To every state of the game which is already present( they are stored in a map), is mapped a vector with actions and the value for each     action. Best action is that with max value for the current state.\
  
 
  
