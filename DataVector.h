#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
class DataVector
{
private:
    int dimension;
    vector<double> v;

public:
    DataVector(int size=0);                                              // Constructor
    DataVector(vector<double> &);                                        // Constructor
    DataVector(const DataVector &);                                      // Copy Constructor
    ~DataVector();                                                       // Destructor
    DataVector &operator=(const DataVector &);                           // Copy Assignment Operator
    int getDimension() const;                                            // Access Dimension
    void setDimension(int size=0);                                       // Change Dimension
    double getCoordinate(int);                                           // Access a coordinate in Vector
    void setCoordinate(int, double);                                     // Change a coordinate in Vector
    DataVector operator+(const DataVector &);                            // Vector Addition
    DataVector operator-(const DataVector &);                            // Vector Subtraction
    double operator*(const DataVector &);                                // Dot Product
    double norm();                                                       // Length of Vector
    double dist(const DataVector &);                                     // Distance between two Vectors
    bool operator==(const DataVector &);                                 // Compare two Vectors
    friend std::ostream &operator<<(std::ostream &, DataVector const &); // Print Vector
};

//  <<:(friend function) To print the vector coordinates, seperated by commas (facilitates writing vector into CSV file)
