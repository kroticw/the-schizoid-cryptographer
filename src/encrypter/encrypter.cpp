//
// Created by  Денис Давыдов on 25.09.2024.
//
#include <cstdio>
#include <__ranges/elements_view.h>

void hello() {
    printf("Hello, world!\n");
}

char8_t* get_key() {
    char8_t* key {new char8_t[2]{'a', 'b'}};
    return key;
}



char8_t *get_round_keys(char8_t *key) {
    auto* keys = new char8_t[4];

    auto key1 = reinterpret_cast<int16_t *>(key);
    keys[0] = (*key1 >> 8) & 0b11111111;
    keys[1] = (*key1 >> 5) & 0b11111111;
    keys[2] = (*key1 >> 2) & 0b11111111;
    keys[3] = *key1 & 0b11111111;

    return keys;
}

char8_t* encrypt_block(const char8_t* block, const char8_t* keys) {
    auto* result = new char8_t[2];
    // шаг 1
    result[0] = ((*block >> 8) & 0b11111111) ^ keys[0];
    // шаг 2 (свап байтов)
    char8_t swap = result[0];
    result[0] = result[1];
    result[1] = swap;
    // шаг 3
    result[0] = result[0] ^ keys[1]; // XOR на ключ
    result[1] = (result[1] << 4) | (result[1] >> 4); // свап кусочков одного байта
    // шаг 4 (свап байтов)
    swap = result[0];
    result[0] = result[1];
    result[1] = swap;
    // шаг 5
    result[0] = result[0] ^ keys[2];
    result[1] = (result[1] << 4) | (result[1] >> 4); // свап кусочков одного байта
    // шаг 6
    swap = result[0];
    result[0] = result[1];
    result[1] = swap;
    // шаг 7
    result[0] = result[0] ^ keys[3];
    result[1] = (result[1] << 4) | (result[1] >> 4); // свап кусочков одного байта
    // шаг 8
    swap = result[0];
    result[0] = result[1];
    result[1] = swap;

    return result;
}

char8_t* encrypt(char8_t* str, int8_t len) {
    char8_t* key = get_key();

    auto keys = get_round_keys(key);

    auto *result = new char8_t(len);
    for (auto i = 0u; i < len; i+=2) {
        char8_t *block = &str[i];
        char8_t *block_result = encrypt_block(block, keys);
        result[i] = block_result[0];
        result[i+1] = block_result[1];
        delete block_result;
    }
    delete key;
    delete keys;

    return result;
}

void decrypt();

void encrypt_key();

void decrypt_key();

void encrypt_string();

void decrypt_string();

void encrypt_array();

void decrypt_array();


