#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

// Include other functions
//// The order in which these are loaded is important, hence the structs file first.  We should think about redoing/ordering or something
#include "client/structs.cpp"
#include "client/file_funcs.cpp"
#include "client/list_moves.cpp"
#include "client/make_move.cpp"
#include "client/print_board.cpp"
#include "client/get_possible_moves.cpp"
#include "client/check_check.cpp"
#include "client/piece_reach.cpp"
#include "client/parse_input.cpp"
#include "client/player_move.cpp"
#include "engine/engine_move.cpp"
#include "client/generate_board.cpp"

// Run program
int main()
{
	// Display welcome message
	cout << "Welcome to Chess++!" << endl;
	cout << "Press Enter for a new game, otherwise input a path to a FEN file or the FEN sequence here." << endl;
	string start_input;
	// getline(cin, start_input);
	start_input = "ch_fen2.txt"; //// faster testing of FEN input, remove later
	// start_input = ""; //// faster testing of blank input, remove later

	board::ChessBoard current_board;
	if (filesystem::exists(start_input))
	{ // Check if we input a file
		cout << "FEN file \"" + start_input + "\" opened, importing FEN." << endl;
		ifstream fen_file;
		string fen_input;
		fen_file.open(start_input);
		getline(fen_file, fen_input);
		current_board = board::GenerateBoard(fen_input);
	}
	else
	{ // No file, or doesn't exist
		current_board = board::GenerateBoard("");
	}

	cout << endl;
	board::PrintBoardFull(current_board);
	cout << endl;

	// Set both move functions here for 2P, then change one to engine if needed
	auto white_move = move::PlayerMove;
	auto black_move = move::PlayerMove;

	// Check vs. engine or 2 player
	cout << "Would you like to play vs. the engine (1) or a 2-player game (2)?" << endl;

	while (cin)
	{
		int play_mode;
		cin >> play_mode;
		if (play_mode == 1)
		{ // vs. engine
			cout << "Starting engine game..." << endl;
			cout << "Which color would you like to play: w(hite), b(lack), r(andom)?" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string player_color;
			while (cin)
			{
				cin >> player_color;
				if (regex_match(player_color, regex("[Ww](?:[Hh](?:[Ii](?:[Tt](?:[Ee])?)?)?)?")))
				{
					cout << endl
						 << "Player is white, engine is black." << endl;
					black_move = move::EngineMove;
					break;
				}
				else if (regex_match(player_color, regex("[Bb](?:[Ll](?:[Aa](?:[Cc](?:[Kk])?)?)?)?")))
				{
					cout << endl
						 << "Engine is white, player is black." << endl;
					white_move = move::EngineMove;
					break;
				}
				else if (regex_match(player_color, regex("[Rr](?:[Aa](?:[Nn](?:[Dd](?:[Oo](?:[Mm])?)?)?)?)?")))
				{
					srand(time(0));
					if (rand() / double(RAND_MAX) < 0.5)
					{ // Player is white
						cout << endl
							 << "Player is white, engine is black." << endl;
						black_move = move::EngineMove;
					}
					else
					{ // Player is black
						cout << endl
							 << "Player is black, engine is white." << endl;
						white_move = move::EngineMove;
					}
					break;
				}
				else
				{
					cout << "Invalid option!  Please choose a color to play: w(hite), b(lack), r(andom)?" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			break;
		}
		else if (play_mode == 2)
		{ // 2-player
			cout << "Starting 2-player game..." << endl;
			break;
		}
		else
		{
			cout << "Invalid option!  Please choose to play vs. the engine (1) or a 2-player game (2)." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	clrscr();
	// Main game loop
	while (current_board.checkmate == 2)
	{
		if (current_board.color == 0)
		{ // White move
			current_board = white_move(current_board);
		}
		else if (current_board.color == 1)
		{ // Black move
			current_board = black_move(current_board);
		}
	}

	// Now game should be over (with mate or resign)
	if (current_board.checkmate == 0)
	{
		cout << "*** White wins! ***" << endl
			 << endl;
	}
	else if (current_board.checkmate == 1)
	{
		cout << "*** Black wins! ***" << endl
			 << endl;
	}
	cout << "Final position:" << endl
		 << endl;
	board::PrintBoard(current_board);

	return 0;
} // end main
