#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

void encryptStep(vector<uint8_t>& block, const vector<uint8_t>& key) {
    for (int i = 0; i < 12; ++i) {
        if (i < 8) block[i] = block[i] ^ key[i];
        else swap(block[i], block[i + 4]);
    }

    for (int i = 0; i < 8; ++i) {
        swap(block[i], block[i + 8]);
    }
}

void encryptBlock(vector<uint8_t>& block, const vector<uint8_t>& key) {
    vector<uint8_t> K1(key.begin(), key.begin() + 8);
    vector<uint8_t> K2(key.begin() + 4, key.begin() + 12);
    vector<uint8_t> K3(key.begin() + 6, key.begin() + 14);
    vector<uint8_t> K4(key.begin() + 8, key.end());

    encryptStep(block, K1);
    encryptStep(block, K2);
    encryptStep(block, K3);
    encryptStep(block, K4);
}

void decryptStep(vector<uint8_t>& block, const vector<uint8_t>& key) {
    for (int i = 0; i < 8; ++i) {
        swap(block[i], block[i + 8]);
    }

    for (int i = 0; i < 12; ++i) {
        if (i < 8) block[i] = block[i] ^ key[i];
        else swap(block[i], block[i + 4]);
    }
}

void decryptBlock(vector<uint8_t>& block, const vector<uint8_t>& key) {
    vector<uint8_t> K1(key.begin(), key.begin() + 8);
    vector<uint8_t> K2(key.begin() + 4, key.begin() + 12);
    vector<uint8_t> K3(key.begin() + 6, key.begin() + 14);
    vector<uint8_t> K4(key.begin() + 8, key.end());

    decryptStep(block, K4);
    decryptStep(block, K3);
    decryptStep(block, K2);
    decryptStep(block, K1);
}

void modifyFile(const string& inputFilename, const string& outputFilename, const vector<uint8_t>& key, const string& mode) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);

    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл [имя входного файла]" << endl;
        return;
    }

    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл [имя выходного файла]" << endl;
        return;
    }

    // Считываем файл блоками по 16 байт
    vector<uint8_t> block(16);
    while (!inputFile.eof()) {
        inputFile.read((char*)&block[0], 16);
        if (inputFile.gcount() == 16) { // Проверяем, что было прочитано 16 байт
            if (mode == "encrypt") encryptBlock(block, key);
            else if (mode == "decrypt") decryptBlock(block, key);

            outputFile.write((char*)&block[0], 16);
        }
    }

    inputFile.close();
    outputFile.close();
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    if (false && argc < 4) {
        cerr << "Укажите три аргумента: [имя входного файла] [имя выходного файла] [режим 'encrypt' или 'decrypt']" << endl;
        return 1;
    }

    // Ключ шифрования в двоичном формате
    vector<uint8_t> key = {
      0x00, 0x01, 0x01, 0x01, 0x10, 0x00, 0x01, 0x01,
      0x10, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x11
    };

    string inputFilename = argv[1];
    string outputFilename = argv[2];
    string mode = argv[3];

    modifyFile(inputFilename, outputFilename, key, mode);

    if (mode == "encrypt") cout << "Файл успешно зашифрован!" << endl;
    else if (mode == "decrypt") cout << "Файл успешно расшифрован!" << endl;
    else cout << "Третий аргумент [режим] может принимать значения только 'encrypt' или 'decrypt";

    return 0;
}