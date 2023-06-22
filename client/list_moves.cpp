namespace move {

	void ListMoves(board::ChessBoard current_board, vector<ChessMove> move_list) {
		for (int i = 0; i < move_list.size(); i++) {
			ChessMove t_move = move_list[i];
			int start_rank = t_move.start[0];
			int start_file = t_move.start[1];
			string piece;
			if (current_board.squares[start_rank][start_file].substr(1,1) != "P") {
				piece = current_board.squares[start_rank][start_file].substr(1,1);
			}
			int end_rank = t_move.end[0];
			int end_file = t_move.end[1];

			cout << i+1 << ": " << piece << board::IntToFile(start_file) << 8-start_rank << " -> " << piece << board::IntToFile(end_file) << 8-end_rank << endl;
		}
	}

} // end namespace