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
	int ids[100] {};
};

gameArr readData(string fileName);
game analyzeGame(string round, game tracker);
idArr findPossibleGames(gameArr allGames, int maxRed, int maxGreen, int maxBlue);

int main() {
	int maxRed = 12;
	int maxGreen = 13;
	int maxBlue = 14;

	gameArr results = readData("input.txt");
	idArr possibleGames = findPossibleGames(results, maxRed, maxGreen, maxBlue);

	int idSum = 0;
	for (auto id: possibleGames.ids) {
		if (id > 0) {
			cout << "ID: " << results.games[id - 1].id << " Reds: " << results.games[id - 1].red << " Greens: " << results.games[id - 1].green << " Blues: " << results.games[id - 1].green << endl;
			idSum += id;
		}
	}
	cout << endl;
	cout << "Valid ID Total: " << idSum;

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

idArr findPossibleGames(gameArr allGames, int maxRed, int maxGreen, int maxBlue) {
	idArr possibleGames;
	int index = 0;
	for (game gameData : allGames.games) {
		if (gameData.red <= maxRed && gameData.green <= maxGreen && gameData.blue <= maxBlue) {
			possibleGames.ids[index] = gameData.id;
			index++;
		}
	}
	return possibleGames;
}