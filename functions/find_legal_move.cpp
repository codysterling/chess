ChessMove FindLegalMove(ChessBoard current_board, string piece, int start_rank, int start_file, int end_rank, int end_file)
{
	// Here we see if there is a piece of some type that can reach the end rank/file from possible start rank/file
	// We may know starting rank/file to decide which piece to use if there are multiple which can reach
	// Returns: ChessMove, either legal or with illegal positions depending on what's found (to be checked in ParseInput)

	vector<ChessMove> moves_list;
	ChessMove temp_move;
	temp_move = {{start_rank, start_file}, {end_rank, end_file}};

	string move_color, take_color;
	if (current_board.color == 0)
	{
		move_color = "w";
		take_color = "b";
	}
	else
	{
		move_color = "b";
		take_color = "w";
	}
	string target_piece = move_color.append(piece);

	// Search over board for appropriate piece
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (current_board.squares[i][j] == target_piece)
			{ // Find right piece
				vector<ChessMove> piece_moves = GetPossibleMoves(current_board, i, j);
				moves_list.insert(moves_list.end(), piece_moves.begin(), piece_moves.end());
			}
		}
	}

	// Search maater move list to remove moves that cause check
	vector<ChessMove> moves_list2;
	ChessBoard temp_board;
	for (ChessMove m : moves_list)
	{
		temp_board = MakeMove(current_board, m);
		temp_board.color = (temp_board.color + 1) % 2;
		int check = CheckCheck(temp_board);
		if (check == 0)
		{
			moves_list2.push_back(m);
		}
	}

	// Checking if move matches the known information about rank/file
	vector<ChessMove> final_move;
	for (ChessMove m : moves_list2)
	{
		if ((start_rank == 8 || start_rank == m.start[0]) && (start_file == 8 || start_file == m.start[1]) && end_rank == m.end[0] && end_file == m.end[1])
		{
			final_move.push_back(m);
		}
	}

	// If only 1 move matched, return it
	if (final_move.size() == 1)
	{
		temp_move = final_move[0];
	}
	else
	{ // Else return illegal move to prompt new input
		temp_move = {{8, 8}, {8, 8}};
	}

	return temp_move;

} // end function