#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

int main() {
    std::string inputFileName, outputFileName;

    std::cout << "Write path to file in encoding (UTF-8): ";
    std::cin >> inputFileName;

    std::cout << "Write path to file in encoding  (Windows-1251): ";
    std::cin >> outputFileName;

    // Открываем входной файл в режиме бинарного чтения
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "I can't open imported file" << std::endl;
        return 1;
    }

    // Открываем выходной файл в режиме бинарной записи
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "I can't open exported file." << std::endl;
        return 1;
    }

    // Читаем и конвертируем содержимое входного файла и записываем его в выходной файл
    std::string line;

    while (std::getline(inputFile, line)) {
        int len = MultiByteToWideChar(CP_UTF8, 0, line.c_str(), -1, nullptr, 0);
        if (len > 0) {
            std::wstring wstr(len, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, line.c_str(), -1, &wstr[0], len);

            len = WideCharToMultiByte(1251, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
            if (len > 0) {
                std::string ansiStr(len, '\0');
                WideCharToMultiByte(1251, 0, wstr.c_str(), -1, &ansiStr[0], len, nullptr, nullptr);

                outputFile << ansiStr;
            }
        }
    }

    // Закрываем файлы
    inputFile.close();
    outputFile.close();

    std::cout << "Convertation successfull!" << std::endl;

    return 0;
}
