#include"DataVector.h"

DataVector::DataVector(int size): dimension(size),v(size,0) {}
DataVector::DataVector(vector<double> &arr): dimension(arr.size()),v(arr) {}
DataVector::DataVector(const DataVector& temp): dimension(temp.dimension), v(temp.v) {}

DataVector::~DataVector() {}

DataVector& DataVector::operator=(const DataVector& temp)
{
    if(this!=&temp)
    {
        dimension=temp.dimension;
        v=temp.v;
    }
    return *this;
}

int DataVector::getDimension()const
{
    return dimension;
}

void DataVector::setDimension(int size)
{
    dimension=size;
    v.resize(size,0);
}

double DataVector::getCoordinate(int idx)
{
    if(idx>=dimension)
    {
        cout<<"Index out of bound"<<"\n";
        exit(0);
    }
    return v[idx];
}

void DataVector::setCoordinate(int idx,double value)
{
    if(idx>=dimension)
    {
        cout<<"Index out of bound"<<"\n";
        exit(0);
    }
    v[idx]=value;
}

DataVector DataVector::operator+(const DataVector& temp)
{
    if(dimension!=temp.dimension)
    {
        cout<<"+ : can't add vectors of different sizes\n";
        exit(0);
    }
    DataVector newVector(dimension);
    for(int i=0;i<dimension;i++)
    {
        newVector.v[i]=v[i]+temp.v[i];
    }
    return newVector;
}

DataVector DataVector::operator-(const DataVector& temp)
{
    if(dimension!=temp.dimension)
    {
        cout<<"- : can't subtract vectors of different sizes\n";
        exit(0);
    }
    DataVector newVector(dimension);
    for(int i=0;i<dimension;i++)
    {
        newVector.v[i]=v[i]-temp.v[i];
    }
    return newVector;
}

double DataVector::operator*(const DataVector& temp)
{
    if(dimension!=temp.dimension)
    {
        cout<<"* : can't multiply vectors of different sizes\n";
        exit(0);
    }
    double dotProduct=0;
    for(int i=0;i<dimension;i++)
    {
        dotProduct+=v[i]*temp.v[i];
    }
    return dotProduct;
}

double DataVector::norm()
{
    return sqrt(*this * *this);
}

double DataVector::dist(const DataVector& temp)
{
    if(dimension!=temp.dimension)
    {
        cout<<"can't find distancebetween vectors of different sizes\n";
        exit(0);
    }
    return (*this-temp).norm();
}

bool DataVector::operator==(const DataVector& temp)
{
    if(dimension!=temp.dimension)
    {
        return false;
    }
    for(int i=0;i<dimension;i++)
    {
        if(v[i]!=temp.v[i]) return false;
    }
    return true;
}

ostream& operator<<(ostream& os,const DataVector& other)
{
    int size=other.dimension;
    for(int i=0;i<size;i++)
    {
        os<<other.v[i];
        if(i<size-1) os<<",";
        else os<<"\n";
    }
    return os;
}
