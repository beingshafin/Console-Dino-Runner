# Lab Project Report: Console Dino Runner

## Chapter 1
### Introduction
This chapter outlines the background, motivation, and objectives of the Console Dino Runner project.

#### 1.1 Introduction
The "Console Dino Runner" is a console-based game application developed in the C programming language. It is a recreation of the popular offline dinosaur game found in the Google Chrome web browser. The project demonstrates the capability of standard C libraries to create interactive, real-time graphical applications within a command-line interface. The core problem this project aims to address is the creation of a lightweight, entertainment application that runs efficiently on low-resource environments without the need for a graphical user interface (GUI) or web browser.

#### 1.2 Motivation
The primary computational motivation for this project is to explore and implement the fundamental concepts of game development—specifically the "game loop"—within a procedural programming paradigm. Developing a real-time application in C requires handling user input interruptions, managing frame timing, and rendering graphics using ASCII characters. Solving these problems provides deep insights into memory management, coordinate systems (for console cursor positioning), and basic physics simulation (gravity and velocity). This project benefits the developer by solidifying their understanding of C pointers, standard I/O, and system-level interactions.

#### 1.3 Objectives
The specific objectives of the project are:
1.  To design and implement a stable game loop that updates game state at a consistent frame rate.
2.  To implement collision detection logic between the player (dino) and obstacles (cacti).
3.  To create a responsive control system that handles user input for jumping and game control.
4.  To utilize the Windows API (`windows.h`) for console manipulation (cursor hiding, positioning, colors) and sound playback.
5.  To provide a scoring system that tracks current progress and high scores.

#### 1.4 Feasibility Study
Similar research and projects exist primarily in the realm of educational game development.
*   **Existing Web Applications:** The original Chrome Dino Game is a JavaScript/HTML5 Canvas application. It requires a browser engine to run.
*   **Existing Mobile Apps:** Numerous clones exist on App Stores, typically built with engines like Unity.
*   **Methodological Contribution:** This project differentiates itself by stripping away heavy graphics engines. It relies solely on `stdio.h` and `conio.h`, proving that engaging gameplay can be achieved with minimal dependencies. It runs natively on Windows Command Prompt.

#### 1.5 Gap Analysis
Most modern game projects utilize high-level engines (Unity, Unreal) or frameworks (SDL, Pygame) that abstract away the low-level logic of rendering and timing. The gap addressed here is the lack of educational resources that demonstrate *how* these high-level concepts work at the bare metal (console) level. This project bridges that gap by implementing gravity, collision, and rendering manually.

#### 1.6 Project Outcome
The outcomes of this work include:
1.  A fully functional executable (`dino.exe`) playable on Windows.
2.  Source code (`dino.c`) that serves as an educational reference for C students.
3.  A documented implementation of a finite state machine (Menu -> Game -> Game Over) in C.

**Timeline Flow:**
*   **Problem identification:** Need for a simple C-based game for learning.
*   **Literature review:** Studying `conio.h` and game loop logic.
*   **Observation & analysis:** Analyzing the physics of the original Chrome game (jump arc, speed).
*   **Result & findings:** Successful replication of gameplay mechanics in text mode.

---

## Chapter 2
### Proposed Methodology/Architecture
This chapter details the system requirements, architecture, and design specifications used to build the game.

#### 2.1 Requirement Analysis & Design Specification

##### 2.1.1 Overview
The system is designed as a single-threaded application that loops continuously until the user chooses to exit. It requires a Windows environment due to the dependency on `windows.h` for console control and `mciSendString` for audio.

##### 2.1.2 Proposed Methodology/ System Design
The system follows a classic Game Loop architecture:

1.  **Input:** Poll keyboard buffer (`kbhit()`, `getch()`) for 'Space', 'W', 'Enter', or 'Q'.
2.  **Update:** 
    *   Apply gravity to Dino's Y position.
    *   Update horizontal position of Cacti.
    *   Check for collisions.
    *   Update score.
3.  **Render:** 
    *   Clear screen (or update specific portions).
    *   Draw Ground.
    *   Draw Dino (with animation frames).
    *   Draw Cactus.
    *   Draw Score.
4.  **Sync:** Wait for a specific duration (`Sleep(gameDelay)`) to control FPS.

*(Conceptual Diagram)*
`Start -> [Game Loop] -> { Input -> Physics Update -> Collision Check -> Render } -> Wait -> Repeat`

##### 2.1.3 UI Design
The User Interface is text-based (ASCII Art).
*   **Lobby Screen:** Displays the logo, dinosaur art, and control instructions.
*   **Game Screen:**
    *   **Top:** Score and High Score.
    *   **Center:** The play area featuring the Dino sprite and moving Cacti.
    *   **Bottom:** The ground line.
*   **Game Over Screen:** Displays the final score and prompts to restart or exit.

#### 2.2 Overall Project Plan
The development followed an agile approach:
1.  **Phase 1:** Setup console environment (hide cursor, `gotoxy` function).
2.  **Phase 2:** Implement Dino jumping physics.
3.  **Phase 3:** Implement Cactus spawning and movement.
4.  **Phase 4:** Add collision detection and scoring.
5.  **Phase 5:** Polish (Sound effects, colors, start/end screens).

---

## Chapter 3
### Implementation and Results
This chapter discusses the coding implementation, performance metrics, and final results of the project.

