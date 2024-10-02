//
// Created by  Денис Давыдов on 25.09.2024.
//

#ifndef ENCRYPTER_H
#define ENCRYPTER_H
#include <vector>

int modifyFile(const std::string& inputFilename, const std::string& outputFilename, const std::vector<uint8_t>& key);

#endif //ENCRYPTER_H
