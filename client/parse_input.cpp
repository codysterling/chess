namespace move {

	ChessMove ParseInput(board::ChessBoard current_board, string player_input) {
		/*
		Parse given human-readable move (in various formats) to ChessMove struct with .start/.end locations
		Accepts two types of input:
			- Normal chess notation (e4, Na3, ...), in which case we return the move to execute
			- Provide a square with a piece (e.g. a2, b2, ...), in which case we provide the possible moves
			  //// *(not implemented yet, more complicated than first thought)*
		*/

		ChessMove parsed_move; // Initialize the move that we return later

		// regex r_piece = regex("[BKNPQR]");
		// regex r_square = regex("[a-h][1-8]");
		// regex r_normal = regex("[BKNQR][a-h][1-8]");

		string piece = "";
		int start_rank = 8;
		int start_file = 8;
		int end_rank = 8;
		int end_file = 8;

		// There are not many possible legal input structures, so we can iterate them all manually to make parsing easier
		if (regex_match(player_input,regex("[0Oo](?:-?)[0Oo](?:-?)[0Oo]"))) { // Queen-side castling
			start_file = 4;
			end_file = 2;
			if (current_board.color == 0) { // For white
				piece = "wK";
				start_rank = 7;
				end_rank = 7;
			} else if (current_board.color == 1) { // For black
				piece = "bK";
				start_rank = 0;
				end_rank = 0;
			}
		} else if (regex_match(player_input,regex("[0Oo](?:-?)[0Oo]"))) { // King-side castling
			start_file = 4;
			end_file = 6;
			if (current_board.color == 0) { // For white
				piece = "wK";
				start_rank = 7;
				end_rank = 7;
			} else if (current_board.color == 1) { // For black
				piece = "bK";
				start_rank = 0;
				end_rank = 0;
			}
		} else if (regex_match(player_input,regex("[BKNQR][a-h][1-8](?:x?)[a-h][1-8]"))) { // Most explicit way, not used often
			cout << "matched big regex" << endl;
			piece = player_input.substr(0,1);
			start_rank = 8 - stoi(player_input.substr(2,1));
			start_file = FileToInt(player_input.substr(1,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[BKNQR][a-h](?:x?)[a-h][1-8]"))) { // Provide starting file
			cout << "matched file regex" << endl;
			piece = player_input.substr(0,1);
			start_file = FileToInt(player_input.substr(1,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[BKNQR][1-9](?:x?)[a-h][1-8]"))) { // Provide starting rank
			cout << "matched rank regex" << endl;
			piece = player_input.substr(0,1);
			start_rank = 8 - stoi(player_input.substr(1,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[BKNQR](?:x?)[a-h][1-8]"))) { // Normal move (Na3, Qd4, etc.)
			cout << "matched piece move" << endl;
			piece = player_input.substr(0,1);
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = FileToInt(player_input.substr(player_input.length()-2,1));
		} else if (regex_match(player_input,regex("[a-h]x[a-h][1-8]"))) { // Pawn taking (dxe4)
			cout << "matched pawn taking" << endl;
			piece = "P";
			start_file = FileToInt(player_input.substr(0,1));
			end_rank = 8 - stoi(player_input.substr(player_input.length()-1,1));
			end_file = FileToInt(player_input.substr(player_input.length()-2,1));
			start_rank = end_rank + 1 - 2*current_board.color;
		} else if (regex_match(player_input,regex("[a-h][1-8]"))) { // Either pawn move, or return possible moves
			cout << "matched square" << endl;
			int rank = 8 - stoi(player_input.substr(1,1));
			int file = FileToInt(player_input.substr(0,1));
			cout << "coords: " << rank << "," << file << endl;
			if (current_board.squares[rank][file] == "  ") { // If end square is empty, do pawn move
				cout << "End cxsquare is empty, doing pawn move";
				piece = "P";
				end_rank = rank;
				end_file = file;
			} else { // Square isn't empty
				if ((current_board.color == 0 && current_board.squares[rank][file][0] == 'w') || (current_board.color == 1 && current_board.squares[rank][file][0] == 'b')) { // Return possible moves if it's your color
					cout << "occupied with color, get moves" << endl;
					//// Manually adding a move_vec list to test
					vector<ChessMove> move_vec;
					ChessMove m1 = {{6,1},{5,2}};
					ChessMove m2 = {{7,4},{7,6}};
					ChessMove m3 = {{6,2},{5,1}};
					move_vec.push_back(m1);
					move_vec.push_back(m2);
					move_vec.push_back(m3);
					cout << "mvec: ";
					PrintMove(move_vec[1]);
					ListMoves(current_board, move_vec);
					// move_vec = get_moves(current_board,rank,file);

					// After printing moves, ask for new move:
					cout << "Please enter move number, final square, or normal algebraic move: ";
					string read_input;
					cin >> read_input;
					cout << "input is: " << read_input << endl;
					try { // If int, read from vector list and return listed move
						int n = stoi(read_input);
						cout << "have int" << endl;
						if (n > 0 && n <= move_vec.size()) {
							return move_vec[stoi(read_input)-1];
						}
					} catch (logic_error &e) { // If not int, should be string of final square
						cout << "not int" << endl;
						if (regex_match(read_input,regex("[a-h][1-8]"))) {
							int read_file = FileToInt(read_input.substr(0,1));
							int read_rank = 8 - stoi(read_input.substr(1,1));
							ChessMove read_move;
							read_move = {{rank,file},{read_rank,read_file}};
							
	 						if (find(move_vec.begin(), move_vec.end(), read_move) != move_vec.end()) { // See if that move is in the list
								cout << "move in list" << endl;
								return read_move;
							} else { // Otherwise fail to below
								cout << "not in list" << endl;
							}
						}
						// If not final square, assume it's some other move and try to parse (which might itself fail)
						cout << "now here" << endl;
						ChessMove t_move = ParseInput(current_board,read_input);
						return t_move;
					}					
				} else { // Square occupied with wrong color
					cout << "occupied wrong" << endl;
				}
			}
		} else { // No match with regex, illegal move
			cout << "No match with regex, illegal move." << endl;
		}
		cout << "Coords: " << start_rank << "," << start_file << " to: " << end_rank << "," << end_file << endl;
		parsed_move = PieceReach(current_board, piece, start_rank, start_file, end_rank, end_file);

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