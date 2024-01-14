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
idArr findPossibleGames(gameArr allGames, int maxRed, int maxGreen, int maxBlue);
game newAnalyze(string round, game tracker);

int main() {
	int maxRed = 12;
	int maxGreen = 13;
	int maxBlue = 14;

	gameArr results = readData("input.txt");
	idArr possibleGames = findPossibleGames(results, maxRed, maxGreen, maxBlue);

	int idSum = 0;
	for (auto id: possibleGames.ids) {
		if (id > 0) {
			cout << "ID: " << results.games[id - 1].id << " Reds: " << results.games[id - 1].red << " Greens: " << results.games[id - 1].green << " Blues: " << results.games[id - 1].blue << endl;
			idSum += id;
		}
	}
	cout << endl;
	cout << "Valid ID Total: " << idSum;
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

		cout << line << endl;

		line = line.substr(line.find(':') + 2);
		while (line.find(';') != string::npos) {
			round = line.substr(0, line.find(';'));
			line = line.substr(line.find(';') + 2);
			inputData.games[gameIndex] = newAnalyze(round, inputData.games[gameIndex]);
		}
		round = line; // the last section lacks a semicolor
		inputData.games[gameIndex] = newAnalyze(round, inputData.games[gameIndex]);
		cout << "\tRed: " << inputData.games[gameIndex].red << endl;
		cout << "\tGreen: " << inputData.games[gameIndex].green << endl;
		cout << "\tBlue: " << inputData.games[gameIndex].blue << endl;

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
	string colors[3] = { "", "", "" };
	int value;
	int index = 0;
	while (round.find(',') != string::npos) {
		colors[index] = round.substr(0, round.find(','));
		index++;
		round = round.substr(round.find(',') + 2);
	}
	colors[2] = round;

	for (string color : colors) {
		value = 0;
		if (color.find("red") != string::npos) {
			color = color.substr(0, color.find("red") - 1);
			if (color.length() == 1) {
				value = static_cast<int>(color[0] - '0');
				if (value > tracker.red) {
					tracker.red = value;
				}
			}
			else if (color.length() == 2) {
				value = static_cast<int>(color[0] - '0') * 10;
				value += static_cast<int>(color[1] - '0');
				if (value > tracker.red) {
					tracker.red = value;
				}
			}
			else {
				cout << "Error. Round analyse generated a final string that is too long." << endl;
			}
		}
		if (color.find("green") != string::npos) {
			color = color.substr(0, color.find("green") - 1);
			if (color.length() == 1) {
				value = static_cast<int>(color[0] - '0');
				if (value > tracker.green) {
					tracker.green = value;
				}
			}
			else if (color.length() == 2) {
				value = static_cast<int>(color[0] - '0') * 10;
				value += static_cast<int>(color[1] - '0');
				if (value > tracker.green) {
					tracker.green = value;
				}
			}
			else {
				cout << "Error. Round analyse generated a final string that is too long." << endl;
			}
		}
		if (color.find("blue") != string::npos) {
			color = color.substr(0, color.find("blue") - 1);
			if (color.length() == 1) {
				value = static_cast<int>(color[0] - '0');
				if (value > tracker.blue) {
					tracker.blue = value;
				}
			}
			else if (color.length() == 2) {
				value = static_cast<int>(color[0] - '0') * 10;
				value += static_cast<int>(color[1] - '0');
				if (value > tracker.blue) {
					tracker.blue = value;
				}
			}
			else {
				cout << "Error. Round analyse generated a final string that is too long." << endl;
			}
		}
	}
	return tracker;
}