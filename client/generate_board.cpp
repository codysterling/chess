namespace board {

	struct ChessBoard { // Default board is a new board
		string square[8][8] = {
			{"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
			{"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
			{"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
			{"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}
		};
	};

	ChessBoard GenerateBoard(string fen_seq) {

		ChessBoard start_board;

		if (fen_seq.empty()) { // Blank input: return new board
			return start_board;
		} else { // (Probably legal) FEN sequence: turn into board
			int rank = 0;
			int file = 0;
			for (int i=0; i<fen_seq.length(); i++) {
				auto fen_char = fen_seq[i];

				if (fen_char == '/') {
					rank += 1;
					file = 0;
				} else if (isdigit(fen_char)) {
					fen_char -= '0';
					for (int i=file; i<file+fen_char; i++) {
						start_board.square[rank][i] = "  ";
					}
					file += fen_char;
				} else if (fen_char == toupper(fen_char)) {
					start_board.square[rank][file][0] = 'w';
					start_board.square[rank][file][1] = toupper(fen_char);
					file += 1;
				} else if (fen_char == tolower(fen_char)) {
					start_board.square[rank][file][0] = 'b';
					start_board.square[rank][file][1] = toupper(fen_char);
					file += 1;
				}
				
			}
			return start_board;
		}

	} // end function

} // end namespace
