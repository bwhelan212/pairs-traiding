#include <iostream>
#include <string>
#include <fstream>
#include <vector>
int main (int argc, char* argv[]) {
    std::ifstream file_a("K.csv");
    std::string line;
    int rows = 0;
    int columns = 7;

    std::getline(file_a, line);
    while(std::getline(file_a, line)) {
        rows++;
    }

    file_a.close();
   
    file_a.open("K.csv");
    int row_num_a = 0;

    // skip first line
    std::string line2;
    std::getline(file_a, line2);
    const int size = rows;
    double* adj_close_a = new double[size];
    while(file_a.good()) { // row
        for (int i = 0; i < columns; ++i) { //column
            std::string cell;
            if ( i == 6) { 
                std::getline(file_a,cell, '\n');
            }
            else {
                std::getline(file_a, cell, ',');
                if (i == 5) {
                    adj_close_a[row_num_a] = std::stod(cell);
                }
            }
        }
        row_num_a++;
    }

    std::ifstream file_b("MKC.csv");
    std::cout << adj_close_a[0];
    return 0;
}