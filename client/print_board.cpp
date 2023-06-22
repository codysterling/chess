namespace board {

	void PrintBoard(ChessBoard current_board) {
		if (current_board.color == 0) { // printing from White PoV
			for (int i=0; i<8; i++) {
				cout << 8-i << " ";
				for (int j=0; j<8; j++) {
					cout << "[" << current_board.squares[i][j] << "]";
				}
				cout << endl;
			}
			cout << "   a   b   c   d   e   f   g   h" << endl;
		} else { // printing from Black PoV
			for (int i=7; i>=0; i--) {
				cout << 8-i << " ";
				for (int j=7; j>=0; j--) {
					cout << "[" << current_board.squares[i][j] << "]";
				}
				cout << endl;
			}
			cout << "   h   g   f   e   d   c   b   a" << endl;
		}
		
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

} // end namespace