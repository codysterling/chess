vector<ChessMove> GetPossibleMoves(ChessBoard current_board, int rank, int file) {
	// For a square at rank/file on the board current_board, return a vector list of possible final moves

	vector<ChessMove> moves_list;
	ChessMove temp_move = {{rank,file},{8,8}};

	char color = current_board.squares[rank][file][0];
	char take_color;
	if (color == 'w') {
		take_color = 'b';
	} else if (color == 'b') {
		take_color = 'w';
	}
	string piece = current_board.squares[rank][file].substr(1,1);

	// First get all moves without considering check, then remove some moves later if needed
	if (piece == "P") { // Pawn moves
		int pawn_dir;
		if (color == 'w') {
			pawn_dir = -1;
		} else if (color == 'b') {
			pawn_dir = 1;
		}
		// Normal pawn move
		if (current_board.squares[rank+pawn_dir][file] == "  ") {
			temp_move.end[0] = rank+pawn_dir;
			temp_move.end[1] = file;
			moves_list.push_back(temp_move);
		}
		// Double moves
		if (color == 'w' && rank == 6 && current_board.squares[5][file] == "  " && current_board.squares[4][file] == "  ") {
			temp_move.end[0] = 4;
			temp_move.end[1] = file;
			moves_list.push_back(temp_move);
		} else if (color == 'b' && rank == 1 && current_board.squares[2][file] == "  " && current_board.squares[3][file] == "  ") {
			temp_move.end[0] = 3;
			temp_move.end[1] = file;
			moves_list.push_back(temp_move);
		}
		// If taking is possible
		if (file-1 >= 0 && (current_board.squares[rank+pawn_dir][file-1][0] == take_color || (current_board.en_passant[0] == rank+pawn_dir && current_board.en_passant[1] == file-1))) {
			temp_move.end[0] = rank+pawn_dir;
			temp_move.end[1] = file-1;
			moves_list.push_back(temp_move);
		}
		if (file+1 <= 7 && (current_board.squares[rank+pawn_dir][file+1][0] == take_color || (current_board.en_passant[0] == rank+pawn_dir && current_board.en_passant[1] == file+1))) {
			temp_move.end[0] = rank+pawn_dir;
			temp_move.end[1] = file+1;
			moves_list.push_back(temp_move);
		}

	} else if (piece == "N") { // Knight moves
		// Vector of 8 possible knight moves
		// {rank change, file change}
		vector<vector<int>> n_moves = {
			{2,1},
			{2,-1},
			{-2,1},
			{-2,-1},
			{1,2},
			{1,-2},
			{-1,2},
			{-1,-2}
		};
		for (int i=0; i < n_moves.size(); i++) {
			int end_rank = rank+n_moves[i][0];
			int end_file = file+n_moves[i][1];
			if (end_rank >= 0 && end_rank < 8 && end_file >= 0 && end_file < 8) { // Move is in bounds
				if (current_board.squares[end_rank][end_file] == "  " || current_board.squares[end_rank][end_file][1] == take_color) {
					temp_move.end[0] = end_rank;
					temp_move.end[1] = end_file;
					moves_list.push_back(temp_move);
				}
			}
		}

	} else if (piece == "B") { // Bishop moves
		// Vector of bishop diagonal directions
		// {rank change, file change}
		vector<vector<int>> b_moves = {
			{1,1},
			{1,-1},
			{-1,1},
			{-1,-1}
		};
		for (vector<int> dir : b_moves) {
			for (int i=1; i<8; i++) {
				int end_rank = rank + dir[0]*i;
				int end_file = file + dir[1]*i;
				if (end_rank >= 0 && end_rank < 8 && end_file >= 0 && end_file < 8) { // Move is in bounds
					if (current_board.squares[end_rank][end_file] == "  ") {
						temp_move.end[0] = end_rank;
						temp_move.end[1] = end_file;
						moves_list.push_back(temp_move);
					} else { // Piece there, takeable or not?
						if (current_board.squares[end_rank][end_file][0] == take_color) { // Takeable piece, add to list
							temp_move.end[0] = end_rank;
							temp_move.end[1] = end_file;
							moves_list.push_back(temp_move);
						}
						break; // Break, after adding or skipping if own color
					}
				}
			}
		}

	} else if (piece == "R") { // Rook moves
		// Vector of rook directions
		// {rank change, file change}
		vector<vector<int>> r_moves = {
			{0,1},
			{0,-1},
			{1,0},
			{-1,0}
		};
		for (vector<int> dir : r_moves) {
			for (int i=1; i<8; i++) {
				int end_rank = rank + dir[0]*i;
				int end_file = file + dir[1]*i;
				if (end_rank >= 0 && end_rank < 8 && end_file >= 0 && end_file < 8) { // Move is in bounds
					if (current_board.squares[end_rank][end_file] == "  ") {
						temp_move.end[0] = end_rank;
						temp_move.end[1] = end_file;
						moves_list.push_back(temp_move);
					} else { // Piece there, takeable or not?
						if (current_board.squares[end_rank][end_file][0] == take_color) { // Takeable piece, add to list
							temp_move.end[0] = end_rank;
							temp_move.end[1] = end_file;
							moves_list.push_back(temp_move);
						}
						break; // Break, after adding or skipping if own color
					}
				}
			}
		}

	} else if (piece == "Q") { // Queen moves
		// Vector of queen directions (bishop + rook)
		// {rank change, file change}
		vector<vector<int>> q_moves = {
			{1,1},
			{1,-1},
			{-1,1},
			{-1,-1},
			{0,1},
			{0,-1},
			{1,0},
			{-1,0}
		};
		for (vector<int> dir : q_moves) {
			for (int i=1; i<8; i++) {
				int end_rank = rank + dir[0]*i;
				int end_file = file + dir[1]*i;
				if (end_rank >= 0 && end_rank < 8 && end_file >= 0 && end_file < 8) { // Move is in bounds
					if (current_board.squares[end_rank][end_file] == "  ") {
						temp_move.end[0] = end_rank;
						temp_move.end[1] = end_file;
						moves_list.push_back(temp_move);
					} else { // Piece there, takeable or not?
						if (current_board.squares[end_rank][end_file][0] == take_color) { // Takeable piece, add to list
							temp_move.end[0] = end_rank;
							temp_move.end[1] = end_file;
							moves_list.push_back(temp_move);
						}
						break; // Break, after adding or skipping if own color
					}
				}
			}
		}

	} else if (piece == "K") { // King moves
		// Check castling
		int c_rank, c_num;
		if (color == 'w') {
			c_rank = 7;
			c_num = current_board.white_castle;
		} else if (color == 'b') {
			c_rank = 0;
			c_num = current_board.black_castle;
		}
		if (rank == c_rank && file == 4) { // King at starting square
			// Queen-side
			if ((c_num == 3 || c_num == 1) && current_board.squares[c_rank][1] == "  " && current_board.squares[c_rank][2] == "  " && current_board.squares[c_rank][3] == "  ") {
				temp_move.end[0] = c_rank;
				temp_move.end[1] = 2;
				moves_list.push_back(temp_move);
			}
			// King-side
			if ((c_num == 3 || c_num == 2) && current_board.squares[c_rank][5] == "  " && current_board.squares[c_rank][6] == "  ") {
				temp_move.end[0] = c_rank;
				temp_move.end[1] = 6;
				moves_list.push_back(temp_move);
			}
		}
		// Normal king moves
		vector<vector<int>> k_moves = {
			{0,1},
			{0,-1},
			{1,0},
			{-1,0},
			{1,1},
			{1,-1},
			{-1,1},
			{-1,-1}
		};
		for (int i=0; i < k_moves.size(); i++) {
			int end_rank = rank+k_moves[i][0];
			int end_file = file+k_moves[i][1];
			if (end_rank >= 0 && end_rank < 8 && end_file >= 0 && end_file < 8) { // Move is in bounds
				if (current_board.squares[end_rank][end_file] == "  " || current_board.squares[end_rank][end_file][1] == take_color) {
					temp_move.end[0] = end_rank;
					temp_move.end[1] = end_file;
					moves_list.push_back(temp_move);
				}
			}
		}
	}

	return moves_list;
}