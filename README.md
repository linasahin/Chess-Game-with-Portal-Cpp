# ♟️ Chess Game with Portals (C++)

A custom chess game implemented in C++ using a JSON-based configuration system. It includes unique **portal teleportation** mechanics and supports standard chess moves, undo functionality, and a turn-based interface.

## 🚀 Features
- Standard chess moves (Pawn, Rook, Knight, Bishop, Queen, King).
- Portals on the board that teleport pieces.
- Portal cooldown and allowed colors.
- Move undo functionality.
- Display current board status.
- JSON file for game settings and portal configurations.

## 🛠️ Technologies
- C++17
- nlohmann/json library for JSON parsing
- VS Code / MinGW (development environment)
- Makefile for easy compilation

## 📂 Project Structure
include/
├── ChessBoard.hpp
├── ChessPiece.hpp
├── ConfigReader.hpp
├── GameManager.hpp
├── MoveRecord.hpp
├── MoveValidator.hpp
├── Portal.hpp
├── PortalCooldownManager.hpp
├── nlohmann/json.hpp

src/
├── ChessBoard.cpp
├── ConfigReader.cpp
├── GameManager.cpp
├── main.cpp
├── MoveValidator.cpp
├── Portal.cpp
├── PortalCooldownManager.cpp

Makefile
data/ (game configurations)

## ⚡ How to Run
make
./chessgame

## Author
- 👩‍💻 Lina Şahin
