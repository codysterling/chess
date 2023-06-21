namespace move {

	move::ChessMove PieceReach(board::ChessBoard current_board, string piece, int start_rank, int start_file, int end_rank, int end_file) {
		// Here we work backwards to see if there is a piece of some type that can reach the given rank/file
		// We may know starting rank/file to decide which piece to use if there are multiple which can reach
		// Returns: ChessMove, either legal or with illegal positions depending on what's found (to be checked in ParseInput)

		move::ChessMove temp_move;

		char move_color;
		char take_color;
		if (current_board.color == 0) {
			move_color = 'w';
			take_color = 'b';
		} else {
			move_color = 'b';
			take_color = 'w';
		}

		// Castling is its own logic, so we check it here

		temp_move = {{start_rank,start_file},{end_rank,end_file}};

		// First check to make sure square isn't occupied by own color
		char current_square_color = current_board.squares[end_rank][end_file][0];
		cout << "Current square is: " << current_square_color << endl;
		if (current_square_color == move_color) {
			cout << "Square " << IntToFile(end_file) << 8-end_rank << " is already occupied with your own color!" << endl;
			return temp_move;
		}

		int n_pieces_can_reach = 0;
		if (piece == "P") {
			if (current_square_color == take_color) { // searching for diagonal moves
				if (move_color == 'w') {
					cout << "here with white" << endl;
				}
			}
		}

		// temp_move.start[0] = 6;
		// temp_move.start[1] = 4;
		// temp_move.end[0] = end_rank;
		// temp_move.end[1] = end_file;
		return temp_move;

	} // end function

	vector<int[2]> GetPossibleMoves(board::ChessBoard current_board, int rank, int file) {
		// For a square at rank/file on the board current_board, return a vector list of possible final positions

		vector<int[2]> moves_list;

		return moves_list;
	}

} // end namespace