#include <iostream>
//#include "pairs.cc"
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
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
    double adj_close_a[size];
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

    //now do for other file
    std::ifstream file_b("K.csv");
    int row_num_b = 0;
    std::string line3;
    std::getline(file_b, line3);
    //const int size = rows;
    double adj_close_b[size];
    while(file_b.good()) { // row
        for (int i = 0; i < columns; ++i) { //column
            std::string cell2;
            if ( i == 6) { 
                std::getline(file_b,cell2, '\n');
            }
            else {
                std::getline(file_b, cell2, ',');
                if (i == 5) {
                    adj_close_b[row_num_b] = std::stod(cell2);
                }
            }
        }
        row_num_b++;
    }
   
    // is it size - 1?
    double log_return_a[size - 1];
    double log_return_b[size - 1];

    for (int h = 0; h < size - 1; ++h) { 
        log_return_a[h] = log(adj_close_a[h+1]) - log(adj_close_a[h]);
        log_return_b[h] = log(adj_close_b[h+1]) - log(adj_close_b[h]);
    }

    int n = size - 1;
    double sum_a = 0;
    double sum_b = 0;
    for(int k = 0; k < n; k++) {
        sum_a += log_return_a[k];
        sum_b += log_return_b[k];
    }

    double mean_a = sum_a / n;
    double mean_b = sum_b / n;

    
    double deviation_a[n];
    double squared_dev_a[n];
    double squared_dev_sum_a = 0; 
    double deviation_b[n];
    double squared_dev_b[n];
    double squared_dev_sum_b = 0; 
    for (int index = 0; index < n; index++) {
        deviation_a[index] = log_return_a[index] - mean_a;
        squared_dev_a[index] = deviation_a[index] * deviation_a[index];
        squared_dev_sum_a += squared_dev_a[index];
        deviation_b[index] = log_return_b[index] - mean_b;
        squared_dev_b[index] = deviation_b[index] * deviation_b[index];
        squared_dev_sum_b += squared_dev_b[index];
    }

    double degrees_freedom = n-1;
    double variance_a = squared_dev_sum_a / (degrees_freedom); //variance
    double std_deviation_a = sqrt(variance_a); //standard deviation

    double variance_b = squared_dev_sum_b / (degrees_freedom); //variance
    double std_deviation_b = sqrt(variance_b); //standard deviation
    
    //Z-score
    double z_scores_a[n];
    double z_scores_b[n];

    for (int g = 0; g < n; ++g) {
        z_scores_a[g] = (log_return_a[g] - mean_a) / std_deviation_a;
        z_scores_b[g] = (log_return_b[g] - mean_b) / std_deviation_b;
    }

    //Inter-quartitle Range

    //max
    double maximum_a = log_return_a[0];
    double maximum_b = log_return_b[0];

    for (int z = 0; z < n; ++z) {
        if (maximum_a < log_return_a[z]) {
            maximum_a = log_return_a[z];
        }
        if (maximum_b < log_return_b[z]) {
            maximum_b = log_return_b[z];
        }
    }
    //min
    double minimum_a = log_return_a[0];
    double minimum_b = log_return_b[0];
    for (int z = 0; z < n; ++z) {
        if (minimum_a > log_return_a[z]) {
            minimum_a = log_return_a[z];
        }
        if (minimum_b > log_return_b[z]) {
            minimum_b = log_return_b[z];
        }
    }
    //range 
    double range_a = maximum_a - minimum_a;
    double range_b = maximum_b - minimum_b;

    // correlation
    double product[n];
    double product_sum = 0;
    for (int x = 0; x < n; ++x) {
        product[x] = z_scores_a[x] * z_scores_b[x];
        product_sum += product[x];
        std::cout << product[x]<< "   " << product_sum << "\n";
    }

    double pearson_correlation = product_sum / (n - 1);
   // std::cout << product_sum << "\n" << pearson_correlation;
    // cointegration
    //Inter-Quartile range


    // 
    
    
    return 0;
   
}