#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <map>

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
idArr findPossibleGames(gameArr allGames, int maxRed, int maxGreen, int maxBlue);
game newAnalyze(string round, game tracker);

int main() {
	int maxRed = 12;
	int maxGreen = 13;
	int maxBlue = 14;

	gameArr results = readData("input.txt");
	idArr possibleGames = findPossibleGames(results, maxRed, maxGreen, maxBlue);

	int idSum = 0;
	cout << "Valid Games:" << endl;
	for (auto id: possibleGames.ids) {
		if (id > 0) {
			cout << "\tID: " << results.games[id - 1].id << " Reds: " << results.games[id - 1].red << " Greens: " << results.games[id - 1].green << " Blues: " << results.games[id - 1].blue << endl;
			idSum += id;
		}
	}
	cout << endl;
	cout << "Valid ID Total: " << idSum << endl;
	return 0;

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
			inputData.games[gameIndex] = newAnalyze(round, inputData.games[gameIndex]);
		}
		round = line; // the last section lacks a semicolor

		gameIndex++;
		idCount++;
	}
	return inputData;
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

game newAnalyze(string round, game tracker) {
	// determines if this draw has any values greater than the current max and reports back the max so far
	string blockCountStrings[3] = { "", "", "" };
	int value;
	int index = 0;

	map<string, int*> trackers;
	trackers["red"] = &tracker.red;
	trackers["green"] = &tracker.green;
	trackers["blue"] = &tracker.blue;

	while (round.find(',') != string::npos) {
		blockCountStrings[index] = round.substr(0, round.find(','));
		index++;
		round = round.substr(round.find(',') + 2);
	}
	blockCountStrings[2] = round;

	for (string blockCountStr : blockCountStrings) {
		value = 0;
		for (auto pair : trackers) {
			string color = pair.first;
			if (blockCountStr.find(color) != string::npos) {
				string numberStr = blockCountStr.substr(0, blockCountStr.find(color) - 1);
				if (numberStr.length() == 1) {
					value = static_cast<int>(numberStr[0] - '0');
				}
				else if (numberStr.length() == 2) {
					value = static_cast<int>(numberStr[0] - '0') * 10;
					value += static_cast<int>(numberStr[1] - '0');
				}
				if (value > *trackers[color]) {
					*trackers[color] = value;
				}
			}
		}
	}
	return tracker;
}