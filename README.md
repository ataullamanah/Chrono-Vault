# Chrono Vault: A C++ Time-Travel Dungeon Crawler

**Chrono Vault** is a console-based dungeon crawler game written in C++. Explore a randomly generated 10x10 maze, collect time crystals, avoid traps, and use a unique time-rewind mechanic to undo mistakes. This project showcases advanced C++ concepts like stack-based state management, file I/O for high-score persistence, and dynamic dungeon generation, making it a fun game and a valuable learning tool.

## Features
- **Random Dungeons**: Navigate a 10x10 grid with walls ('#'), crystals ('C'), and traps ('T').
- **Time Rewind**: Undo up to 5 moves at the cost of energy, adding strategic depth.
- **Energy System**: Collect crystals to restore energy; moving and rewinding consume it.
- **High Score**: Persistent high-score tracking based on crystals collected.
- **Simple Controls**: Use WASD to move, 'r' to rewind time, 'q' to quit.

## How to Play
1. Clone the repository: `git clone <your-repo-url>`
2. Compile the game: `g++ ChronoVault.cpp -o ChronoVault`
3. Run the game: `./ChronoVault` (Linux/Mac) or `ChronoVault.exe` (Windows)
4. Move with WASD to collect Crystals ('C'), avoid Traps ('T'), and navigate around Walls ('#').
5. Use 'r' to rewind time if you hit a trap or make a mistake (costs energy).
6. Survive as long as possible to maximize your score; high score is saved automatically.

## Why Sponsor?
Chrono Vault is an engaging, extensible game that demonstrates sophisticated C++ programming. By sponsoring, you’ll support:
- Adding a graphical interface using SFML or SDL for a modern look.
- Implementing online leaderboards for competitive play.
- Introducing new mechanics like enemies or time-based puzzles.
- Creating educational tutorials on C++ game development and state management.

## Contributing
Contributions are welcome! Fork the repository, submit issues, or create pull requests. Suggestions for new dungeon features, mechanics, or UI improvements are appreciated.

## Future Plans
- Develop a graphical UI with SFML or SDL.
- Add enemies that patrol the dungeon.
- Implement procedurally generated levels with varying sizes.
- Support custom dungeon layouts via input files.

## License
MIT License - feel free to use and modify this code for your own projects.

## Contact
Reach out via GitHub Issues or [your contact info] for questions or collaboration.

*Built with passion by [Your Name]. Support this project via [GitHub Sponsors](#)!*