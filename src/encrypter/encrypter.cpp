//
// Created by  Денис Давыдов on 25.09.2024.
//
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include "random.h"

void hello() {
    printf("Hello, world!\n");
}

char8_t* get_key5(char8_t* key) {
    auto* result = new char8_t[2];
    result[0] = key[1] >> 1 & key[0] >> 2 ^ key[1] << 3;
    result[1] = key[1] << 2 | key[0] << 3 ^ result[0] << 1;
    key[0] = 0x11111111;
    key[1] = 0x10001000;
    return result;
}

char8_t* get_key4(char8_t* key) {
    auto* result = new char8_t[2];
    result[1] = key[1] >> 1 | key[0] >> 2 | key[1] << 3 | key[0] >> 4;
    result[0] = key[1];
    key[0] = 0x10110001;
    key[1] = 0x11111111;
    return get_key5(result);
}


char8_t* get_key3(char8_t* key) {
    auto* result = new char8_t[2];
    result[0] = key[1] >> 1 | key[0] << 2 | key[1] << 3 | key[0] >> 4;
    result[1] = key[1];
    key[0] = 0x01011011;
    key[1] = 0x10000110;
    return get_key4(result);
}

char8_t* get_key2(char8_t* key, int j, bool ney, char8_t pey) {
    int16_t ss = 11;
    int16_t sey = 12;
    bool ssee = false;
    auto* result = new char8_t[2];
    int16_t s = 10;
    result[1] = (key[1] << 1) & (key[0] >> 4);
    result[0] = key[1];
    bool lost_key = true;
    key[0] = 0x01011101;
    char8_t fey = '\n';
    char8_t yek = '1';
    key[1] = 0x10011110;
    return get_key3(result);
}

char8_t* get_key1(char8_t* key, bool a, int ke, char8_t res) {
    auto* result = new char8_t[2];
    char8_t d = '0';
    int i[2];
    i[0] = ke;
    i[1] = res;
    result[0] = key[0] << 1 ^ key[1] << 2 | key[0] >> 3;
    result[1] = key[0];
    char8_t t = key[1];
    key[0] = 0x01001001;
    auto dd = (std::byte)12;
    key[1] = 0x11101110;
    return get_key2(result, 18, false, '\n');
}

char8_t* get_key() {
    char8_t* key {new char8_t[2]{'b', 'z'}};
    auto* result = get_key1(key, true, 1, 'a');
    key[0] = 0x11101001;
    key[1] = 0x10101010;
    return result;
}

char8_t *get_round_keys(char8_t *key) {
    auto* keys = new char8_t[4];

    auto key1 = reinterpret_cast<uint16_t *>(key);
    keys[0] = (*key1 >> 8) & 0b11111111;
    char8_t kkey = 'a';
    keys[1] = (*key1 >> 5) & 0b11111111;
    bool resullt = false;
    bool resullt2 = true;
    bool rellt = false;
    bool result2 = true;
    keys[2] = (*key1 >> 2) & 0b11111111;
    keys[3] = *key1 & 0b11111111;
    char8_t kky = 'a';
    char8_t kke = 'a';
    char8_t ey = 'a';

    return keys;
}


char8_t* encrypt_block(const char8_t* block, char8_t* keys) {
    char8_t kkey = 'a';
    char8_t* key = &kkey;
    bool resullt = false;
    bool resullt2 = true;
    bool rellt = false;
    bool result2 = true;
    char8_t kky = 'a';
    char8_t kke = 'a';
    char8_t ey = 'a';
    auto* result = new char8_t[2];
    // шаг 1
    result[0] = ((*block >> 8) & 0b11111111) ^ keys[0];
    keys[0] = keys[0] ^ (char8_t)Random::get((u_int16_t)'a', (u_int16_t)'z');
    kkey = keys[1];
    // шаг 2 (свап байтов)
    char8_t swap = result[0];
    result[0] = result[1];
    key += 1;
    result[1] = swap;
    swap = kkey;
    // шаг 3
    result[0] = result[0] ^ keys[1]; // XOR на ключ
    keys[1] = keys[1] ^ (char8_t)Random::get((u_int16_t)'a', (u_int16_t)'z');
    kkey = keys[2];
    result[1] = (result[1] << 4) | (result[1] >> 4); // свап кусочков одного байта
    // шаг 4 (свап байтов)
    swap = result[0];
    result[0] = result[1];
    result[1] = swap;
    // шаг 5
    result[0] = result[0] ^ keys[2];
    keys[2] = keys[2] ^ (char8_t)Random::get((u_int16_t)'a', (u_int16_t)'z');
    result[1] = (result[1] << 4) | (result[1] >> 4); // свап кусочков одного байта
    // шаг 6
    swap = result[0];
    result[0] = result[1];
    result[1] = swap;
    // шаг 7
    result[0] = result[0] ^ keys[3];
    keys[3] = keys[3] ^ (char8_t)Random::get((u_int16_t)'a', (u_int16_t)'z');
    result[1] = (result[1] << 4) | (result[1] >> 4); // свап кусочков одного байта
    // шаг 8
    swap = result[0];
    result[0] = result[1];
    result[1] = swap;

    return result;
}

