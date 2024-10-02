#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

#include "encrypter.h"

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    if (argc < 4) {
        cerr << "Укажите три аргумента: [режим 'e'] [имя входного файла]" << endl;
        return 1;
    }

    if (argv[1][0] == 'e') {
        // Ключ шифрования в двоичном формате

        vector<uint8_t> key = {
            0x00, 0x01, 0x01, 0x01, 0x10, 0x00, 0x01, 0x01,
            0x10, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x11
          };

        string inputFilename = argv[2];
        string outputFilename = argv[3];

        int result = modifyFile(inputFilename, outputFilename, key);

        cout << "Файл успешно зашифрован!" << endl;
        return result;
    }


    return 0;
}