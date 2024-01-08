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
idArr findPossibleGames(gameArr allGames, int redTotal, int greenTotal, int blueTotal);


int main() {
	gameArr results = readData("input.txt");
	for (auto round: results.games) {
		cout << round.id << ' ' << round.red << ' ' << round.blue << ' ' << round.green << endl;
	}

} 

gameArr readData(string fileName) {
	// reads all data into an array of composed of cube counts for each game
	gameArr inputData;
	string line;
	string round;


	ifstream file(fileName);
	assert(file.good());

	int idCount = 1;
	int gameIndex = 0;
	while (!file.eof()) {
		getline(file, line);
		cout << line << endl;
		inputData.games[gameIndex].id = idCount;

		line = line.substr(line.find(':') + 2);
		while (line.find(';') != string::npos) {
			round = line.substr(0, line.find(';'));
			line = line.substr(line.find(';') + 2);
			inputData.games[gameIndex] = analyzeGame(round, inputData.games[gameIndex]);
		}
		round = line; // the last section lacks a semicolor
		inputData.games[gameIndex] = analyzeGame(round, inputData.games[gameIndex]);

		gameIndex++;
		idCount++;
	}
	return inputData;
}

game analyzeGame(string round, game tracker) {
	//add the cube found from the current round to the cube count for the whole game
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

idArr findPossibleGames(gameArr allGames, int redTotal, int greenTotal, int blueTotal) {
	idArr possibleGames;
	int counter = 0;
	for (game round : allGames.games) {
		if (round.red <= redTotal && round.green < greenTotal && round.blue < blueTotal) {
			possibleGames.ids[counter] = round.id;
			counter++;
		}
	}
	return possibleGames;
}