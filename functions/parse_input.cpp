ChessMove ParseInput(ChessBoard current_board, string player_input)
{
	/*
	Parse given human-readable move (in various formats) to ChessMove struct with .start/.end locations
	Accepts two types of input:
		- Normal chess notation (e4, Na3, ...), in which case we return the move to execute
		- Provide a square with your color piece (e.g. a2, b2, ...), in which case we provide the possible moves
	*/

	ChessMove parsed_move; // Initialize the move that we return later

	string piece = "";
	int start_rank = 8;
	int start_file = 8;
	int end_rank = 8;
	int end_file = 8;
	char promotion;

	// Checking promotion
	if (regex_match(player_input, regex("[a-hx1-8].*=[BNRQ]")))
	{
		promotion = player_input[player_input.length() - 1];
		player_input = player_input.substr(0, player_input.length() - 2);
	}

	// There are not many possible legal input structures, so we can iterate them all manually to make parsing easier
	if (regex_match(player_input, regex("[0Oo](?:-?)[0Oo](?:-?)[0Oo]")))
	{ // Queen-side castling
		start_file = 4;
		end_file = 2;
		piece = "K";
		if (current_board.color == 0)
		{ // For white
			start_rank = 7;
			end_rank = 7;
		}
		else if (current_board.color == 1)
		{ // For black
			start_rank = 0;
			end_rank = 0;
		}
	}
	else if (regex_match(player_input, regex("[0Oo](?:-?)[0Oo]")))
	{ // King-side castling
		start_file = 4;
		end_file = 6;
		piece = "K";
		if (current_board.color == 0)
		{ // For white
			start_rank = 7;
			end_rank = 7;
		}
		else if (current_board.color == 1)
		{ // For black
			start_rank = 0;
			end_rank = 0;
		}
	}
	else if (regex_match(player_input, regex("[BKNQR][a-h][1-8](?:x?)[a-h][1-8]")))
	{ // Most explicit way, not used often
		piece = player_input.substr(0, 1);
		start_rank = 8 - stoi(player_input.substr(2, 1));
		start_file = FileToInt(player_input.substr(1, 1));
		end_rank = 8 - stoi(player_input.substr(player_input.length() - 1, 1));
		end_file = FileToInt(player_input.substr(player_input.length() - 2, 1));
	}
	else if (regex_match(player_input, regex("[BKNQR][a-h](?:x?)[a-h][1-8]")))
	{ // Provide starting file
		piece = player_input.substr(0, 1);
		start_file = FileToInt(player_input.substr(1, 1));
		end_rank = 8 - stoi(player_input.substr(player_input.length() - 1, 1));
		end_file = FileToInt(player_input.substr(player_input.length() - 2, 1));
	}
	else if (regex_match(player_input, regex("[BKNQR][1-9](?:x?)[a-h][1-8]")))
	{ // Provide starting rank
		piece = player_input.substr(0, 1);
		start_rank = 8 - stoi(player_input.substr(1, 1));
		end_rank = 8 - stoi(player_input.substr(player_input.length() - 1, 1));
		end_file = FileToInt(player_input.substr(player_input.length() - 2, 1));
	}
	else if (regex_match(player_input, regex("[BKNQR](?:x?)[a-h][1-8]")))
	{ // Normal move (Na3, Qd4, etc.)
		piece = player_input.substr(0, 1);
		end_rank = 8 - stoi(player_input.substr(player_input.length() - 1, 1));
		end_file = FileToInt(player_input.substr(player_input.length() - 2, 1));
	}
	else if (regex_match(player_input, regex("[a-h](?:[1-8]?)x[a-h][1-8]")))
	{ // Pawn taking (dxe4)
		piece = "P";
		start_file = FileToInt(player_input.substr(0, 1));
		end_rank = 8 - stoi(player_input.substr(player_input.length() - 1, 1));
		end_file = FileToInt(player_input.substr(player_input.length() - 2, 1));
		start_rank = end_rank + 1 - 2 * current_board.color;
	}
	else if (regex_match(player_input, regex("[a-h][1-8]")))
	{ // Either pawn move, or return possible moves
		int rank = 8 - stoi(player_input.substr(1, 1));
		int file = FileToInt(player_input.substr(0, 1));
		if (current_board.squares[rank][file] == "  ")
		{ // If end square is empty, do pawn move
			piece = "P";
			end_rank = rank;
			end_file = file;
			start_file = file;
		}
		else
		{ // Square isn't empty
			if ((current_board.color == 0 && current_board.squares[rank][file][0] == 'w') || (current_board.color == 1 && current_board.squares[rank][file][0] == 'b'))
			{ // Return possible moves if it's your color
				// Get possible moves (without considering check)
				vector<ChessMove> move_vec;
				move_vec = GetPossibleMoves(current_board, rank, file);
				// Filter those moves if they leave you in check
				vector<ChessMove> move_vec2;
				ChessBoard temp_board;
				for (ChessMove m : move_vec)
				{
					temp_board = MakeMove(current_board, m);
					temp_board.color = (temp_board.color + 1) % 2;
					int check = CheckCheck(temp_board);
					if (check == 0)
					{
						move_vec2.push_back(m);
					}
				}

				// If there are legal moves, print them
				if (move_vec2.size() != 0)
				{
					cout << "Legal moves:" << endl;
					ListMoves(current_board, move_vec2);
					cout << "Please enter move number, final square, or normal algebraic move: ";
					string read_input;
					cin >> read_input;
					try
					{ // If int, read from vector list and return listed move
						int n = stoi(read_input);
						if (n > 0 && n <= move_vec2.size())
						{
							return move_vec2[stoi(read_input) - 1];
						}
					}
					catch (logic_error &e)
					{ // If not int, should be string of final square
						if (regex_match(read_input, regex("[a-h][1-8]")))
						{
							int read_file = FileToInt(read_input.substr(0, 1));
							int read_rank = 8 - stoi(read_input.substr(1, 1));
							ChessMove read_move;
							read_move = {{rank, file}, {read_rank, read_file}};

							if (find(move_vec2.begin(), move_vec2.end(), read_move) != move_vec2.end())
							{ // See if that move is in the list
								return read_move;
							}
							else
							{
								// Otherwise fail to below
							}
						}
						// If not final square, assume it's some other move and try to parse (which might itself fail)
						ChessMove t_move = ParseInput(current_board, read_input);
						return t_move;
					}
				} else
				{
					cout << "This piece has no legal moves.  Please enter a new move or square:" << endl;
					string read_input;
					cin >> read_input;
					// Doing small internal recheck of move input if we get here
					ChessMove t_move = ParseInput(current_board, read_input);
					return t_move;
				}
			}
			else
			{
				// Square occupied with wrong color
			}
		}
	}
	else
	{
		// No match with regex, illegal move
	}
	parsed_move = FindLegalMove(current_board, piece, start_rank, start_file, end_rank, end_file);

	// Adding promotion to move
	string promstr;
	promstr += promotion;
	if (regex_match(promstr, regex("[BNRQ]")))
	{
		parsed_move.promotion = promotion;
	}

	return parsed_move;
} // end function