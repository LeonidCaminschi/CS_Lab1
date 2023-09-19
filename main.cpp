#include <iostream>
#include <vector>
#include <map>

using namespace std;

string caesarCipher(const string& text, int shift, char mode, const vector<char>& alphabet) {
    string result;

    for (char c : text) {
        if (isalpha(c)) {
            int index;
            for (int i = 0; i <= alphabet.size(); i++) {
                if (alphabet[i] == tolower(c)) {
                   index = i;
                   break;
                }
            }
            char shifted = alphabet[(index + (mode == 'e' ? shift : -shift)) % alphabet.size()];
            result += toupper(shifted);
        } else {
            result += c;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) {
        cout << "Please input 3 arguments" << endl;
        cout << "./lab1 <method> <number> \"<input_text>\"" << endl;
        cout << "method> - is 'e' for encryption and 'd' for decryption" << endl;
        cout << "<number> - is the number of alphabet movement ranged from 1-25" << endl;
        cout << "\"<input_text>\" must be a text could include spaces and any other English alphabet letters" << endl;
        cout << "\"<key2>\" optional used to make the initial alphabet more random using caesarsCipher advanced" << endl;
        return 1;
    }

    char method = argv[1][0];
    int shift = atoi(argv[2]);
    string inputText = argv[3];
    string key2;

    if (argc == 5) {
        key2 = argv[4];
    }

    if (method != 'e' && method != 'd') {
        cout << "Invalid argument. Please check your method to be 'd' or 'e'." << endl;
        return 1;
    }

    if (shift < 1 || shift > 25) {
        cout << "Invalid arguments. Please check the number to be in range of 1-25" << endl;
        return 1;
    }

    vector<char> alphabet;
    for (char c = 'a'; c <= 'z'; c++) {
        alphabet.push_back(c);
    }

    if (argc == 5) {
        if (key2.size() < 7) {
            cout << "Please input a new <key2> and for it not to be less than 7 characters" << endl;
            return 1;
        }

        vector<char> tobereplaced;

        for (char c : key2) {
            if (std::find(tobereplaced.begin(), tobereplaced.end(), c) == tobereplaced.end()) {
                tobereplaced.emplace_back(c);
            }
        }

        for (char c : alphabet) {
            if (std::find(tobereplaced.begin(), tobereplaced.end(), c) == tobereplaced.end()) {
                tobereplaced.emplace_back(c);
            }
        }

        alphabet = tobereplaced;
    }

    cout << "Current used alphabet:" << endl;
    for (char c : alphabet) {
        cout << c << " ";
    }
    cout << endl;

    string result;

    if (method == 'e') {
        result = caesarCipher(inputText, shift, 'e', alphabet);
        cout << "Encrypted text: " << result << endl;
    } else {
        result = caesarCipher(inputText, shift, 'd', alphabet);
        cout << "Decrypted text: " << result << endl;
    }

    return 0;
}
