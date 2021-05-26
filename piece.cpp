#include "Chessboard.h"
#include "piece.h"

Piece::Piece(Position startPosition, Color color) : position_(startPosition), color_(color) {

}

Color Piece::color() const {
	return color_;
}

Position Piece::position() const {
	return position_;
}

void Piece::move_to(Chessboard& chessboard, Position newPosition) {
	position_ = newPosition;

	std::vector<std::shared_ptr<Piece>> enemyPieces = color() == White ? chessboard.blackPieces() : chessboard.whitePieces();

	for (auto piece = enemyPieces.begin(); piece != enemyPieces.end(); piece++) // TODO: Change to getting the pieces by color
	{
		if ((**piece).position_ == position_)
		{
			//chessboard.removePiece((**piece), ); // How do i get the player exactly?
		}
	}
}

void Piece::try_add_movement_option(Position pos, std::vector<Position>& positions, const Chessboard& chessboard) const {
	if (pos.on_chessboard()) {
		if (!chessboard.pieceExists(pos) || chessboard.getPiece(pos).color() != color()) {
			positions.push_back(pos);
		}
	}
}

bool Piece::operator==(const Piece& other) const {
	return full_name() == other.full_name() && position_ == other.position_ && color_ == other.color_;
}

bool Piece::operator!=(const Piece& other) const {
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Piece& piece) {
	out << piece.chessboard_representation();
	return out;
}

Pawn::Pawn(Position startPosition, Color color) : Piece(startPosition, color), firstMove_(true) {}

std::string Pawn::full_name() const {
	return "Pawn";
}

char Pawn::chessboard_representation() const {
	return color() == White ? 'p' : 'P';
}

std::vector<Position> Pawn::possible_moves(const Chessboard& chessboard) const {
	std::vector<Position> possible;
	Position pos = position();

	if (color() == White) {
		if (pos.y() < 8) {
			possible.push_back(pos + Position(1, 0));
		}

		if (firstMove_ && pos.y() < 7) {
			possible.push_back(pos + Position(2, 0));
		}

		auto tryPos = pos + Position(1, -1);
		if (chessboard.pieceExists(tryPos)) {
			try_add_movement_option(tryPos, possible, chessboard);
		}

		tryPos = pos + Position(1, 1);
		if (chessboard.pieceExists(tryPos)) {
			try_add_movement_option(tryPos, possible, chessboard);
		}
	}
	else {
		Position pos = position();
		if (pos.y() > 1) {
			possible.push_back(pos + Position(-1, 0));
		}

		if (firstMove_ && pos.y() > 2) {
			possible.push_back(pos + Position(-2, 0));
		}

		auto tryPos = pos + Position(-1, -1);

		if (chessboard.pieceExists(tryPos)) {
			try_add_movement_option(tryPos, possible, chessboard);
		}

		tryPos = pos + Position(-1, 1);
		if (chessboard.pieceExists(tryPos)) {
			try_add_movement_option(tryPos, possible, chessboard);
		}
	}

	return possible;
}

void Pawn::on_moved(Position newPosition) {
	firstMove_ = false;
}

std::string Knight::full_name() const {
	return "Knight";
}

char Knight::chessboard_representation() const {
	return color() == White ? 'n' : 'N';
}

std::vector<Position> Knight::possible_moves(const Chessboard& chessboard) const {
	std::vector<Position> possible;
	for (int x = -1; x < 1; x += 1) {
		for (int y = -2; y < 2; y += 4) {
			try_add_movement_option(position() + Position(x, y), possible, chessboard);
			try_add_movement_option(position() + Position(y, x), possible, chessboard);
		}
	}

	return possible;
}

std::string Bishop::full_name() const {
	return "Bishop";
}

char Bishop::chessboard_representation() const {
	return color() == White ? 'b' : 'B';
}

std::vector<Position> Bishop::possible_moves(const Chessboard& chessboard) const {
	std::vector<Position> possible;

	// TODO: add movement

	return possible;
}

std::string Rook::full_name() const {
	return "Rook";
}

char Rook::chessboard_representation() const {
	return color() == White ? 'r' : 'R';
}

std::vector<Position> Rook::possible_moves(const Chessboard& chessboard) const {
	std::vector<Position> possible;

	// TODO: add movement

	return possible;
}

std::string Queen::full_name() const {
	return "Queen";
}

char Queen::chessboard_representation() const {
	return color() == White ? 'q' : 'Q';
}

std::vector<Position> Queen::possible_moves(const Chessboard& chessboard) const {
	std::vector<Position> possible;

	// TODO: add movement

	return possible;
}

std::string King::full_name() const {
	return "King";
}

char King::chessboard_representation() const {
	return color() == White ? 'k' : 'K';
}

std::vector<Position> King::possible_moves(const Chessboard& chessboard) const {
	std::vector<Position> possible;

	// TODO: add movement

	return possible;
}