#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

double weight = 0.3, learning_rate = 0.0001, bias = 0.3;

double predict(double input);
double error(double predicted_sum, double output_sum, long size_of_dataset);
void update_weight(double input_sum, double output_sum, long size_of_dataset);
void update_bias(double input_sum, double output_sum, long size_of_dataset);

int main() {
    // system("clear");

    //variables
    string line; //to read and store lines from the file
    long i, size_of_dataset;
    double epoch = 10, input_sum = 0, output_sum = 0;
    vector<double> input_values, output_values;
    fstream infile;

    infile.open("data.txt");
    if(!infile) {
        cout<<"File not found";
        return 1;
    }

    while(getline(infile,line)) {
        i = 0;

        //variables local to loop
        string value = "";
        double input, output;

        while(line[i] != ',') {
            //read the input value
            value += line[i];
            i++;
        }

        //convert the vaule to double
        input = stod(value);

        //empty the string to store the output
        value = "";

        i++; //move pas the comma

        while(i < line.size()) {
            //read the output value
            value += line[i];
            i++;
        }

        //convert value to double
        output = stod(value);

        //add to the value of input_sum and output_sum
        input_sum += input;
        output_sum += output;

        //push input and output to respective vectors

        input_values.push_back(input);
        output_values.push_back(output);
    }

    //initialize size of dataset
    size_of_dataset = input_values.size();

    while(epoch--) {
        
        //variables local to each epoch
        double estimated_sum = 0, err;

        for(i = 0; i < size_of_dataset; i++) {
            double estimated_value = predict(input_values[i]);
            estimated_sum += estimated_value;
        }

        err = error(estimated_sum, output_sum, size_of_dataset);

        update_weight(input_sum, output_sum, size_of_dataset);

        update_bias(input_sum, output_sum, size_of_dataset);
    }

    long testcase;
    cout<<"Enter number of test cases: ";
    cin>>testcase;
    while(testcase--) {
        cout<<endl;
        cout<<"Enter input value: ";
        double input_test;
        cin>>input_test;
        cout<<endl<<"Predicted output values is "<<predict(input_test)<<endl;
    }

    return 0;
}

double predict(double input) {
    return ((weight * input) + bias);
}

double error(double predicted_sum, double output_sum, long size_of_dataset) {
    return pow((predicted_sum - output_sum),2) / size_of_dataset;
}

void update_weight(double input_sum, double output_sum, long size_of_dataset) {
    weight = weight - (learning_rate * (2 * input_sum * ((weight * input_sum) + (size_of_dataset * bias) - output_sum) / size_of_dataset));
}

void update_bias(double input_sum, double output_sum, long size_of_dataset) {
    bias = bias - (learning_rate * (2 * ((weight * input_sum) + (size_of_dataset * bias) - output_sum) / size_of_dataset));   
}