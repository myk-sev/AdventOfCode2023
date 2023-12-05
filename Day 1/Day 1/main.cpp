#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main() {
	ifstream calibrationDocument("input.txt");

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

	cout << answer;
	return 0;
}