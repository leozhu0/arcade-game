README.md

# Bullet Hell
by Leo Zhu, John Lins, Jennifer Lopez, and Kevin Lee

For our arcade game, we have created a bullet hell style game. The point of the game is to have the player clear all the mobs in order to win. Enemies are destroyed after 20 hits by the player. Enemies also fire projectiles at the player which kills the player. The player dies after one hit by a mob. The projectiles of enemies are spawned randomly in waves and the player should avoid them while trying to kill the enemies. 

# Scoring
Game Over: Player is killed by a projectile. The player earns no score because they didn't finis the game
           Player fails to kill all the enemies within the alloted time.
Game Win: Player kills all the enemies within 2 minutes.
          The faster they kill all the enemies, the higher the score.
          The slower they kill all the enemies, the lower the score

## How to Play

Once the window loads, follow the instructions to start the game. The player's position is controlled by the mouse. The player’s character can fire projectiles at the enemies by using the `spacebar`. The enemies will begin to move around the screen and fire projectiles at the player.


## How to Compile Using The Makefile

To build the game:
- Open your terminal use `make`
- Then use `./main`
- To clean up built files, use `make clean`.

## Exiting The Game
Use the command `ctrl C` on your terminal to exit the game.
