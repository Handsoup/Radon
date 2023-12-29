//VectorOperations.h

#ifndef MY_FUNCTION_HPP
#define MY_FUNCTION_HPP

#include <vector>

inline void Print2DDoubleVector(std::vector<std::vector<double>>& matrix) {
   
	for (const auto& row : matrix) {
        for (const auto& val : row) {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }

}

#endif // MY_FUNCTION_HPP

