#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>
#include <vector>

using namespace std;

// Include other functions
//// The order in which these are loaded is important, hence the structs file first.  We should think about redoing/ordering or something
#include "client/structs.cpp"
#include "client/generate_board.cpp"
#include "client/print_board.cpp"
#include "client/find_moves.cpp"
#include "client/parse_input.cpp"
#include "client/player_move.cpp"
#include "engine/engine_move.cpp"

// void clrscr() { // Hacky way to clear terminal
// 	// From: https://stackoverflow.com/questions/17335816/clear-screen-using-c
// 	cout << "\033[2J\033[1;1H";
// }

// Run program
int main() {
	// Display welcome message
	cout << "Welcome to Chess++!" << endl;
	cout << "Press Enter for a new game, otherwise input a path to a FEN file or the FEN sequence here." << endl;
	string start_input;
	// getline(cin, start_input);
	start_input = "c_fen.txt"; //// faster testing of FEN input, remove later
	// start_input = ""; //// faster testing of blank input, remove later

	// Checking input to parse FEN
	// Right now only supports static board state, later add move/castle/etc.
	regex fen_seq_regex = regex("([BKNPQRbknpqr1-8]+/){7}[BKNPQRbknpqr1-8]+");

	if (filesystem::exists(start_input)) { // Check if we input a file
		cout << "FEN file \"" + start_input + "\" opened, importing FEN." << endl;
		ifstream fen_file (start_input);
		fen_file >> start_input;
	}

	if (regex_match(start_input, fen_seq_regex)) { // Regex match to import FEN
		cout << "Board state imported from FEN:" << endl;
	} else { // Broken or no FEN, so use starting board
		cout << "Starting a new game:" << endl;
		start_input = "";
	}
	cout << endl;
	board::ChessBoard current_board = board::GenerateBoard(start_input);
	board::PrintBoard(current_board);
	cout << endl;

	// Set both move functions here for 2P, then change one to engine if needed
	auto white_move = move::PlayerMove;
	auto black_move = move::PlayerMove;

	// Check vs. engine or 2 player
	cout << "Would you like to play vs. the engine (1) or a 2-player game (2)?" << endl;

	while (cin) {
		int play_mode;
		// cin >> play_mode;
		play_mode = 2;
		if (play_mode == 1) { // vs. engine
			cout << "Starting engine game..." << endl;
			cout << "Which color would you like to play: w(hite), b(lack), r(andom)?" << endl;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string player_color;
			while (cin) {
				cin >> player_color;
				if (regex_match(player_color, regex("[Ww](?:[Hh](?:[Ii](?:[Tt](?:[Ee])?)?)?)?"))) {
					cout << endl << "Player is white, engine is black." << endl;
					black_move = move::EngineMove;
					break;
				} else if (regex_match(player_color, regex("[Bb](?:[Ll](?:[Aa](?:[Cc](?:[Kk])?)?)?)?"))) {
					cout << endl << "Engine is white, player is black." << endl;
					white_move = move::EngineMove;
					break;
				} else if (regex_match(player_color, regex("[Rr](?:[Aa](?:[Nn](?:[Dd](?:[Oo](?:[Mm])?)?)?)?)?"))) {
					srand(time(0));
					if (rand()/double(RAND_MAX) < 0.5) { // Player is white
						cout << endl << "Player is white, engine is black." << endl;
						black_move = move::EngineMove;
					} else { // Player is black
						cout << endl << "Player is black, engine is white." << endl;
						white_move = move::EngineMove;
					}
					break;
				} else {
					cout << "Invalid option!  Please choose a color to play: w(hite), b(lack), r(andom)?" << endl;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			break;
		} else if (play_mode == 2) { // 2-player
			cout << "Starting 2-player game..." << endl;
			break;
		} else {
			cout << "Invalid option!  Please choose to play vs. the engine (1) or a 2-player game (2)." << endl;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	clrscr();
	// Main game loop
	while (current_board.checkmate == 2) {
		if (current_board.color == 0) { // White move
			current_board = white_move(current_board);
		} else if (current_board.color == 1) { // Black move
			current_board = black_move(current_board);
		}
	}

	// Now game should be over (with mate or resign)
	if (current_board.checkmate == 0) {
		cout << "*** White wins! ***" << endl << endl;
	} else if (current_board.checkmate == 1) {
		cout << "*** Black wins! ***" << endl << endl;
	}
	cout << "Final position:" << endl << endl;
	board::PrintBoard(current_board);

	return 0;
} // end main





/* Client pseudocode
// This could be through CLI, GUI, with Python somehow external if we want later?

// Generate starting board
func generate_starting_board() {
	// board = 8x8 array
	// fill in with pieces so it looks like:
	// ["bR","bN","bB",...]
	// ["bP","bP",...]
	// ["xx","xx",...]
	// ["xx","xx",...]
	// ["xx","xx",...]
	// ["xx","xx",...]
	// ["wP","wP",...]
	// ["wR","wN","wB",...]
	return board
}

// Decide if player is white, black, or random

// Iterate white/black moves
// After each move, update castling/en passant/check flags, check for checkmate to end game
// On player move, check if it's legal (with check_move() defined in engine code) then make it

func parse_player_move(board,move) {
	// Parse the player move in normal chess notation ("a3", "Nc3", ...) to something easier for us: [Pa2,Pa3], [Na1,Nc3]
	// If it's unclear (e.g. two knights can go to same location) then we need to exit this and reprompt the player for a more clear notation
	// Alternatively if we have a GUI we can just ignore this part I guess since the GUI handles start/ending location
}

func make_move(board,move) {
	// This just updates the board state with the given move, at this point it should have already been check for legality
	start_loc = move[0]
	moved_piece = board[start_loc]
	end_loc = move[1]

	board[start_loc] = "xx" // Blank square now
	board[end_loc] = moved_piece
	return board
}
*/
