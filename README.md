# Connect 4
## Abstract
This code uses a modified Monte Carlo Tree Search, as well as Upper Confidence Trees (similar to AlphaGo). The algorithm branches off from the current game state into the different move possibilities to find out which move yields highest chance of winning. In order to account for time, the algorithm cuts short right before the 3 second mark and chooses the best possibility from the existing tree.

## How to use
Source code is found in `Connect4/Strategy`  
Compile with Visual Studio to make a .dll  
Run UI.sln in `Connect4/UI`

## Implementation
Our task was to modify 2 functions, getPoint and clearPoint, so that other programs may use them. 
One of the parameters for getPoint was a 2d array named board. In order to check for wins more efficiently, we will store the board state in 4 1d arrays, representing each of the 4 directions one can win (inspired by the 8 queen’s problem). We also use bit manipulation to make the process faster. Because our implementation is different, we end up not using many of the provided functions.
Monte Carlo Tree Search uses the upper confidence trees (UCT) to choose the move with the most value. The formula for UCT is:

Si = xi + C * sqrt(ln(t)/ni)
 
Where:

Si = value of a node i  
xi = empirical mean of a node I (wins/simulations for the given node)  
C = a constant (around sqrt(2))  
t = total number of simulations

The child node that returns the highest value will be selected.

## Experimental Results
For my experimental procedure, I first wrote a python script that had my dll compete against all 100 of the test dlls 5 times in order to gauge the skill of the test cases. My strategy lost its first game against 47.dll, so I formed my testcases based on these results.

| Opponent | Total Games | Wins | Win rate |
| :------- | :---------- | :--- | :------- |
| 47 | 10 | 10 | 100% |
| 55 | 10 | 10 | 100% |
| 65 | 10 | 9 | 90% |
| 75 | 15 | 13 | 86.66% |
| 85 | 15 | 14 | 93.33% |
| 95 | 15 | 13 | 86.66% |
| 100 | 50 | 44 | 88% |

## Conclusion
Overall the results were better than what I had expected. I had a rough time playing against the toughest dll, and I would guess that my winrate was around 20% without redos.

At first, I thought that the biggest limiting factor was the 3 second limit. Memory wasn’t an issue since I used arrays instead of node structs. Because of this, I switched from using arrays in Board to using bit manipulation. After testing more however, I realized that time didn’t matter too much. The game itself is small enough that it wouldn’t affect the result too much. With that being said, I’m not sure how I could optimize the algorithm even further without having it just test every possibility. 
