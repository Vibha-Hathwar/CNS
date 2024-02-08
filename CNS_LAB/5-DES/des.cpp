#include <bits/stdc++.h>
using namespace std;
string rotateSubKey(string s, int rot) 
{
    return s.substr(rot) + s.substr(0, rot);
}
string firstPermute(string input, int *permChoiceOne)
{
    string res = "";
    for (int i = 0; i < 56; i++)
        res += input[permChoiceOne[i] -1];
    return res;
}
string bin_to_hex(string binary)
{
    string res="";
    unordered_map<string,char>m;
        m["0000"]='0';
        m["0001"]='1';
        m["0010"]='2';
        m["0011"]='3';
        m["0100"]='4';
        m["0101"]='5';
        m["0110"]='6';
        m["0111"]='7';
        m["1000"]='8';
        m["1001"]='9';
        m["1010"]='A';
        m["1011"]='B';
        m["1100"]='C';
        m["1101"]='D';
        m["1110"]='E';
        m["1111"]='F';
    for(int i=0;i<binary.length();i+=4)
    {
        res+=m[binary.substr(i,4)];
    }
    return res;

    
}

/*string bin_to_hex(const string& binaryString) {
    
    unsigned long long int decimalValue = bitset<48>(binaryString).to_ullong();
    stringstream ss;
    ss << hex << decimalValue;
    return ss.str();
}*/
string secondPermute(string input, int *permChoiceTwo)
{
    string res = "";
    for (int i = 0; i < 48; i++)
        res += input[permChoiceTwo[i] -1];
    return res;
}
void genKeys(string left, string right, int *permChoiceTwo, int *leftShiftTable)
{
    ofstream fout("keygen.txt");          
    
    for (int i = 0; i < 16; i++)
    {
        left = rotateSubKey(left, leftShiftTable[i]);
        right = rotateSubKey(right, leftShiftTable[i]);
        string key = secondPermute(left + right, permChoiceTwo);
        string keyH=bin_to_hex(key);
        cout << "key " << i + 1 << " : " << key << "\t\t"<<keyH<<endl;
        fout << key << endl; 
    }
    fout.close();
}
int main()
{
    int permChoiceOne[] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4};
    int permChoiceTwo[] = {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32};
    int leftShiftTable[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2,
                            2, 2, 2, 1};

    unsigned long long hexkey;
    cout << "\nEnter 64-bit key in hexadecimal(16-digits) : ";
    cin >> hex >> hexkey;
 
    string key = bitset<64>(hexkey).to_string();
    cout << "Binary key (k) \t: " << key << endl;

    key = firstPermute(key, permChoiceOne);
    cout << "PC-1 key (k+) \t: " << key << endl;

    cout << "\nSubKeys: " << endl;
    genKeys(key.substr(0, 28),
            key.substr(28, 28), permChoiceTwo, leftShiftTable);
    cout << endl
         << endl;
    return 0;
}