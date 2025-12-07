# Console Dino Runner 🦖

A simple **Chrome Dinosaur-inspired console game** written in C for Windows. Jump over cacti, survive as long as you can, and beat your high score!

---

## Features

- Console-based gameplay with colorful ASCII graphics.
- Smooth dinosaur running and jumping animations.
- Randomly spawning cacti for endless fun.
- Score tracking and high score system.
- Background music and sound effects for jumps and collisions.
- Beginner-friendly code — perfect for learning game loops and console graphics in C.

---

## How to Play

- **Jump**: Press `SPACE` or `W`  
- **Start Game**: Press `ENTER`  
- **Exit Game**: Press `Q`

Avoid hitting the cacti and try to get the highest score possible! 🏆

---

## Requirements

- Windows OS (uses Windows-specific headers like `windows.h` and `conio.h`)
- A C compiler (like GCC or Visual Studio)
- Sound files:  
  - `music.wav` (background music)  
  - `jump.wav` (jump sound)  
  - `collide.wav` (collision sound)  
  - `freshgame.wav` (start game sound)  
  - `restart.wav` (restart sound)

Make sure these `.wav` files are in the same folder as the executable.

---

## How to Run

1. Clone this repository:

   ```bash
   git clone <your-repo-url>
   ```

2. Compile the game:

   ```bash
   gcc dino_game.c -o dino_game -lwinmm
   ```

3. Run the game:

   ```bash
   ./dino_game
   ```

---

## How It Works

The game uses a **game loop** that updates every frame (based on FPS).
Key components:

* **Input**: Detects jump key (`SPACE` or `W`).
* **Physics**: Handles gravity, jumping, and cactus movement.
* **Collision**: Checks if the dinosaur hits a cactus.
* **Drawing**: Prints the dinosaur, ground, and cacti using ASCII art.
* **Sound**: Plays background music and effects using `PlaySound` and `mciSendString`.

All constants like `FPS`, `DINO_X`, `JUMP_VEL`, etc., are defined at the top for easy modification.

---

## Tips for Beginners

* Try changing `FPS` to make the game faster or slower.
* Modify `JUMP_VEL` or `GRAVITY` to tweak jumping physics.
* Experiment with the ASCII art to make a custom dinosaur!
* Add new obstacles or power-ups for extra fun.

---

## Screenshots

```
[Insert console screenshots of the dinosaur jumping and game over screen here]
```

---

Made with ❤️ in C by Shafin
