#include <regex>

namespace board {

	// struct ChessBoard { // Default board is a new board
	// 	string squares[8][8] = {
	// 		{"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
	// 		{"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
	// 		{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 		{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 		{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 		{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
	// 		{"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
	// 		{"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}
	// 	};
	// 	bool color = 0; // current move color: 0 = white, 1 = black
	// 	int check = 2; // 0 = white in check, 1 = black in check, 2 = no check
	// 	int checkmate = 2; // 0 = white has mate, 1 = black has mate, 2 = no mate
	// 	int en_passant[2]; // store row/column of where en passant can happen
	// 	int white_castle = 3; // Q-side: 1, K-side: 2, both: 3, neither: 0
	// 	int black_castle = 3; // Q-side: 1, K-side: 2, both: 3, neither: 0
	// }; // end struct

	ChessBoard GenerateBoard(string fen_seq) {
		ChessBoard start_board;

		if (fen_seq.empty()) { // Blank input: return new board
			return start_board;
		} else { // (Probably legal) FEN sequence: turn into board
			//// The '/' part breaks regex, probably parsing is bad overall, fix
			// regex tr = reginex("[BKNPQR]");
			// regex tr2 = regex("[bknpqr]");
			int rank = 0;
			int file = 0;
			for (int i=0; i<fen_seq.length(); i++) {
				char fen_char = fen_seq[i];
				// cout << "char is " << &fen_char << endl;

				if (fen_char == '/') {
					rank += 1;
					file = 0;
				} else if (isdigit(fen_char)) {
					fen_char -= '0'; // workaround for math stuff with char
					for (int i=file; i<file+fen_char; i++) {
						start_board.squares[rank][i] = "  ";
					}
					file += fen_char;
				} else if (fen_char == toupper(fen_char)) {
				// } else if (regex_match(&fen_char, tr)) {
					// cout << "char matched upper" << endl;
					start_board.squares[rank][file][0] = 'w';
					start_board.squares[rank][file][1] = toupper(fen_char);
					file += 1;
				} else if (fen_char == tolower(fen_char)) {
				// } else if (regex_match(&fen_char, tr2)) {
					// cout << "char matched lower" << endl;
					start_board.squares[rank][file][0] = 'b';
					start_board.squares[rank][file][1] = toupper(fen_char);
					file += 1;
				}
			}
			return start_board;
		}
	} // end function

	ChessBoard MakeMove(ChessBoard current_board, move::ChessMove given_move) {

		// Check castling move, assume that it's already been checked to be legal
		if (current_board.squares[given_move.start[0]][given_move.start[1]] == "wK" && given_move.start[0] == 7 && given_move.start[1] == 4 && (given_move.end[1] == 2 || given_move.end[1] == 0)) { // White Queen-side
			current_board.squares[7][4] = "  ";
			current_board.squares[7][0] = "  ";
			current_board.squares[7][2] = "wK";
			current_board.squares[7][3] = "wR";
			current_board.white_castle = 0;
		} else if (current_board.squares[given_move.start[0]][given_move.start[1]] == "wK" && given_move.start[0] == 7 && given_move.start[1] == 4 && (given_move.end[1] == 6 || given_move.end[1] == 7)) { // White King-side
			current_board.squares[7][4] = "  ";
			current_board.squares[7][7] = "  ";
			current_board.squares[7][6] = "wK";
			current_board.squares[7][5] = "wR";
			current_board.white_castle = 0;
		} else if (current_board.squares[given_move.start[0]][given_move.start[1]] == "bK" && given_move.start[0] == 0 && given_move.start[1] == 4 && (given_move.end[1] == 2 || given_move.end[1] == 0)) { // Black Queen-side
			current_board.squares[0][4] = "  ";
			current_board.squares[0][0] = "  ";
			current_board.squares[0][2] = "bK";
			current_board.squares[0][3] = "bR";
			current_board.black_castle = 0;
		} else if (current_board.squares[given_move.start[0]][given_move.start[1]] == "bK" && given_move.start[0] == 0 && given_move.start[1] == 4 && (given_move.end[1] == 6 || given_move.end[1] == 7)) { // Black King-side
			current_board.squares[0][4] = "  ";
			current_board.squares[0][7] = "  ";
			current_board.squares[0][6] = "bK";
			current_board.squares[0][5] = "bR";
			current_board.black_castle = 0;
		} else { // Not castling, so do normal move
			current_board.squares[given_move.end[0]][given_move.end[1]] = current_board.squares[given_move.start[0]][given_move.start[1]];
			current_board.squares[given_move.start[0]][given_move.start[1]] = "  ";
		}

		// Update color and return board
		current_board.color = (current_board.color + 1)%2;
		return(current_board);
	} // end function

} // end namespace
