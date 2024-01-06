#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

struct game {
	int red;
	int green;
	int blue;
};

struct gameArr {
	game games[100];
};

gameArr readData(string fileName);

game analyzeGame(string round, game tracker);

gameArr findPossibleGames(gameArr allGames, int redTotal, int greenTotal, int blueTotal);

int main() {
	//string line = "Game 1: 3 red, 2 green, 1 blue; 1 red, 1 green, 1 blue; 3 blue, 3 red, 3 green; 1 blue, 3 green, 7 red; 5 red, 3 green, 1 blue";
	//line = line.substr(line.find(':') + 2);
	//cout << "Uncut: " << line << endl << endl << endl;
	//string round;
	//game data;
	//data.red = 0;
	//data.blue = 0;
	//data.green = 0;
	//while (line.find(';') != string::npos) {
	//	round = line.substr(0, line.find(';'));
	//	cout << "Round: " << round << endl;
	//	line = line.substr(line.find(';') + 2);
	//	cout << "Post Cut: " << line << endl;

	//	cout << "Red: " << line.find("red")  << endl;
	//	cout << "Blue: " << line.find("blue") << endl;
	//	cout << "Green: " << line.find("green") << endl;
	//	cout << endl;

	//	data.red += static_cast<int>(round.substr(round.find("red") - 2, round.find("red") - 1)[0] - '0');
	//	data.blue += static_cast<int>(round.substr(round.find("blue") - 2, round.find("blue") - 1)[0] - '0');
	//	data.green += static_cast<int>(round.substr(round.find("green") - 2, round.find("green") - 1)[0] - '0');

	//	cout << "Red Total: " << data.red << endl;
	//	cout << "Green Total: " << data.green << endl;
	//	cout << "Blue Total: " << data.blue << endl;
	//	cout << endl;
	//}
	readData("input.txt");

} 

gameArr readData(string fileName) {
	gameArr inputData;
	string line;
	string round;
	int gameN = 0;


	ifstream file(fileName);
	assert(file.good());

	while (!file.eof()) {
		getline(file, line);
		cout << line << endl;
		inputData.games[gameN].red = 0;
		inputData.games[gameN].blue = 0;
		inputData.games[gameN].green = 0;

		line = line.substr(line.find(':') + 2);
		while (line.find(';') != string::npos) {
			round = line.substr(0, line.find(';'));
			line = line.substr(line.find(';') + 2);
			inputData.games[gameN] = analyzeGame(round, inputData.games[gameN]);
		}
		round = line; // the last section lacks a semicolor
		inputData.games[gameN] = analyzeGame(round, inputData.games[gameN]);
		cout << "Red Total: " << inputData.games[gameN].red << endl;
		cout << "Green Total: " << inputData.games[gameN].green << endl;
		cout << "Blue Total: " << inputData.games[gameN].blue << endl;
		cout << endl;
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