namespace move {

	board::ChessBoard PlayerMove(board::ChessBoard current_board) { // This is the main player move function

		clrscr();
		cout << "Current board is:" << endl;
		board::PrintBoardFull(current_board);
		ChessMove parsed_move;

		if (current_board.color == current_board.check) {
			cout << "* You are in check! *" << endl;
		}

		if (current_board.color == 0) {
			cout << "Player is white";
		} else {
			cout << "Player is black";
		}
		cout << ", please enter move:" << endl;
		
		while (cin) {
			string read_move;
			cin >> read_move;
			parsed_move = ParseInput(current_board, read_move);
			// cout << parsed_move.start[0];
			if (parsed_move.start[0] == 8 || parsed_move.start[1] == 8 || parsed_move.end[0] == 8 || parsed_move.end[1] == 8) { // Parser returns bad move
				cout << "You have entered an illegal or unclear move.  Please enter a new one." << endl;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} else { // Otherwise good move, break to do move
				break;
			}
		}

		current_board = board::MakeMove(current_board, parsed_move);
		return current_board;
	} // end function

} // end namespace