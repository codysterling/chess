namespace board
{

	int CheckCheck(ChessBoard current_board)
	{
		// Checks if the current_board position is in check for color whose move it is
		// Basically look at all off-color moves and see if any end at the square the current color king is on

		int king_square[2];
		vector<move::ChessMove> move_list;
		vector<move::ChessMove> sq_moves;

		char take_color;
		string color;
		if (current_board.color == 0)
		{
			take_color = 'b';
			color = "wK";
		}
		else
		{
			take_color = 'w';
			color = "bK";
		}

		// Running over board to get king square and possible moves of other color
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (current_board.squares[i][j] == color)
				{ // Checking king square
					king_square[0] = i;
					king_square[1] = j;
					// cout << "king at: " << i << "," << j << endl;
				}
				else if (current_board.squares[i][j][0] == take_color)
				{ // Else found a possible move square
					sq_moves = move::GetPossibleMoves(current_board, i, j);
					move_list.insert(move_list.end(), sq_moves.begin(), sq_moves.end());
				}
			}
		}

		// Seeing if any move ends on the king's square
		for (move::ChessMove m : move_list)
		{
			if (m.end[0] == king_square[0] && m.end[1] == king_square[1])
			{
				return 1;
			}
		}

		return 0;
	}

}