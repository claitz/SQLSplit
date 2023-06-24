#pragma once

#include <string>
#include <vector>

class FileUtil {
public:
    constexpr static const char progressIndicator[8] = {'-', '\\', '|', '/', '-', '\\', '|', '/'};

    static std::vector<std::string> splitSQL(const std::string &inputFilePath, const std::string &outputDirectory);
    static void recombineSQL(const std::vector<std::string> &inputFilePaths, const std::string &outputFilePath);
};
