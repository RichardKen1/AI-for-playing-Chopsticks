# AI-for-playing-Chopsticks
AI will play Chopsticks (rollover variation-remains unsolved). It will give move strength for each action, and can also analyze arbitrary positions. 


Inorder to play please enter the number of fingers starting in your hand and your opponents hand (if you want to play the game, just enter 1 
for all values). The AI will spit out a series of moves with an associated strength, as well as the new hand values. If the win is 
forced, it will print out forced win. 

Code utilizes basic tree search algorithm, and evaluation methods as well as a montecarlo search inorder to find best move. The search horizon
is around 7 -10 moves deep. 
