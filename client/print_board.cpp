namespace board {

	void PrintBoard(ChessBoard current_board) {
		for (int i=0; i<8; i++) {
			for (int j=0; j<8; j++) {
				cout << "[" << current_board.squares[i][j] << "] ";
			}
			cout << endl;
		}
		cout << endl;
	} // end function

	void PrintBoardFull(ChessBoard current_board) {
		for (int i=0; i<8; i++) {
			for (int j=0; j<8; j++) {
				cout << "[" << current_board.squares[i][j] << "] ";
			}
			cout << endl;
		}
		cout << endl;
		
		cout << "Color: " << current_board.color << endl;
		cout << "Check: " << current_board.check << endl;
		cout << "Checkmate: " << current_board.checkmate << endl;
		cout << "Enpassant: " << current_board.en_passant[0] << "," << current_board.en_passant[1] << endl;
		cout << "White castle: " << current_board.white_castle << endl;
		cout << "Black castle: " << current_board.black_castle << endl;
	} // end function

} // end namespace