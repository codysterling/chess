namespace move {

	// struct ChessMove { // Chess move with start/end locations
	// 	// We start out of bounds so we can catch with parser
	// 	int start[2] = {8, 8};
	// 	int end[2] = {8, 8};
	// };

	ChessMove ParseMove(board::ChessBoard current_board, string given_move) {
		// Parse given human-readable move (in various formats) to ChessMove struct with .start/.end locations

		ChessMove parsed_move; // Failure, ask for new move
		parsed_move.start[0] = 6;
		parsed_move.start[1] = 0;
		parsed_move.end[0] = 5;
		parsed_move.end[1] = 0;

		return parsed_move;
	} // end function

	board::ChessBoard PlayerMove(board::ChessBoard current_board) { // This is the main player move function

		cout << "player move test" << endl;
		ChessMove parsed_move;

		while (cin) {
			string read_move;
			cin >> read_move;
			parsed_move = ParseMove(current_board, read_move);
			cout << parsed_move.start[0];
			if (parsed_move.start[0] == 8 || parsed_move.start[1] == 8 || parsed_move.end[0] == 8 || parsed_move.end[1] == 8) { // Parser returns bad move
				cout << "You have entered an illegal or unclear move.  Please enter a new one." << endl;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} else { // Otherwise good move, break to do move
				cout << "Good move!" << endl;
				break;
			}
		}

		current_board = board::MakeMove(current_board, parsed_move);
		board::PrintBoardFull(current_board);
		return current_board;
	} // end function

} // end namespace