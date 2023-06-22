namespace board {
	
	int FileToInt(string rank) {
		if (rank == "a") {
			return 0;
		} else if (rank == "b") {
			return 1;
		} else if (rank == "c") {
			return 2;
		} else if (rank == "d") {
			return 3;
		} else if (rank == "e") {
			return 4;
		} else if (rank == "f") {
			return 5;
		} else if (rank == "g") {
			return 6;
		} else if (rank == "h") {
			return 7;
		} else {
			cout << "Illegal rank given, something is broken with FileToInt!" << endl;
			return 8;
		}
	}

	string IntToFile(int rank) {
		if (rank == 0) {
			return "a";
		} else if (rank == 1) {
			return "b";
		} else if (rank == 2) {
			return "c";
		} else if (rank == 3) {
			return "d";
		} else if (rank == 4) {
			return "e";
		} else if (rank == 5) {
			return "f";
		} else if (rank == 6) {
			return "g";
		} else if (rank == 7) {
			return "h";
		} else {
			cout << "Illegal rank given, something is broken with IntToFile!" << endl;
			return "x";
		}
	}

} // end namespace