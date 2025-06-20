#include"VectorDataset.h"
#include<chrono>
#include<queue>
#include<utility>
using namespace std;

//return a dataset containing K nearest neighbours of the given vector
VectorDataset KNN_function(DataVector test_vector,VectorDataset& train_data,int k)
{
    priority_queue<pair<double,int>> pq;
    int datasetSize=train_data.getDatasetSize();

    VectorDataset KNN(k);

    for(int i=0;i<datasetSize;i++)
    {
        double neighbour_dist=test_vector.dist(train_data.getVector(i));
        if(pq.size()<k)
        {
            pq.push({neighbour_dist,i});
            continue;
        }
        if(pq.top().first>neighbour_dist)
        {
            pq.pop();
            pq.push({neighbour_dist,i});
        }
    }
    int i=1;
    while(!pq.empty())
    {
        KNN.setVector(k-i,train_data.getVector(pq.top().second));
        pq.pop();
        i++;
    }
    return KNN;
}

int main()
{
    chrono::time_point<chrono::steady_clock> start,end;
    chrono::duration<double> elapsed_seconds;

    //Read and create test data
    start=chrono::steady_clock::now();
    VectorDataset testData;
    testData.ReadDataset("test.csv");
    int testSz=testData.getDatasetSize();
    end=chrono::steady_clock::now();
    elapsed_seconds=end-start;
    cout<<"Reading Test Data: "<<elapsed_seconds.count()<<"sec\tSize:"<<testSz<<"\n";

    //Read and create train data
    start=chrono::steady_clock::now();
    VectorDataset trainData;
    trainData.ReadDataset("train.csv");
    int trainSz=trainData.getDatasetSize();
    end=chrono::steady_clock::now();
    elapsed_seconds=end-start;
    cout<<"Reading Train Data: "<<elapsed_seconds.count()<<"sec\tSize:"<<trainSz<<"\n";

    int k;
    cout<<"Enter Value of K: ";
    cin>>k;
    if(k<=0)
    {
        cout<<"K must be positive\n";
        exit(0);
    }
    if(k>trainSz)
    {
        cout<<"K can't be grater than Training dataset size:"<<trainSz<<"\n";
        exit(0);
    }
    
    int n;
    cout<<"Find KNN from how many vectors?";
    cin>>n;
    if(n<=0)
    {
        cout<<"N must be positive\n";
    }
    if(n>testSz)
    {
        cout<<"N can't be grater than Testing dataset size:"<<testSz<<"\n";
        exit(0);
    }

    cout<<"Computing KNN from first "<<n<<"test Vectors\n";
    start=chrono::steady_clock::now();
    for(int i=0;i<n;i++)
    {
        cout<<"Test Vector "<<i+1<<"\n";
        ofstream output;
        output.open("testvector"+to_string(i+1)+".csv");
        output<<KNN_function(testData.getVector(i),trainData,k);
        output.close();
    }
    end=chrono::steady_clock::now();
    elapsed_seconds=end-start;
    cout<<"Time for Training "<<n<<" vectors: "<<elapsed_seconds.count()<<"sec\n";

}

//g++ DataVector.cpp VectorDataset.cpp nearest_neighbour.cpp