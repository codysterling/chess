#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>

using namespace std;

// Include other functions
#include "client/generate_board.cpp"
#include "client/print_board.cpp"

// Run program
int main() {
	// Display welcome message
	cout << "Welcome to Chess++!" << endl;
	cout << "Press Enter for a new game, otherwise input a path to a FEN file or the FEN sequence here." << endl;
	string start_input;
	getline(cin, start_input);
	// start_input = "fen.txt"; // faster testing of FEN input, remove later

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
	} else { // No regex match, so use starting board
		cout << "Starting a new game:" << endl;
		start_input = "";
	}
	cout << endl;
	board::ChessBoard current_board = board::GenerateBoard(start_input);
	board::PrintBoard(current_board);
	cout << endl;

	// Prompt for player color
	cout << "Which color would you like to play? [w(hite),b(lack),r(andom)]" << endl;
	string player_color;
	getline(cin, player_color);

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
