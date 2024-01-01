#include <iostream>
#include <fstream>
#include <string>
#include <cassert>


using namespace std;

int wordValue(string word);
int findSecondDigit(string line);
int day1_part1(ifstream& fileName);
int day1_part2(ifstream& fileName);

int main() {
	string calibrationDocumentName = "input.txt";
	ifstream calibrationDocument(calibrationDocumentName);
	cout << "Calibration Value (Part 1): " << day1_part1(calibrationDocument) << endl;
	calibrationDocument.seekg(0, ios::beg);
	cout << "Calibration Value (Part 2): " << day1_part2(calibrationDocument);

	calibrationDocument.close();
	return 0;
}

int wordValue(string word) {
	string numbersAlpha[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	for (int i = 0; i < 10; i++) {
		if (word == numbersAlpha[i]) {
			return i;
		}
	}
}

int findSecondDigit(string line) {
	string numbersAlpha[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string numbersDecimal[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	string endPortion;

	for (int i = line.length() - 1; i >= 0; i--) {
		endPortion = line.substr(i);
		for (string number : numbersAlpha) {
			if (endPortion.find(number) != string::npos) {
				return wordValue(number);
			}
		}
		for (string number : numbersDecimal) {
			if (endPortion.find(number) != string::npos) {
				return static_cast<int>(number[0] - '0');
			}
		}
	}

}

int day1_part1(ifstream& calibrationDocument) {
	string line;
	int calibrationTotal = 0;
	int firstDigit;
	int secondDigit;
	int lineValue = 0;

	while (!calibrationDocument.eof()) {

		getline(calibrationDocument, line);
		firstDigit = 0;
		secondDigit = 0;

		for (int i = 0; i < line.length(); i++) {
			if (isdigit(line[i])) {
				firstDigit = static_cast<int>(line[i] - '0');
				break;
			}
		}
		for (int i = line.length() - 1; i>= 0; i--) {
			if (isdigit(line[i])) {
				secondDigit = static_cast<int>(line[i] - '0');
				break;
			}
		}
		assert(firstDigit != 0 && secondDigit != 0);
		lineValue = 10 * firstDigit + secondDigit;

		calibrationTotal += lineValue;
	}
	return calibrationTotal;
}

int day1_part2(ifstream& calibrationDocument) {
	string line;
	string numbersAlpha[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string numbersDecimal[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	int calibrationTotal = 0;
	int lineValue;
	int firstDigit;
	int secondDigit;
	size_t firstDigitIndex = 99;


	int startIndex = 0;

	string blank;
	while (!calibrationDocument.eof()) {
		getline(calibrationDocument, line);
		//retrieves value of first digit
		size_t firstDigitIndex = line.length();
		firstDigit = 10;
		for (auto number : numbersAlpha) {
			if (line.find(number) != string::npos) {
				if (line.find(number) < firstDigitIndex) {
					firstDigitIndex = line.find(number);
					firstDigit = wordValue(number);
				}
			}

		}
		for (auto number : numbersDecimal) {
			if (line.find(number) != string::npos) {
				if (line.find(number) < firstDigitIndex) {
					firstDigitIndex = line.find(number);
					firstDigit = static_cast<int>(number[0] - '0');
				}
			}

		}
		secondDigit = findSecondDigit(line);

		lineValue = firstDigit * 10 + secondDigit;
		calibrationTotal += lineValue;
	}

	return calibrationTotal;
	
}