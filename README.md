# Connect-Four-in-C-With-Ai-Algorithm

#### Usage : 

#### Description: This is a program that simulates the game Connect-Four. It uses C++ langauge to create a command-line program. It allows for 2 options for the user to choose when starting. They can either go single-player or multi-player. If they decide to do singleplayer, they will fight an Ai that uses the minimax algorithm. Otherwise, it will switch between asking player 1's and player 2's moves.


#### When running the program, it will ask for the user's input if they want to play single or multi-player. Then create an empty board vector as well as refreshing the map used to store the positions of the next input of each column.
When choosing multi#player, the program will randomly select the starting player and ask for the column they wish to insert their coin. Then, the program will call a function each time to check if the move resulted in a win. If so, the program will state the winner and call the replay function to either start another round or exit. Else, it will continue to ask for inputs until the board is full, which it will call a draw and call the replay function.

#### When choosing the single-player mode, the program will switch between the user's turn and the ai. The user's turn will use the same functions as the ones used in the mutliplayer mode. When it's the Ai's turn, the ai will use its algorithm to find the best move at the time. It will look at all possible combination of the board 5 turns into the future and determine the move that results in the highest value. When simulating the board, if it is the Ai's turn aka. maximizing player it will look the move that results in the highest value. Alternatively, if it is the player's turn during the simulation, it will look for the move resulting in the lowest value. These values are a given to these boards when they reach the end of the tree by looking at all the possible 4-line-connections on a board. For each one of our's and the opponent's pieces, the value is added up and down respectively.

#### Functions include :

##### printBoard() creates a board-like line and outputs the values in the board vector.
##### replay() is called when a game is over. It will ask if the user wants to replay again.
##### minimax() is called when the AI has to make a move. It is a recursive function that for each column, it will create a board that has that move played and puts it into the minimax() function again. This will continue until it reaches game-over or it is at max depth, at which it will call the score() function to calculate the board value. At the end, the AI will play the move that results in the highest value. Additionally, if there is a possible move that leads to a win or lose for the AI, it will automatically be put at the highest value and break out of the recursion.
##### score() is called by minimax when trying to evaluate a board. For each row, column, diagonal, and reverse-diagonal, it will create a vector of 4-piece connections with the values of those positions from the board and throw it into the evaluateBoard() function to be summed up. This will continue until the whole board is checked.
##### evaluateBoard() is called by the score() function and calculates the value of the connection and return it to be summed up in score(). For example, a 4-piece connection with 2 AI pieces and 0 opposing pieces will be scored a +3, or a connection with 0 AI pieces and 3 opposing pieces will result in a score of -5.
##### checkboard() is called every turn to check if the latest action resulted in a win. It will check the horizontal, vertical, diagonal, and reverse-diagonal lines spanning out from the piece and returns whether it is a win or not.
##### getInput() is called every start of the turn to ask the user which column they want to insert their coin in. It will check if the into is valid or not as well. It will catch anything that is not a number between 1-7.
