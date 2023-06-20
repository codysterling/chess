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
	}; // end struct

	int FileToInt(string rank) {
		if (rank == "a") {
			return 0;
		} else if (rank == "b") {
			return 1;
		} else if (rank == "c") {
			return 2;
		} else if (rank == "d") {
			return 3;
		} else if (rank == "e") {
			return 4;
		} else if (rank == "f") {
			return 5;
		} else if (rank == "g") {
			return 6;
		} else if (rank == "h") {
			return 7;
		} else {
			cout << "Illegal rank given, something is broken with FileToInt!" << endl;
			return 8;
		}
	}

	string IntToFile(int rank) {
		if (rank == 0) {
			return "a";
		} else if (rank == 1) {
			return "b";
		} else if (rank == 2) {
			return "c";
		} else if (rank == 3) {
			return "d";
		} else if (rank == 4) {
			return "e";
		} else if (rank == 5) {
			return "f";
		} else if (rank == 6) {
			return "g";
		} else if (rank == 7) {
			return "h";
		} else {
			cout << "Illegal rank given, something is broken with IntToFile!" << endl;
			return "x";
		}
	}

	void PrintMove(ChessMove p_move) {
		cout << "Move: " << IntToFile(p_move.start[1]) << 8-p_move.start[0] << " to " << IntToFile(p_move.end[1]) << 8-p_move.end[0] << endl;
	}

} // end namespace