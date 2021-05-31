#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Player.h"
#include "piece_types.h"
#include "color.h"
#include "piece.h"
#include "position.h"
class Chessboard
{
private:
	std::vector<std::shared_ptr<Piece>> whitePieces_;
	std::vector<std::shared_ptr<Piece>> blackPieces_;
	int round_;
public:

	//Creates a new chessboard with default Pieces setup
	Chessboard();

	//Creates a new chessboard with custom Pieces setup
	Chessboard(std::vector<std::shared_ptr<Piece>> firstPlayerPieces, std::vector<std::shared_ptr<Piece>> secondPlayerPieces);

	//Getter to first player pieces vector
	std::vector<std::shared_ptr<Piece>> const& whitePieces() const;

	//Getter to first player pieces vector
	std::vector<std::shared_ptr<Piece>> const& blackPieces() const;

	//Removes given piece from chessboard
	void removePiece(Piece& piece, Color color);

	Piece& getPiece(const Position& position) const;

	bool pieceExists(const Position& position) const;

	void upgradePiece(Piece& piece_to_upgrade, int choice);

	bool checkUpgradePossibility(Player& player);

	Piece& getPieceToUpgrade(Player& player);

	int round();

	void incRound();

	bool checkIfCheck(Player& player, Color color);

	bool checkShortCastlePossibility(Player& player, Color color);

	bool checkLongCastlePossibility(Player& player, Color color);

	std::pair<std::shared_ptr<Piece>, Position> getShortCastle(Color color);

	std::pair<std::shared_ptr<Piece>, Position> getLongCastle(Color color);

	void doShortCastle(Color color);

	void doLongCastle(Color color);

	bool checkAttackPossibility(Player& player, const Position& position);

	bool checkWin(Color color);

	void printLine(int lineNumber, int firstColor, int secondColor, std::ostream& os) const; 

	friend std::ostream& operator<<(std::ostream& os, const Chessboard& chessboard);
};
