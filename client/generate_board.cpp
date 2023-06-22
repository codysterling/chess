#include <regex>

namespace board {

	ChessBoard GenerateBoard(string fen_seq) {
		ChessBoard start_board;

		regex fen_regex_pos = regex("^(([BKNPQRbknpqr1-8]+/){7}[BKNPQRbknpqr1-8]+).*$");
		regex fen_regex_full = regex("^(([BKNPQRbknpqr1-8]+/){7}[BKNPQRbknpqr1-8]+)? ([wb])? ([KQkq]{1,4}|-)? (([a-h][1-8])|-).*");
		smatch m;

		if (regex_match(fen_seq,m,fen_regex_full)) { // Match full FEN regex
			cout << "Board state imported from FEN:" << endl;
			fen_seq = m.str(1);
			// Importing color
			if (m.str(3) == "w") {
				start_board.color = 0;
			} else if (m.str(3) == "b") {
				start_board.color = 1;
			}
			// Importing castling
			if (m.str(4).find("K") == string::npos) {
				start_board.white_castle -= 2;
			}
			if (m.str(4).find("Q") == string::npos) {
				start_board.white_castle -= 1;
			}
			if (m.str(4).find("k") == string::npos) {
				start_board.black_castle -= 2;
			}
			if (m.str(4).find("q") == string::npos) {
				start_board.black_castle -= 1;
			}
			// Importing en passant
			if (regex_match(m.str(5),regex("[a-h][1-8]"))) {
				int file = board::FileToInt(m.str(5).substr(0,1));
				int rank = 8-stoi(m.str(5).substr(1,1));
				start_board.en_passant[0] = rank;
				start_board.en_passant[1] = file;
			}
		} else if (regex_match(fen_seq,m,fen_regex_pos)) { // Match pos FEN regex
			cout << "Board position imported from FEN:" << endl;
			fen_seq = m[1];
		} else { // No regex match for position, return normal starting board
			cout << "Starting a new game:" << endl;
			return start_board;
		}

		// Parsing FEN position
		int rank = 0;
		int file = 0;
		char fen_char;
		for (int i=0; i<fen_seq.length(); i++) {
			fen_char = fen_seq[i];

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
				start_board.squares[rank][file][0] = 'w';
				start_board.squares[rank][file][1] = toupper(fen_char);
				file += 1;
			} else if (fen_char == tolower(fen_char)) {
				start_board.squares[rank][file][0] = 'b';
				start_board.squares[rank][file][1] = toupper(fen_char);
				file += 1;
			} else if (fen_char == ' ') {
				break;
			}
		}

		// Basic castling checks from FEN position, in case not in FEN import
		if (start_board.squares[7][4] != "wK") {
			start_board.white_castle = 0;
		} else {
			if (start_board.squares[7][0] != "wR") {
				start_board.white_castle = floor(start_board.white_castle/2)*2;
			}
			if (start_board.squares[7][7] != "wR") {
				start_board.white_castle = start_board.white_castle%2;
			}
		}
		if (start_board.squares[0][4] != "bK") {
			start_board.black_castle = 0;
		} else {
			if (start_board.squares[0][0] != "bR") {
				start_board.black_castle = floor(start_board.black_castle/2)*2;
			}
			if (start_board.squares[0][7] != "bR") {
				start_board.black_castle = start_board.black_castle%2;
			}
		}

		return start_board;
	} // end function

} // end namespace
