#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <random>
using namespace std;
map<char, char> generateRandomCipher() {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string shuffledAlphabet = alphabet;
    unsigned seed = static_cast<unsigned>(time(0));
    shuffle(shuffledAlphabet.begin(), shuffledAlphabet.end(), default_random_engine(seed));
    map<char, char> cipher;
    for (int i = 0; i < alphabet.size(); i++) 
        cipher[alphabet[i]] = shuffledAlphabet[i];
    return cipher;
}
void computeCharacterFrequency(const string& text, map<char, double>& frequency) {
    int length = text.size();
    for (char c : text)
        if (isalpha(c))
        {
            char lowercase = tolower(c);
            if (frequency.count(lowercase) > 0) 
                frequency[lowercase] += 1.0 / length;
            else 
                frequency[lowercase] = 1.0 / length;
        }
}
int main() {
    map<char, char> cipher = generateRandomCipher();
    // Table of mappings
    cout << "Letter Mappings Table:" << endl;
    cout << "Alphabet: ";
    for (char letter = 'a'; letter <= 'z'; letter++)
        cout << letter << ' ';
    cout << "\nKey     : ";
    for (char letter = 'a'; letter <= 'z'; letter++)
            cout << cipher[letter] << ' ';
    cout << "\n" << endl;

    ifstream input("plaintext.txt");
    if (!input.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }
    string plaintext;
    getline(input, plaintext);
    input.close();
    cout << "Plaintext: " << plaintext << "\n" << endl;
    ofstream output("ciphertext.txt");
    if (!output.is_open()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }
    string ciphertext;
    for (char c : plaintext)
    {
        if (isalpha(c))
        {
            char lowercase = tolower(c);
            if (cipher.count(lowercase) > 0) 
                if (isupper(c)) 
                    ciphertext += toupper(cipher[lowercase]);
                 else 
                    ciphertext += cipher[lowercase];
        } else 
            ciphertext += c;
    }
    output << ciphertext;
    output.close();
    cout << "Ciphertext: " << ciphertext << "\n" << endl;
    map<char, double> characterFrequency;
    computeCharacterFrequency(plaintext, characterFrequency);
    cout << "Frequency\tPlain text Character\tCipher text Character" << endl;

    for (char letter = 'a'; letter <= 'z'; letter++) {
        char lowercase = tolower(letter);
        if (characterFrequency.count(lowercase) > 0)
            cout << characterFrequency[lowercase] << "\t\t" << lowercase << "\t\t" << cipher[lowercase] << endl;
    }
    return 0;
}
