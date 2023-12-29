#include "CSVHandler.hpp"
#include <fstream>
#include <iostream>
#include <sstream> 

CSVHandler::CSVHandler() {
    // Constructor body if initialization is required
}

void CSVHandler::Write2DVectorToCSV(std::vector<std::vector<double>>& matrix, const std::string& name) {
    std::ofstream out(name);

    for (auto& row : matrix) {
        for (auto col : row)
            out << col << ';';
        out << '\n';
    }
}

void CSVHandler::Load2DVectorFromCSV(std::vector<std::vector<double>>& items, const std::string& path, char separator) {
  
	std::ifstream csv(path);
    std::string line;

    if (csv.is_open()) {
        while (std::getline(csv, line)) {
            std::istringstream row_stream(line);
            items.emplace_back();
            for (std::string column; std::getline(row_stream, column, separator);) {
                items.back().push_back(std::stod(column));
            }
        }
        csv.close();
    } 
	
	else {
        std::cout << "Unable to open file: " << path << std::endl;
    }

}

