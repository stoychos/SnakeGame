Dependencies 

You will need OpenGL and freeglut installed to run the game

Q-Learning algorithm is used to solve Snake game - the snake will need approximately 10 minutes of training for a good result

Steps

  1. Get current state of the game S
    1.1 The state S of the game is represented as 11 booleans\
      1.1.1 3 booleans representing potential danger in front of the snake\
      1.1.2 4 booleans representing the position of the food relative to snake's head\
      1.1.3 4 booleans representing the current direction of movement\
      As an example - (1 0 0 0 1 0 1 0 1 0 0) = S, means that there is a danger in the left(1 0 0), the position of the food relative to 
      the snake's head is right and down(0 1 0 1), and the direction of movement is right(0 1 0 0)
  2. Get best action for state S
    2.1 To every state of the game which is already present(they are stored in a map), is mapped a vector with actions and the value for       
    each action. Best action is that with max value for the current state.\
    (1 0 0 0 1 0 1 0 1 0 0) -> 0,312 0,1 0 -1,2. Best action will be 0,312, or left.
  3. The snake gets the relevant award for the chosen action 
    3.1 If the food is eaten, the reward for the action is +1
    3.2 If the snake crashes, reward for the action is -1
    3.3 If the food is not eaten, but the snake doesn't crash, reward is -0,1
  4. Get next state of the game and update Q-table 
    4.1 ![alt text](https://github.com/stoychos/SnakeGame/blob/master/qtable_f.png)
    The formula used to update the q-table, source: wikipedia

  
 
  
