#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int wordValue(string word);
int singleLineValue(string line);
int findSecondDigit(string line);

int day1_part1(string fileName ) {
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

int day1_part2_2(string fileName) {
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

		secondDigit = 10;
		size_t lastDigitIndex = 0;
		bool numberFound = true;
		string searchPortion = line;
		//cout << line << endl;
		while (numberFound) {
			numberFound = false;
			//cout << "\tSecond Digit: " << secondDigit << "\tLast Digit Index: " << lastDigitIndex << endl;
			searchPortion = line.substr(lastDigitIndex);
			for (string number : numbersAlpha) {
				//cout << "\tSearch Portion: " << searchPortion << " Looking for: " << number << endl;
				if (searchPortion.find(number) != string::npos) {
					secondDigit = wordValue(number);
					lastDigitIndex += searchPortion.find(number) + number.length();
					searchPortion = line.substr(lastDigitIndex);
					numberFound = true;
					/*cout << "\t\t Number Found" << endl;*/
				} 
			}
			//cout << endl;
			for (string number : numbersDecimal) {
				//cout << "\tSearch Portion: " << searchPortion << " Looking for: " << number << endl;
				if (searchPortion.find(number) != string::npos) {
					secondDigit = static_cast<int>(number[0] - '0');
					lastDigitIndex += searchPortion.find(number) + number.length();
					searchPortion = line.substr(lastDigitIndex);
					numberFound = true;
					/*cout << "\t\t Number Found" << endl;*/
				}
			}
			//cout << endl << numberFound << endl;
			//cin >> blank;
		}
		//cout << "Final Second Digit: " << secondDigit << endl;
		//cin >> blank;
		//cout << line << " " << firstDigit * 10 + secondDigit << endl;
		lineValue = firstDigit * 10 + secondDigit;
		calibrationTotal += lineValue;
	}
	
	return calibrationTotal;
}

int day1_part2_attempt2(string fileName) {
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
		//cout << line << endl;
		secondDigit = findSecondDigit(line);
		//cout << "\tsecond digit found" << endl;
		//cout << line << " " << firstDigit * 10 + secondDigit << endl;
		lineValue = firstDigit * 10 + secondDigit;
		calibrationTotal += lineValue;
	}

	return calibrationTotal;
}

int main() {
	
	//cout << day1_part1("input.txt");
	
	//int calibrationValue = findSecondDigit("fivecgtwotwo3oneighth");
	int calibrationValue = day1_part2_attempt2("input.txt");
	cout << "Calibration Value (New): " << calibrationValue << endl;
	calibrationValue = day1_part2_2("input.txt");
	cout << "Calibration Value (Old): " << calibrationValue;
	
	return 0;
}

int singleLineValue(string line) {
	string numbersAlpha[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string numbersDecimal[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	int calibrationTotal = 0;
	int calibrationValue;
	int firstDigit;
	int secondDigit;
	bool firstDigitFound = false;
	bool secondDigitFound = false;


	int startIndex = 0;
	string blank;
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
	secondDigit = 10;
	size_t lastDigitIndex = 0;
	bool numberFound = true;
	string searchPortion = line;

	while (numberFound) {
		numberFound = false;
		searchPortion = line.substr(lastDigitIndex);
		for (string number : numbersAlpha) {
			if (searchPortion.find(number) != string::npos) {
				secondDigit = wordValue(number);
				lastDigitIndex += searchPortion.find(number) + number.length();
				searchPortion = line.substr(lastDigitIndex);
				numberFound = true;
			}
		}
		for (string number : numbersDecimal) {
			if (searchPortion.find(number) != string::npos) {
				secondDigit = static_cast<int>(number[0] - '0');
				lastDigitIndex += searchPortion.find(number) + number.length();
				searchPortion = line.substr(lastDigitIndex);
				numberFound = true;
			}
		}
	}
	calibrationValue = firstDigit * 10 + secondDigit;
	return calibrationValue;
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