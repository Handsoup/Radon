#ifndef CSV_HANDLER_HPP
#define CSV_HANDLER_HPP

#include <string>
#include <vector>
#include <sstream> 

class CSVHandler {
public:
    CSVHandler(); // Constructor declaration

    void Write2DVectorToCSV(std::vector<std::vector<double>>& matrix, const std::string& name);

    void Load2DVectorFromCSV(std::vector<std::vector<double>>& items, const std::string& path, char separator);
};

#endif /* CSV_HANDLER_HPP */

