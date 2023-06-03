namespace board {

	void PrintBoard(ChessBoard current_board) {
		for (int i=0; i<8; i++) {
			for (int j=0; j<8; j++) {
				cout << "[" << current_board.square[i][j] << "] ";
			}
			cout << endl;
		}
	}
}