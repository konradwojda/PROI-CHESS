#include "Game.h"
#include <memory>

//Game::Game(Chessboard chessboard, Player* firstPlayer, Player* secondPlayer)
//{
//	chessboard_ = chessboard;
//	firstPlayer_ = std::unique_ptr<Player>(firstPlayer);
//	secondPlayer_ = std::unique_ptr<Player>(secondPlayer);
//}
Game::Game()
{
	
}

void Game::rollOrder()
{
	int result = rand() % 2 + 1;
	if (result == 1)
	{
		currentPlayer_ = firstPlayer_.get();
	}
	else if (result == 2)
	{
		currentPlayer_ = secondPlayer_.get();
	}
}

void Game::swap()
{
	if (*currentPlayer_ == *firstPlayer_)
	{
		currentPlayer_ = secondPlayer_.get();
		return;
	}
	else if (*currentPlayer_ == *secondPlayer_)
	{
		currentPlayer_ = firstPlayer_.get();
		return;
	}
}

void Game::playPvP()
{
	chessboard_ = Chessboard();
	std::cout << "Please enter the name for player with white pieces. \n";
	std::string white_player_name;
	std::cin >> white_player_name;
	auto white_player = std::make_unique<Human>(Human(White, white_player_name, chessboard_));
	firstPlayer_ = std::move(white_player);
	std::cout << "Please enter the name for player with black pieces. \n";
	std::string black_player_name;
	std::cin >> black_player_name;
	auto black_player = std::make_unique<Human>(Human(Black, black_player_name, chessboard_));
	secondPlayer_ = std::move(black_player);
	firstPlayer_->setEnemy(secondPlayer_.get());
	secondPlayer_->setEnemy(firstPlayer_.get());
	this->rollOrder();
	bool check = false;
	do
	{
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << chessboard_ << std::endl;
		if (chessboard_.checkIfCheck(*firstPlayer_, Black))
		{
			std::cout << secondPlayer_->getName() << " is under attack! " << std::endl;
		}
		if (chessboard_.checkIfCheck(*secondPlayer_, White))
		{
			std::cout << firstPlayer_->getName() << " is under attack! " << std::endl;
		}
		std::cout << "It's " << currentPlayer_->getName() << " move. ";
		currentPlayer_->makeMove(chessboard_);
		if (chessboard_.checkUpgradePossibility(*currentPlayer_))
		{
			std::cout << currentPlayer_->getName() << " has to upgrade pawn. " << std::endl;
			std::cout << "Choose your upgrade: 1 - queen, 2 - knight, 3 - bishop, 4 - rook" << std::endl;
			int choice;
			std::cin >> choice;
			chessboard_.upgradePiece(chessboard_.getPieceToUpgrade(*currentPlayer_), choice);
		}
		this->swap();
	} 	while (!chessboard_.checkWin(White) && !chessboard_.checkWin(Black));
	if (chessboard_.checkWin(firstPlayer_->getColor()))
	{
		std::cout << firstPlayer_->getName() <<  " wins!" << std::endl;
	}
	if (chessboard_.checkWin(secondPlayer_->getColor()))
	{
		std::cout << secondPlayer_->getName() << " wins!" << std::endl;
	}
}

void Game::playPvB()
{
	chessboard_ = Chessboard();
	std::cout << "Please enter your name. You will play with white pieces. \n";
	std::string player_name;
	std::cin >> player_name;
	auto player = std::make_unique<Human>(Human(White, player_name, chessboard_));
	firstPlayer_ = std::move(player);
	auto bot = std::make_unique<RandIntBot>(RandIntBot(Black, "Bot", chessboard_));
	secondPlayer_ = std::move(bot);
	firstPlayer_->setEnemy(secondPlayer_.get());
	secondPlayer_->setEnemy(firstPlayer_.get());
	this->rollOrder();
	do
	{
		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << chessboard_ << std::endl;
		if (chessboard_.checkIfCheck(*firstPlayer_, Black))
		{
			std::cout << secondPlayer_->getName() << " is under attack! " << std::endl;
		}
		if (chessboard_.checkIfCheck(*secondPlayer_, White))
		{
			std::cout << firstPlayer_->getName() << " is under attack! " << std::endl;
		}
		std::cout << "It's " << currentPlayer_->getName() << " move. ";
		currentPlayer_->makeMove(chessboard_);
		if (chessboard_.checkUpgradePossibility(*currentPlayer_))
		{
			std::cout << currentPlayer_->getName() << " has to upgrade pawn. " << std::endl;
			std::cout << "Choose your upgrade: 1 - queen, 2 - knight, 3 - bishop, 4 - rook" << std::endl;
			int choice;
			std::cin >> choice;
			chessboard_.upgradePiece(chessboard_.getPieceToUpgrade(*currentPlayer_), choice);
		}
		this->swap();
	} while (!chessboard_.checkWin(White) && !chessboard_.checkWin(Black));
	if (chessboard_.checkWin(firstPlayer_->getColor()))
	{
		std::cout << firstPlayer_->getName() << " wins!" << std::endl;
	}
	if (chessboard_.checkWin(secondPlayer_->getColor()))
	{
		std::cout << secondPlayer_->getName() << " wins!" << std::endl;
	}
}

void Game::play()
{
	int choice;
	std::cout << "Welcome to chess game. Please choose game mode. " << std::endl;
	std::cout << "1. Player versus player mode. \n";
	std::cout << "2. Player versus bot mode. " << std::endl;
	std::cin >> choice;
	if (choice == 1)
		this->playPvP();
	else if (choice == 2)
		this->playPvB();
	else
		system("pause");
}