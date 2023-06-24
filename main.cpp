#include "FileUtil.h"
#include <iostream>
#include <filesystem>

void PrintBanner(){
    std::string banner = R"(
   ________    __   ____     ___ __    ___ ___
  / __/ __ \  / /  / __/__  / (_) /_  <  // _ \
 _\ \/ /_/ / / /___\ \/ _ \/ / / __/  / // // /
/___/\___\_\/____/___/ .__/_/_/\__/  /_(_)___/
                    /_/                 @clait
    )";

    std::cout << banner << std::endl;
}

void PrintHelp(){
    std::cerr << "Usage:" << std::endl;
    std::cerr << "  SQLSplit <command> <options>" << std::endl;
    std::cerr << "\nCommands:" << std::endl;
    std::cerr << "  split    - Splits a SQL file into multiple table files." << std::endl;
    std::cerr << "  combine  - Combines multiple table files into a single SQL file." << std::endl;
    std::cerr << "\nOptions:" << std::endl;
    std::cerr << "  For split:   <input_file> [output_directory]" << std::endl;
    std::cerr << "  For combine: <input_directory> <output_file>" << std::endl;
    std::cerr << "\nExamples:" << std::endl;
    std::cerr << "  SQLSplit split database.sql output_directory" << std::endl;
    std::cerr << "  SQLSplit combine output_directory combined_database.sql" << std::endl;

    std::cerr << "\nNote: The output directory will be created if it doesn't exist." << std::endl;
    std::cerr << "      The output file will be overwritten if it already exists." << std::endl;
    std::cerr << "==================================================================" << std::endl;
}

int main(int argc, char *argv[]) {

    PrintBanner();

    if (argc < 3) {

        PrintHelp();
        return 1;
    }

    std::string command = argv[1];

    if (command == "split") {
        std::string inputFilePath = argv[2];

        std::string outputDirectory = "output";  // Default output directory
        if (argc > 3) {
            outputDirectory = argv[3];  // Use provided output directory if available
        }

        std::filesystem::create_directories(outputDirectory);  // Create the output directory if it doesn't exist

        auto outputFiles = FileUtil::splitSQL(inputFilePath, outputDirectory);
        std::cout << "[INFO] Split into " << outputFiles.size() << " files." << std::endl;
    }
    else if (command == "combine") {
        if (argc < 4) {
            PrintHelp();
            return 1;
        }

        std::string inputDirectory = argv[2];
        if (!std::filesystem::exists(inputDirectory) || !std::filesystem::is_directory(inputDirectory)) {
            std::cerr << "[ERROR] Input directory does not exist or is not a directory: " << inputDirectory << std::endl;
            return 1;
        }

        std::vector<std::string> inputFiles;
        for (const auto &entry : std::filesystem::directory_iterator(inputDirectory)) {
            if (entry.path().extension() == ".sql") {
                inputFiles.push_back(entry.path().string());
            }
        }

        FileUtil::recombineSQL(inputFiles, argv[3]);
        std::cout << "[INFO] Combined into " << argv[3] << std::endl;
    }
    else {
        std::cerr << "Unknown command " << command << std::endl;
        return 1;
    }

    return 0;
}


