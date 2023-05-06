# Tetris Clone with SFML Library

This is my implementation of the popular Tetris game, written in C++ using the SFML library (No game engine is used). The game is functional with most of the features that you'd expect from a classical Tetris game.

## Features

- ✅ **Randomizer**: The game uses the bag randomizer, which ensures that each shape is guaranteed to appear once in every seven pieces. This prevents the player from having long droughts and adds an extra layer of strategy to the game.
- ✅ **Rotation**: Basic rotations from Super Rotation System (SRS) has been applied.
- ❌ **Wall Kicks**: Not implemented yet.
- ❌ **Highscore System**: Not implemented yet.
- ❌ **Time Mode**: Not implemented yet.
- ✅ **Leveling**: After each 10 line clears, level of the player is incremented by one and the speed of the falling shapes increases. Following formula is applied: **Time for Falling 1 Cell Down = (0.8 - ((Level - 1) * 0.007))<sup>(Level-1)</sup>**
- ✅ **Lock Delay**: Once a current piece is landed, it will be locked by a duration of **falling one cell down**. This duration will be less as the player progresses through the levels.
- ✅ **Next Piece**: In order to keep the game more challenging, only 1 next piece is shown on the UI.
- ✅ **Scoring**: Following is the score table for different numbers of clear lines.
    - Single: 100,
    - Double: 300,
    - Triple: 1000
    - Tetris: 1400
- ✅ **Sounds**: Thanks to [MadRooster Game Audio Lab](https://www.madrooster.co), we have sound effects in this game. 🙏🏻
- ✅ **Asset Manager**: AssetManager class loads the game assets from file, and holds them in a map. Assets have a static access everywhere in the project since the class uses Singleton pattern.
- ✅ **Game States**: States of the game, such as MainMenuState, InGameState and GameOver states are handled by using State Pattern. It is very easy to transition between states thanks to StateMachine class.

## Requirements

To run this game, you will need to have the SFML library installed on your system. You can download [SFML from the official website](https://www.sfml-dev.org/download.php), and follow the installation instructions for your operating system.

## How to Play

- You definitely know how to play Tetris. But here is the controls in case you forgot: 
    - **Move Left**:   A | Left Arrow
    - **Move Right**:  D | Right Arrow
    - **Rotate**:      W | Up Arrow
    - **Soft Drop**:   S | Down Arrow
    - **Hard Drop**:  Spacebar
    - Once a horizontal line is completed, it disappears from the board, and the player earns points. The game ends when the player cannot stack a new shape because there is no more room on the board.

## Conclusion

This project was a challenge for me to test my C++ skills and understanding of graphics libraries. If you have any questions or comments, please feel free to reach out to me. Enjoy the game!
