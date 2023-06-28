ChessBoard EngineMove(ChessBoard current_board) { // This is the main engine move function

	cout << "eng move test" << endl;
	current_board.color = (current_board.color + 1)%2;
	return current_board;
} // end function