# Buckshot Roulette Game

Welcome to the Buckshot Roulette Game, a high-stakes game of chance where players test their luck and strategy with a loaded gun and various items to outwit their opponent.

## Features
- **Randomized Gun Loading**: The gun is loaded with live and blank rounds, which are shuffled to add an element of surprise.
- **Item Generator**: Players receive items like cutters, handcuffs, spy glasses, and health kits to gain strategic advantages.
- **Player Turns**: Both the player and the dealer take turns making choices, such as using items, checking the current shell, and shooting.
- **Health and Damage**: Each player has health points and can use health kits to recover. Damage can be doubled with the cutter item.

## How to Play
1. **Load the Gun**: The game begins by loading the gun with a mix of live and blank rounds.
2. **Distribute Items**: Both players receive a random distribution of items.
3. **Take Turns**: Players take turns making decisions:
   - Use items like cutters (double damage), handcuffs (skip opponent's turn), spy glasses (peek inside the gun), and health kits.
   - Choose to shoot at the opponent or themselves.
4. **Win Condition**: The game continues until one player's health reaches zero, declaring the other player the winner.

## Code Overview
### Functions
- `crand(int x)`: Generates a random number.
- `load_gun()`: Loads the gun and shuffles the bullets.
- `item_generator()`: Distributes items to players.
- `spy_glass(int x)`: Allows players to peek inside the current shell.
- `cutter()`: Doubles the damage.
- `health_kit()`: Recovers player's health.
- `player_input()`: Handles player actions and inputs.
- `dealer_input()`: Handles dealer actions and inputs.
- `display()`: Displays the game status and options.

### Main Loop
- The game alternates turns between the player and the dealer.
- The game state is updated based on player actions, and the game checks for win conditions or if the gun needs reloading.

Enjoy the game and may the luck be with you!

## Requirements
- Windows OS
- C++ Compiler
