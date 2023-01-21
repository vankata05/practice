#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

double calculate_difference(double measured_value, double real_price, double website_price) {
    return (measured_value * real_price) / website_price;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please provide a file path." << endl;
        return 1;
    }
    
    string file_path = argv[1];
    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return 1;
    }
    
    double prices[4] = {0.129, 1.461, 85.07, 0.132};
    double company_data[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            file >> company_data[i][j];
        }
    }
    
    vector<double> total_prices;
    double temp;
    while (file >> temp) {
        total_prices.push_back(temp);
    }
    file.close();

    //get the real price
    double real_prices[4];
    real_prices[0] = company_data[0][0] * prices[0] + company_data[0][1]* prices[1] + company_data[0][2]* prices[2] + company_data[0][3]* prices[3];
    real_prices[1] = company_data[1][0] * prices[0] + company_data[1][1]* prices[1] + company_data[1][2]* prices[2] + company_data[1][3]* prices[3];
    real_prices[2] = company_data[2][0] * prices[0] + company_data[2][1]* prices[1] + company_data[2][2]* prices[2] + company_data[2][3]* prices[3];
    real_prices[3] = company_data[3][0] * prices[0] + company_data[3][1]* prices[1] + company_data[3][2]* prices[2] + company_data[3][3]* prices[3];

    for (int i = 0; i < 4; i++) {
        cout << "Difference for Company " << i+1 << endl;
        cout << "Total : " << real_prices[i] - total_prices[i] << endl;
        cout << "kWh: " << calculate_difference(company_data[i][0], prices[0], 0.129) << endl;
        cout << "m3: " << calculate_difference(company_data[i][1], prices[1], 1.461) << endl;
        cout << "MWh: " << calculate_difference(company_data[i][2], prices[2], 85.07) << endl;
        cout << "min: " << calculate_difference(company_data[i][3], prices[3], 0.132) << endl;
    }
    return 0;
}
