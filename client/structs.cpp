void clrscr() { // Hacky way to clear terminal
	// From: https://stackoverflow.com/questions/17335816/clear-screen-using-c
	cout << "\033[2J\033[1;1H";
}

namespace board {

	struct ChessBoard { // Default board is a new board
		string squares[8][8] = {
			{"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
			{"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
			{"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}
		};
		bool color = 0; // current move color: 0 = white, 1 = black
		int check = 2; // 0 = white in check, 1 = black in check, 2 = no check
		int checkmate = 2; // 0 = white has mate, 1 = black has mate, 2 = no mate
		int en_passant[2] = {8, 8}; // store row/column of where en passant can happen
		int white_castle = 3; // Q-side: 1, K-side: 2, both: 3, neither: 0
		int black_castle = 3; // Q-side: 1, K-side: 2, both: 3, neither: 0
	}; // end struct

} // end namespace

namespace move {

	struct ChessMove { // Chess move with start/end locations
		// We start out of bounds so we can catch with parser
		int start[2] = {8, 8};
		int end[2] = {8, 8};
		char promotion;
	}; // end struct

	inline bool operator==(const ChessMove& lhs, const ChessMove& rhs) {
		return lhs.start[0] == rhs.start[0] && lhs.start[1] == rhs.start[1] && lhs.end[0] == rhs.end[0] && lhs.end[1] == rhs.end[1];
	}

} // end namespace