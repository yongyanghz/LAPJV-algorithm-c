#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept> // Required for exception classes

#include "lap.h"

std::vector<std::string> split(const std::string& str, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delim);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

// Custom exception class for CSV parsing errors
class CSVParseException : public std::runtime_error {
public:
    CSVParseException(const std::string& message) : std::runtime_error(message) {}
};

std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw CSVParseException("Could not open file: " + filename);
    }
    if(filename.find(".csv") == std::string::npos){
        throw CSVParseException(filename + " is not a .csv file");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> row;
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

int main(int argc, char *argv[]) {
    std::cout<<"Hello, LAPJV user!"<<std::endl;
    if(argc < 2){
        std::cerr<<"Error: please input a .csv file"<<std::endl;
        return 0;
    }
    std::ifstream ifs;
    std::string filePath = argv[1];
    std::vector<std::vector<std::string>> data;
    try{
        data  = readCSV(filePath);
    }catch (const CSVParseException& error) {
        std::cerr << "CSV Parse Error: " << error.what() << std::endl;
        return 1; // Indicate an error occurred
    } catch (const std::exception& error) {
         std::cerr << "Standard Exception: " << error.what() << std::endl;
        return 1;
    }
    // Notice that col, row, cost these types are typedef-ed in lap.h
    int dim = data.size();        // Set the dimension of matrix to 10, dim is the problem size
    matrix costMatrix(dim, std::vector<cost>(dim));    // A matrix to store all the costs from vertex i to vertex j
    std::vector<col> rowsol(dim);         // An array to store column indexes assigned to row in solution  
    std::vector<row> colsol(dim);         // An array to store row indexes assigned to column in solution 
    std::vector<cost> u(dim);             // u          - dual variables, row reduction numbers
    std::vector<cost> v(dim);             // u          - dual variables, row reduction numbers
    // Assign costs to the costMatrix
    for(int i=0; i<dim; ++i){
        for(int j=0; j<dim; ++j){
            costMatrix[i][j]  =  atof(data[i][j].c_str());
   	    }
    }
    cost totalCost = lap(dim, costMatrix, rowsol, colsol, u, v);  // Use lap algorithm to calculate the minimum total cost
    // Output lap result to a file
    std::string solutionFileName = "solution.txt";
    std::ofstream ofs(solutionFileName);
    ofs<<totalCost<<std::endl;
    for(int i=0; i< (dim-1); i++){
        ofs<<rowsol[i]<<std::endl;
    }
    ofs<<rowsol[dim-1];
    std::cout<<"Congratulations! The lap calculation have completed, the solution is in solution.txt file."<<std::endl;
    return EXIT_SUCCESS;
}
