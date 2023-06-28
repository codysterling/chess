void PrintBoard(ChessBoard current_board) {
	string white_bkg = "\033[48;5;222m";
	string black_bkg = "\033[48;5;178m";
	string white_text = "\033[38;5;15m";
	string black_text = "\033[38;5;16m";
	string white_clear = "\033[38;5;222m";
	string black_clear = "\033[38;5;178m";
	string clr = "\033[0m";
	string bkg, text;

	map<char,string> p_uni = {
		{'P', u8"\u265F"},
		{'N', u8"\u265E"},
		{'B', u8"\u265D"},
		{'R', u8"\u265C"},
		{'Q', u8"\u265B"},
		{'K', u8"\u265A"},
		{' ', u8"\u265F"}
	};

	// if (current_board.color == 0) { // printing from White PoV
		for (int i=0; i<8; i++) {
			cout << 8-i << " ";
			for (int j=0; j<8; j++) {
				// Set background color 
				if ((i+j)%2 == 0) {
					bkg = white_bkg;
					text = white_clear;
				} else {
					bkg = black_bkg;
					text = black_clear;
				}
				// Set text color
				if (current_board.squares[i][j][0] == 'w') {
					text = white_text;
				} else if (current_board.squares[i][j][0] == 'b') {
					text = black_text;
				}
				// cout << text << bkg << " " << p_uni[current_board.squares[i][j][1]] << " " << clr;
				cout << text << bkg << " " << current_board.squares[i][j][1] << " " << clr;
			}
			cout << endl;
		}
		cout << "   a  b  c  d  e  f  g  h" << endl;
	// } else { // printing from Black PoV
	// 	for (int i=7; i>=0; i--) {
	// 		cout << 8-i << " ";
	// 		for (int j=7; j>=0; j--) {
	// 			// Set background color 
	// 			if ((i+j)%2 == 0) {
	// 				bkg = white_bkg;
	// 				text = white_clear;
	// 			} else {
	// 				bkg = black_bkg;
	// 				text = black_clear;
	// 			}
	// 			// Set text color
	// 			if (current_board.squares[i][j][0] == 'w') {
	// 				text = white_text;
	// 			} else if (current_board.squares[i][j][0] == 'b') {
	// 				text = black_text;
	// 			}
	// 			// cout << text << bkg << " " << p_uni[current_board.squares[i][j][1]] << " " << clr;
	// 			cout << text << bkg << " " << current_board.squares[i][j][1] << " " << clr;
	// 		}
	// 		cout << endl;
	// 	}
	// 	cout << "   h  g  f  e  d  c  b  a" << endl;
	// }

	cout << endl;
} // end function

void PrintBoardFull(ChessBoard current_board) {
	PrintBoard(current_board);
	
	cout << "Color: " << current_board.color << endl;
	cout << "Check: " << current_board.check << endl;
	cout << "Checkmate: " << current_board.checkmate << endl;
	cout << "Enpassant: " << current_board.en_passant[0] << "," << current_board.en_passant[1] << endl;
	cout << "White castle: " << current_board.white_castle << endl;
	cout << "Black castle: " << current_board.black_castle << endl;
} // end function
