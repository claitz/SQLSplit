#include "FileUtil.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <iomanip>

std::vector<std::string> FileUtil::splitSQL(const std::string &inputFilePath, const std::string &outputDirectory) {
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "ERROR: Failed to open input file: " << inputFilePath << std::endl;
        return {};
    }

    // Create output directory if it doesn't exist
    std::filesystem::path outputPath(outputDirectory);
    if (!std::filesystem::exists(outputPath)) {
        std::filesystem::create_directories(outputPath);
    }

    std::string line, currentTable;
    std::vector<std::string> outputFiles;
    std::ofstream outputFile;
    std::vector<std::string> headerLines;
    bool isFirstTable = true;
    int progressIndex = 0;
    size_t lineCount = 0;
    int maxLineLength = 0;

    while (std::getline(inputFile, line)) {
        // Capture the header lines before the first table
        if (isFirstTable && line.find("/*!") == 0) {
            headerLines.push_back(line);
            continue;
        }

        if (line.find("CREATE TABLE") != std::string::npos) {
            isFirstTable = false;
            if (outputFile.is_open()) {
                outputFile.close();
            }
            std::stringstream ss(line);
            std::string word;
            ss >> word >> word >> word >> word >> word >> currentTable;
            currentTable = currentTable.substr(1, currentTable.size() - 2); // Remove the ` characters
            std::string outputFilePath = outputDirectory + "/" + currentTable + ".sql";
            outputFile.open(outputFilePath);
            if (!outputFile.is_open()) {
                std::cerr << "ERROR: Failed to open output file: " << outputFilePath << std::endl;
                continue;
            }
            // Write header lines to the output file
            for (const auto &headerLine : headerLines) {
                outputFile << headerLine << std::endl;
            }
            outputFiles.push_back(outputFilePath);
        }
        if (outputFile.is_open()) {
            outputFile << line << std::endl;
        }

        if (++lineCount % 100 == 0) { // Update progress every 100 lines
            std::string progressMessage = "INFO: Processing table: " + currentTable + " " + progressIndicator[progressIndex++ % 4];
            maxLineLength = std::max(maxLineLength, static_cast<int>(progressMessage.length()));
            std::cout << "\r" << progressMessage << std::setw(maxLineLength - progressMessage.length() + 1) << " " << std::flush;
        }
    }

    std::cout << "\rINFO: Processing table: " << currentTable << " Done.   " << std::setw(maxLineLength - currentTable.length() + 1) << " " << std::endl;

    if (outputFile.is_open()) {
        outputFile.close();
    }
    return outputFiles;
}

void FileUtil::recombineSQL(const std::vector<std::string> &inputFilePaths, const std::string &outputFilePath) {
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "ERROR: Failed to open output file: " << outputFilePath << std::endl;
        return;
    }

    int progressIndex = 0;
    size_t lineCount = 0;
    int maxLineLength = 0;

    for (const auto &inputFilePath : inputFilePaths) {
        std::ifstream inputFile(inputFilePath);
        if (!inputFile.is_open()) {
            std::cerr << "ERROR: Failed to open input file: " << inputFilePath << std::endl;
            continue;
        }
        std::string line;
        while (std::getline(inputFile, line)) {
            outputFile << line << std::endl;
            if (++lineCount % 100 == 0) { // Update progress every 100 lines
                std::string progressMessage = "INFO: Combining file: " + inputFilePath + " " + progressIndicator[progressIndex++ % 4];
                maxLineLength = std::max(maxLineLength, static_cast<int>(progressMessage.length()));
                std::cout << "\r" << progressMessage << std::setw(maxLineLength - progressMessage.length() + 1) << " " << std::flush;
            }
        }
    }
    std::cout << "\rINFO: Done recombining files.   " << std::setw(maxLineLength + 1) << " " << std::endl;
}
