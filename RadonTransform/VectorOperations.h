//VectorOperations.h

#ifndef MY_FUNCTION_HPP
#define MY_FUNCTION_HPP

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
inline void PrintVector(const std::vector<T>& vec) {
    for (const auto& val : vec) {
        std::cout << val << ", ";
    }
    std::cout << std::endl;
}

template<typename T>
inline void Print2DVector(const std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }
}

inline void FindMinMax(const std::vector<std::vector<double>>& matrix, double& minVal, double& maxVal) {
    
	if (matrix.empty() || matrix[0].empty()) {
        std::cerr << "Matrix is empty!" << std::endl;
        return;
    }

    minVal = matrix[0][0];
    maxVal = matrix[0][0];

    for (int i = 0; i <  matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
			if(matrix[i][j] < minVal){
				minVal = matrix[i][j];
			}
            
			if(matrix[i][j] > maxVal){
				maxVal = matrix[i][j];
			
        	}
    	}
	}
	
}

#endif // MY_FUNCTION_HPP

