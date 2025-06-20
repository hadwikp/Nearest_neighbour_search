#include"VectorDataset.h"

VectorDataset::VectorDataset(int size): dataset_(size,0) {}
VectorDataset::VectorDataset(const VectorDataset& temp): dataset_(temp.dataset_) {}
VectorDataset::~VectorDataset() {}

int VectorDataset::getDatasetSize() const
{
    return (int)dataset_.size();
}

void VectorDataset::setDatasetSize(int size)
{
    dataset_.resize(size,0);
}

DataVector VectorDataset::getVector(int idx)
{
    if(idx>=dataset_.size()&&idx<0)
    {
        cout<<"Out of bounds of dataset\n";
        exit(0);
    }
    return dataset_[idx];
}

void VectorDataset::setVector(int idx,DataVector temp)
{
    if(idx>=dataset_.size()&&idx<0)
    {
        cout<<"Out of bounds of dataset\n";
        exit(0);
    }
    dataset_[idx]=temp;
}

void VectorDataset::ReadDataset(const string& CSVFile)
{
    ifstream input{CSVFile};
    string line;
    getline(input,line);
    for(;getline(input,line);)
    {
        stringstream ss(line);
        vector<string> row;
        for(string data;getline(ss,data,',');)
        {
            row.push_back(move(data));
        }
        int dim=row.size();
        DataVector temp(dim);
        for(int i=0;i<dim;i++)
        {
            temp.setCoordinate(i,stod(row[i]));
        }
        dataset_.push_back(temp);
    }
    input.close();
}

int VectorDataset::findVector(const DataVector& temp)
{
    int size=dataset_.size();
    for(int i=0;i<size;i++)
    {
        if(dataset_[i]==temp) return i;
    }
    return -1;
}

void VectorDataset::addVector(const DataVector& temp)
{
    if(dataset_.size()!=0&&dataset_[0].getDimension()!=temp.getDimension())
    {
        cout<<"addVector: can't add vector of different dimensions to the dataset\n";
        exit(0);
    }
    int sz=dataset_.size();
    dataset_.resize(sz+1);
    dataset_[sz]=temp;
}

bool VectorDataset::removeVector(const DataVector& temp)
{
    int idx=findVector(temp);
    if(idx==-1) return false;
    
    int sz=dataset_.size();
    for(int i=idx;i<sz-1;i++)
    {
        dataset_[i]=dataset_[i+1];
    }
    dataset_.resize(sz-1);
    return true;
}

ostream& operator<<(ostream& os,const VectorDataset& temp)
{
    int sz=temp.dataset_.size();
    for(int i=0;i<sz;i++)
    {
        os<<temp.dataset_[i]<<"\n";
    }
    return os;
}