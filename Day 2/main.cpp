#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

struct game {
	int id = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
};

struct gameArr {
	game games[100];
};

struct idArr {
	int ids[100];
};

gameArr readData(string fileName);
game analyzeGame(string round, game tracker);


int main() {
	readData("input.txt");
} 

gameArr readData(string fileName) {
	gameArr inputData;
	string line;
	string round;
	int gameN = 0;


	ifstream file(fileName);
	assert(file.good());

	int counter = 1;
	while (!file.eof()) {
		getline(file, line);
		cout << line << endl;
		inputData.games[gameN].id = counter;

		line = line.substr(line.find(':') + 2);
		while (line.find(';') != string::npos) {
			round = line.substr(0, line.find(';'));
			line = line.substr(line.find(';') + 2);
			inputData.games[gameN] = analyzeGame(round, inputData.games[gameN]);
		}
		round = line; // the last section lacks a semicolor
		inputData.games[gameN] = analyzeGame(round, inputData.games[gameN]);
	}
	return inputData;
}

game analyzeGame(string round, game tracker) {
	if (round.find("red") != string::npos) {
		tracker.red += static_cast<int>(round.substr(round.find("red") - 2, round.find("red") - 1)[0] - '0');
	}
	if (round.find("green") != string::npos) {
		tracker.green += static_cast<int>(round.substr(round.find("green") - 2, round.find("green") - 1)[0] - '0');
	}
	if (round.find("blue") != string::npos) {
		tracker.blue += static_cast<int>(round.substr(round.find("blue") - 2, round.find("blue") - 1)[0] - '0');
	}
	return tracker;
}
