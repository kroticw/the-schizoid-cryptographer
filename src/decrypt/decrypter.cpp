//
// Created by  Денис Давыдов on 01.10.2024.
//


#include <fstream>
#include <iostream>
#include <vector>

void decryptStep(std::vector<uint8_t>& block, const std::vector<uint8_t>& key) {
    for (int i = 0; i < 8; ++i) {
        std::swap(block[i], block[i + 8]);
    }

    for (int i = 0; i < 12; ++i) {
        if (i < 8) block[i] = block[i] ^ key[i];
        else std::swap(block[i], block[i + 4]);
    }
}

void decryptBlock(std::vector<uint8_t>& block, const std::vector<uint8_t>& key) {
    std::vector<uint8_t> K1(key.begin(), key.begin() + 8);
    std::vector<uint8_t> K2(key.begin() + 4, key.begin() + 12);
    std::vector<uint8_t> K3(key.begin() + 6, key.begin() + 14);
    std::vector<uint8_t> K4(key.begin() + 8, key.end());

    decryptStep(block, K4);
    decryptStep(block, K3);
    decryptStep(block, K2);
    decryptStep(block, K1);
}

// void modifyFile(const std::string& inputFilename, const std::string& outputFilename, const std::vector<uint8_t>& key) {
//     std::ifstream inputFile(inputFilename, std::ios::binary);
//     std::ofstream outputFile(outputFilename, std::ios::binary);
//
//     if (!inputFile.is_open()) {
//         std::cerr << "Не удалось открыть файл [имя входного файла]" << std::endl;
//         return;
//     }
//
//     if (!outputFile.is_open()) {
//         std::cerr << "Не удалось открыть файл [имя выходного файла]" << std::endl;
//         return;
//     }
//
//     // Считываем файл блоками по 16 байт
//     std::vector<uint8_t> block(16);
//     while (!inputFile.eof()) {
//         inputFile.read(reinterpret_cast<char *>(&block[0]), 16);
//         if (inputFile.gcount() == 16) { // Проверяем, что было прочитано 16 байт
//             decryptBlock(block, key);
//
//             outputFile.write(reinterpret_cast<char *>(&block[0]), 16);
//         }
//     }
//
//     inputFile.close();
//     outputFile.close();
// }
