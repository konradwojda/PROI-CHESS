#pragma once
#include <string>
#include <vector>
#include <memory>
#include "piece.h"
#include "position.h"

class Piece;

class Chessboard;

class Player
{
private:
	Color color_; // 0 for black, 1 for white
	std::string name_;
	Player* enemy_ = nullptr;

public:
	// Player class constructor
	Player(Color color, std::string playerName, const Chessboard& chessboard);

	// issues a move(will change depending on derivative class)
	virtual void makeMove(Chessboard& chessboard) = 0;

	virtual void doAvailableUpgrades(Chessboard& chessboard) = 0;

	// sets color
	void setColor(Color color);

	void setEnemy(Player* enemy);

	// gets name
	std::string getName();

	Player* getEnemy();

	// gets name
	Color getColor();

	// gets all possible movements from individual pieces
	std::vector<std::pair<std::shared_ptr<Piece>, Position>> allPossibleMoves(const Chessboard& chessboard);

	// checks if players are the same
	bool operator==(Player& player);

};

class Human : public Player
{
public:
	Human(Color color, std::string playerName, const Chessboard& chessboard) : Player(color, playerName, chessboard) {};
	void makeMove(Chessboard& chessboard) override;
	void doAvailableUpgrades(Chessboard& chessboard) override;

};

class RandIntBot : public Player
{
public:
	RandIntBot(Color color, std::string playerName, const Chessboard& chessboard) : Player(color, playerName, chessboard) {};
	void makeMove(Chessboard& chessboard) override;
	void doAvailableUpgrades(Chessboard& chessboard) override;

};

