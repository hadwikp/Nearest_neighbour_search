#include"DataVector.h"
#include<fstream>
#include<sstream>
using namespace std;

class VectorDataset
{
private:
    vector<DataVector> dataset_;

public:
    VectorDataset(int size=0);                                              // Constructor
    VectorDataset(const VectorDataset &);                                   // Copy Constructor
    ~VectorDataset();                                                       // Destructor
    int getDatasetSize() const;                                             // Access size of dataset
    void setDatasetSize(int);                                               // Change size of dataset
    DataVector getVector(int);                                              // Access a vector in dataset
    void setVector(int, DataVector);                                        // Change a vector in dataset
    void ReadDataset(const std::string &);                                  // Create dataset from a CSV file
    int findVector(const DataVector &);                                     // Find a vector in the dataset
    void addVector(const DataVector &);                                     // Add a vector to dataset
    bool removeVector(const DataVector &);                                  // Remove a vector from dataset
    friend std::ostream &operator<<(std::ostream &, VectorDataset const &); // Print Dataset
};

// << - (friend function) To print the dateset vectors, seperated by newline (facilitates writing dataset into CSV file)