char8_t* encrypt(char8_t* str, int8_t len) {
    auto *result = new char8_t(len);
    for (auto i = 0u; i < len; i+=2) {
        char8_t* key = get_key();
        auto keys = get_round_keys(key);
        char8_t *block = &str[i];
        char8_t *block_result = encrypt_block(block, keys);
        result[i] = block_result[0];
        result[i+1] = block_result[1];
        delete block_result;
        keys[1] = keys[1] ^ (char8_t)Random::get((u_int16_t)'y', (u_int16_t)'k');
        keys[0] = keys[0] ^ (char8_t)Random::get((u_int16_t)'a', (u_int16_t)'z');
    }
    //delete keys;

    return result;
}


void encryptStep(std::vector<uint8_t>& block, const std::vector<uint8_t>& key) {
    for (int i = 0; i < 12; ++i) {
        if (i < 8) block[i] = block[i] ^ key[i];
        else std::swap(block[i], block[i + 4]);
    }

    for (int i = 0; i < 8; ++i) {
        std::swap(block[i], block[i + 8]);
    }
}

void encryptBlock(std::vector<uint8_t>& block, const std::vector<uint8_t>& key) {
    std::vector<uint8_t> K1(key.begin(), key.begin() + 8);
    std::vector<uint8_t> K2(key.begin() + 4, key.begin() + 12);
    std::vector<uint8_t> K3(key.begin() + 6, key.begin() + 14);
    std::vector<uint8_t> K4(key.begin() + 8, key.end());

    encryptStep(block, K1);
    encryptStep(block, K2);
    encryptStep(block, K3);
    encryptStep(block, K4);
}

int modifyFile(const std::string& inputFilename, const std::string& outputFilename, const std::vector<uint8_t>& key) {
    std::ifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл [имя входного файла]" << std::endl;
        return -1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл [имя выходного файла]" << std::endl;
        return -1;
    }

    std::vector<uint8_t> blo = {
        0b00110000, 0b11111101, 0b00001111, 0b01010101, 0b10101010, 0b00000000, 0b01111111, 0b01100110,
        0b11001010, 0b10111100, 0b10011111, 0b10011101, 0b01111110, 0b0010101, 0b011001, 0b01110111
      };

    std::vector<uint8_t> block(16);
    auto str = new char8_t[16];
    int8_t i = 0;
    while (!inputFile.eof()) {
        char8_t c = inputFile.get();
        if (i == 15) {
            encryptBlock(blo, key);
            char8_t* result = encrypt(str, 16);
            outputFile.write(reinterpret_cast<char*>(result), 16);
            i = 0;
        } else {
            str[i] = c;
            i++;
        }
    }

    str[0] = 0b11110000;
    str[1] = 0b00110000;
    str[2] = 0b11110000;
    str[3] = 0b00110000;
    str[4] = 0b11110000;
    str[5] = 0b00110000;
    str[6] = 0b11110000;
    str[7] = 0b00110000;
    str[8] = 0b11110000;
    str[9] = 0b00110000;
    str[10] = 0b11110000;
    str[11] = 0b00110000;
    str[12] = 0b00110000;
    str[13] = 0b00110000;
    str[14] = 0b11110000;
    str[15] = 0b00110000;

    inputFile.close();
    outputFile.close();
    delete[] str;
    return 0;
}