#### 3.1 Implementation
The core implementation is contained within `dino.c`. Key functions include:
*   `gotoxy(int x, int y)`: Moves the console cursor to specific coordinates for drawing, avoiding the flicker of full screen clears.
*   `drawDino(int dinoY, int legAnimation)`: Renders the dinosaur sprite. It toggles between two frames for leg animation to simulate running logic.
*   `update()`: The physics engine. It calculates:
    ```c
    dinoY += dinoVel / 5;
    dinoVel -= GRAVITY;
    ```
    This creates a smooth parabolic arc for the jump.
*   `drawCactus(int x)`: Handles the rendering of obstacles, including "clipping" logic to prevent drawing artifacts when obstacles enter/leave the screen edge.

#### 3.2 Performance Analysis
The application runs extremely efficiently as it manipulates text buffers rather than pixel graphics.
*   **Memory Usage:** Minimal (< 2MB), as it stores only integer state variables and string literals.
*   **CPU Usage:** Negligible. The `Sleep(gameDelay)` function ensures the CPU is not 100% utilized, yielding time back to the OS between frames.
*   **Frame Rate:** Controlled by `gameDelay`. Initially set for smooth gameplay, and logic exists to speed up the game (`gameDelay *= 0.9`) as the score increases, increasing difficulty without degrading performance.

#### 3.3 Results and Discussion
The project successfully compiles with GCC (`gcc dino.c -o dino -lwinmm`).
*   **Gameplay:** The dino jumps smoothly, and hitboxes are accurate enough for fair gameplay.
*   **Audio:** Sound effects for jumping and collisions play asynchronously, enhancing the experience.
*   **Stability:** The application handles input gracefully and does not crash on edge cases (e.g., rapid key presses).

---

## Chapter 4
### Engineering Standards and Mapping
This chapter analyzes the societal impact and maps the project to engineering program outcomes.

#### 4.1 Impact on Society, Environment and Sustainability

##### 4.1.1 Impact on Life
While primarily for entertainment, this project serves as a low-stress cognitive exercise improving reaction time. It is accessible to users with low-end hardware, bridging the digital divide in gaming accessibility.

##### 4.1.2 Impact on Society & Environment
The software is purely digital and consumes minimal energy compared to AAA games, contributing to lower carbon footprints for gaming activities. It promotes the "Green Computing" philosophy by extending the useful life of older hardware.

##### 4.1.3 Ethical Aspects
 The project respects copyright by being an "inspired by" work rather than a direct asset rip. It uses custom or generic ASCII art code. No user data is collected, ensuring 100% privacy.

##### 4.1.4 Sustainability Plan
The code is written in standard C (mostly), making it highly maintainable. The use of open-source compilers contributes to sustainable software development practices.

#### 4.2 Project Management and Team Work
*   **Budget:** $0.00. Built using open-source tools (GCC, VS Code).
*   **Revenue Model:** Freeware/Open Source. Potential revenue could be generated if ported to mobile platforms with ads, but the current scope is non-profit.
*   **Timeline:** Completed within the university semester timeline.

#### 4.3 Complex Engineering Problem

##### 4.3.1 Mapping of Program Outcome
Table 4.1: Justification of Program Outcomes

| PO’s | Justification |
| :--- | :--- |
| PO1 (Engineering Knowledge) | Applied knowledge of C programming, memory management, and physics formulas. |
| PO2 (Problem Analysis) | Analyzed the requirements for real-time rendering in a static text terminal. |
| PO3 (Design/Interpretation) | Designed a collision detection algorithm suitable for irregular ASCII shapes. |

##### 4.3.2 Complex Problem Solving
Table 4.2: Mapping with complex problem solving.

| EP1 | EP2 | EP3 | EP4 | EP5 | EP6 | EP7 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Depth of Knowledge** | **Conflicting Requirements** | **Depth of Analysis** | **Familiarity of Issues** | **Applicable Codes** | **Stakeholder Involvement** | **Inter-dependence** |
| High (Pointers, Memory) | High (Speed vs Flicker) | Med (Physics Logic) | Low (New domain) | High (C Standards) | Low (Solo dev) | Med (OS API) |

##### 4.3.3 Engineering Activities
Table 4.3: Mapping with complex engineering activities.

| EA1 | EA2 | EA3 | EA4 | EA5 |
| :--- | :--- | :--- | :--- | :--- |
| **Range of resources** | **Interaction** | **Innovation** | **Consequences** | **Familiarity** |
| Hardware/Software tools | User Input Handling | ASCII Physics Engine | Educational Value | C Syntax/Logic |

---

## Chapter 5
### Conclusion
This chapter summarizes the project achievements and outlines future improvements.

#### 5.1 Summary
The "Console Dino Runner" project successfully met all its objectives. It provides a functional, endless runner game with scoring, audio, and progressive difficulty. It demonstrates that complex behaviors like animation and physics can be implemented in a simple console environment using C.

#### 5.2 Limitation
*   **Graphics:** Limited by the character set and grid of the console window.
*   **Platform:** Heavily dependent on Windows libraries (`conio.h`, `windows.h`), making it non-portable to Linux/macOS without refactoring.
*   **Input:** `getch()` can occasionally be blocking or unresponsive if not handled carefully in tight loops (though currently mitigated).

#### 5.3 Future Work
*   **Cross-Platform Support:** Refactor using `ncurses` to support Linux systems.
*   **Enhanced Graphics:** Implement color palettes for different times of day (day/night cycle).
*   **Save System:** Implement file I/O to save high scores permanently to a `.txt` file.
*   **New Obstacles:** Add flying pterodactyls that require the player to duck (using the 'S' key).
