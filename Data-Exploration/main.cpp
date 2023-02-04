// Dmitrii Obideiko
// DXO200006

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;

// Find the sum of all elements in the given vector
double findSum(vector<double> data) {
    double sum = 0;
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    
    return sum;
}

// Find the mean of all elements in the given vector
double findMean(vector<double> data) {
    double sum = findSum(data);
    return sum / data.size();
}

// Find the medium of all elements in the given vector
double findMed(vector<double> data) {
    sort(data.begin(), data.end());
    int middle = int(data.size() / 2) + 1;
    return data[middle];
}

// Find the range of all elements in the given vector
double findRange(vector<double> data) {
    double min = *min_element(data.begin(), data.end());
    double max = *max_element(data.begin(), data.end());
    
    return max - min;
}

// Callulate various statistics about the data and print the results
void print_stats(vector<double> data) {
    cout << "Sum: "    << findSum(data) << endl;
    cout << "Mean: "   << findMean(data) << endl;
    cout << "Medium: " << findMed(data) << endl;
    cout << "Range: "  << findRange(data) << endl << endl;
}

// Find the covariance
double covar(vector<double> data1, vector<double> data2) {
    double res = 0.0;
    for (int i = 0; i < data1.size(); i++) {
        res += (data1[i] - findMean(data1)) * (data2[i] - findMean(data2));
    }
    
    return res / (data1.size() - 1);
}

// Find the variance
double findVar(vector<double> data) {
    double mean = findMean(data);
    double total = 0;
    for (int i = 0; i < data.size(); i++) {
        double dif = data[i] - mean;
        total += dif * dif;
    }
    
    total /= (data.size() - 1);
    
    
    return sqrt(total);
}

double cor(vector<double> data1, vector<double> data2) {
    return covar(data1, data2) / (findVar(data1) * findVar(data2));
}

int main(int argc, const char * argv[]) {
    ifstream inFS;
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);
    
    cout << "Opening file Boston.csv." << endl;
    
    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file Boston.csv" << endl;
        return 1; // 1 indicates error
    }
        
    cout << "Reading line 1" << endl;
    getline(inFS, line);
    
    // echo heading
    cout << "heading: " << line << endl;
    
    int numObservations = 0;
    while (inFS.good()) {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');
        
        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);
        
        numObservations ++;
    }
    
    rm.resize(numObservations);
    medv.resize(numObservations);
    
    cout << "new length " << rm.size() << endl;
    inFS.close();  // close the file
    
    cout << "Number of records: " << numObservations << endl;
    
    cout << "\nStats for rm" << endl;
    print_stats(rm);
    
    cout << "\nStats for medv" << endl;
    print_stats(medv);
    
    cout << "\nConvariance = " << covar(rm, medv) << endl;
    
    cout << "\nCorrelation = " << cor(rm, medv) << endl;
    
    cout << "\nProgram terminated.";
    
    return 0;
}
