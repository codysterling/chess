namespace board {

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

			// Disabling castling if we're moving a rook or king
			if (current_board.squares[given_move.end[0]][given_move.end[1]][1] == 'R') { // Moving a rook
				if (given_move.start[0] == 7 && given_move.start[1] == 0) { // White Queen-side
					current_board.white_castle = floor(current_board.white_castle/2)*2;
				} else if (given_move.start[0] == 7 && given_move.start[1] == 7) { // White King-side
					current_board.white_castle = current_board.white_castle%2;
				} else if (given_move.start[0] == 0 && given_move.start[1] == 0) { // Black Queen-side
					current_board.black_castle = floor(current_board.black_castle/2)*2;
				} else if (given_move.start[0] == 0 && given_move.start[1] == 7) { // Black King-side
					current_board.black_castle = current_board.white_castle%2;
				}
			}
			if (current_board.squares[given_move.end[0]][given_move.end[1]] == "wK") { // Moving white king
				current_board.white_castle = 0;
			}
			if (current_board.squares[given_move.end[0]][given_move.end[1]] == "bK") { // Moving black king
				current_board.black_castle = 0;
			}

			// Checking if we did an en passant capture
			if (current_board.squares[given_move.end[0]][given_move.end[1]][1] == 'P' && given_move.end[0] == current_board.en_passant[0] && given_move.end[1] == current_board.en_passant[1]) {
				current_board.squares[given_move.end[0]+1-2*current_board.color][given_move.end[1]] = "  ";
			}

			// Disabling en passant after the move
			current_board.en_passant[0] = 8;
			current_board.en_passant[1] = 8;

			// Doing some pawn-specific checks
			if (current_board.squares[given_move.end[0]][given_move.end[1]][1] == 'P') { // First check if we moved a pawn
				// Turning back on en passant if we did a double pawn move
				if (given_move.start[0] == 6 && given_move.end[0] == 4) { // White double pawn move
					current_board.en_passant[0] = 5;
					current_board.en_passant[1] = given_move.start[1];
				} else if (given_move.start[0] == 1 && given_move.end[0] == 3) { // Black double pawn move
					current_board.en_passant[0] = 2;
					current_board.en_passant[1] = given_move.start[1];
				}

				// Pawn promotion
				if (given_move.end[0] == 0 || given_move.end[0] == 7) {
					if (given_move.promotion) {
						current_board.squares[given_move.end[0]][given_move.end[1]][1] = given_move.promotion;
					} else {
						string promotion;
						cout << "Enter a piece to promote pawn into: (k)N(ight), B(ishop), R(ook), Q(ueen)" << endl;
						while (cin) {
							cin >> promotion;
							if (regex_match(promotion, regex("(?:[Kk]?)[Nn](?:[Ii](?:[Gg](?:[Hh](?:[Tt]?)?)?)?)?"))) {
								current_board.squares[given_move.end[0]][given_move.end[1]][1] = 'N';
								break;
							} else if (regex_match(promotion, regex("[Bb](?:[Ii](?:[Ss](?:[Hh](?:[Oo](?:[Pp]?)?)?)?)?)?"))) {
								current_board.squares[given_move.end[0]][given_move.end[1]][1] = 'B';
								break;
							} else if (regex_match(promotion, regex("[Rr](?:[Oo](?:[Oo](?:[Kk]?)?)?)?"))) {
								current_board.squares[given_move.end[0]][given_move.end[1]][1] = 'R';
								break;
							} else if (regex_match(promotion, regex("[Qq](?:[Uu](?:[Ee](?:[Ee](?:[Nn]?)?)?)?)?"))) {
								current_board.squares[given_move.end[0]][given_move.end[1]][1] = 'Q';
								break;
							} else {
								cout << "Invalid piece, please enter a valid piece to promote to." << endl;
								cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
						}
					}
				}
			}
		}

		// Update color and return board
		current_board.color = (current_board.color + 1)%2;
		return(current_board);
	} // end function

} // end namespace