namespace move {

	ChessMove ParseInput(board::ChessBoard current_board, string player_input) {
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
		if (regex_match(player_input,regex("[a-hx1-8].*=[BNRQ]"))) {
			promotion = player_input[player_input.length()-1];
			player_input = player_input.substr(0,player_input.length()-2);
		}

		// There are not many possible legal input structures, so we can iterate them all manually to make parsing easier
		if (regex_match(player_input,regex("[0Oo](?:-?)[0Oo](?:-?)[0Oo]"))) { // Queen-side castling
			start_file = 4;
			end_file = 2;
			piece = "K";
			if (current_board.color == 0) { // For white
				start_rank = 7;
				end_rank = 7;
			} else if (current_board.color == 1) { // For black
				start_rank = 0;
				end_rank = 0;
			}
		} else if (regex_match(player_input,regex("[0Oo](?:-?)[0Oo]"))) { // King-side castling
			start_file = 4;
			end_file = 6;
			piece = "K";
			if (current_board.color == 0) { // For white
				start_rank = 7;
				end_rank = 7;
			} else if (current_board.color == 1) { // For black
				start_rank = 0;
				end_rank = 0;
			}
		} else if (regex_match(player_input,regex("[BKNQR][a-h][1-8](?:x?)[a-h][1-8]"))) { // Most explicit way, not used often
			piece = player_input.substr(0,1);
			start_rank = 8 - stoi(player_input.substr(2,1));
			start_file = board::FileToInt(player_input.substr(1,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = board::FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[BKNQR][a-h](?:x?)[a-h][1-8]"))) { // Provide starting file
			piece = player_input.substr(0,1);
			start_file = board::FileToInt(player_input.substr(1,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = board::FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[BKNQR][1-9](?:x?)[a-h][1-8]"))) { // Provide starting rank
			piece = player_input.substr(0,1);
			start_rank = 8 - stoi(player_input.substr(1,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = board::FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[BKNQR](?:x?)[a-h][1-8]"))) { // Normal move (Na3, Qd4, etc.)
			piece = player_input.substr(0,1);
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = board::FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[a-h](?:[1-8]?)x[a-h][1-8]"))) { // Pawn taking (dxe4)
			piece = "P";
			start_file = board::FileToInt(player_input.substr(0,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = board::FileToInt(player_input.substr(player_input.length()-2,1));
			start_rank = end_rank + 1 - 2*current_board.color;
		} else if (regex_match(player_input,regex("[a-h][1-8]"))) { // Either pawn move, or return possible moves
			int rank = 8 - stoi(player_input.substr(1,1));
			int file = board::FileToInt(player_input.substr(0,1));
			if (current_board.squares[rank][file] == "  ") { // If end square is empty, do pawn move
				piece = "P";
				end_rank = rank;
				end_file = file;
				start_file = file;
			} else { // Square isn't empty
				if ((current_board.color == 0 && current_board.squares[rank][file][0] == 'w') || (current_board.color == 1 && current_board.squares[rank][file][0] == 'b')) { // Return possible moves if it's your color
					vector<ChessMove> move_vec;
					move_vec = GetPossibleMoves(current_board,rank,file);
					cout << "Legal moves:" << endl;
					ListMoves(current_board, move_vec);

					// After printing moves, ask for new move:
					cout << "Please enter move number, final square, or normal algebraic move: ";
					string read_input;
					cin >> read_input;
					try { // If int, read from vector list and return listed move
						int n = stoi(read_input);
						if (n > 0 && n <= move_vec.size()) {
							return move_vec[stoi(read_input)-1];
						}
					} catch (logic_error &e) { // If not int, should be string of final square
						if (regex_match(read_input,regex("[a-h][1-8]"))) {
							int read_file = board::FileToInt(read_input.substr(0,1));
							int read_rank = 8 - stoi(read_input.substr(1,1));
							ChessMove read_move;
							read_move = {{rank,file},{read_rank,read_file}};
							
	 						if (find(move_vec.begin(), move_vec.end(), read_move) != move_vec.end()) { // See if that move is in the list
								return read_move;
							} else {
								// Otherwise fail to below
							}
						}
						// If not final square, assume it's some other move and try to parse (which might itself fail)
						ChessMove t_move = ParseInput(current_board,read_input);
						return t_move;
					}					
				} else {
					// Square occupied with wrong color
				}
			}
		} else {
			// No match with regex, illegal move
		}
		parsed_move = PieceReach(current_board, piece, start_rank, start_file, end_rank, end_file);

		// Adding promotion to move
		string promstr;
		promstr += promotion;
		if (regex_match(promstr,regex("[BNRQ]"))) {
			parsed_move.promotion = promotion;
		}
/*
		input: Na4
		a2

		char[0] == N
		figure out that our knights are at C3 (2,4) and G1 (0,6)
		big_move_func(2,4) + big_move_func(0,6) => [[2,4] => [0,3],...]
		now we check that list for a4 final position (0,3)
		-- write function to check if there is a knight that can reach a4 (basically inverse of above function)
		*/

		//// remove later
		// parsed_move.start[0] = 6;
		// parsed_move.start[1] = 0;
		// parsed_move.end[0] = 5;
		// parsed_move.end[1] = 0;

		return parsed_move;
	} // end function

} // end namespace