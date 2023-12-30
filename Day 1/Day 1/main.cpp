#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int wordValue(string word);
int findSecondDigit(string line);
int day1_part1(string fileName);
int day1_part2(string fileName);

int main1() {
	string calibrationDocumentName = "input.txt";
	//ifstream calibrationDocument(calibrationDocumentName);
	cout << "Calibration Value (Part 1): " << day1_part1(calibrationDocumentName) << endl;
	cout << "Calibration Value (Part 2): " << day1_part2(calibrationDocumentName);

	//calibrationDocument.close();
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
		//cout << line << " Length: " << line.length() << " i: " << i << " substring: " << endPortion << endl;
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

int day1_part1(string fileName) {
	ifstream calibrationDocument(fileName);
	string line;
	int answer = 0;
	int firstDigit;
	int secondDigit;
	bool firstDigitFound = false;
	bool secondDigitFound = false;
	int calibrationValue = 0;

	while (!calibrationDocument.eof()) {

		getline(calibrationDocument, line);
		firstDigitFound = false;
		secondDigitFound = false;
		firstDigit = 0;
		secondDigit = 0;
		calibrationValue = 0;

		for (auto ch : line) {
			if (isdigit(ch) && !firstDigitFound) {
				firstDigitFound = true;
				firstDigit = static_cast<int>(ch - '0');

			}
			else if (isdigit(ch) && firstDigitFound) {
				secondDigitFound = true;
				secondDigit = static_cast<int>(ch - '0');
			}
		}

		if (!secondDigitFound) {
			secondDigit = firstDigit;
		}

		calibrationValue = 10 * firstDigit + secondDigit;

		answer += calibrationValue;
		cout << line << " " << calibrationValue << " " << answer << endl;
	}
	calibrationDocument.close();
	return answer;
}

int day1_part2(string fileName) {
	ifstream calibrationDocument(fileName);
	string line;
	string numbersAlpha[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string numbersDecimal[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	int calibrationTotal = 0;
	int lineValue;
	int firstDigit;
	int secondDigit;
	bool firstDigitFound = false;
	bool secondDigitFound = false;
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

	calibrationDocument.close();
	return calibrationTotal;
	
}