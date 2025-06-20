#include<chrono>
#include"TreeIndex.h"
using namespace std;

TreeIndex* TreeIndex::Instance=nullptr;

int main()
{
    chrono::time_point<chrono::steady_clock> start, end;
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

    //create TreeIndex
    int choice;
    int minSize=10;
    cout<<"1.KD Tree\n2.RP Tree\nEnter choice: ";
    cin>>choice;
    cout<<"Enter minimim size of leaf node: ";
    cin>>minSize;
    start=chrono::steady_clock::now();
    if (choice==1)
        KDTreeIndex::GetInstance(trainData, minSize)->MakeTreeWrapper();
    else if (choice==2)
        RPTreeIndex::GetInstance(trainData, minSize)->MakeTreeWrapper();
    else
        throw invalid_argument("Invalid Choice");
    end = chrono::steady_clock::now();
    elapsed_seconds = end - start;
    cout << "Making Tree Index: " << elapsed_seconds.count() << "sec" << endl;

    int k;
    cout<<"Enter k:";
    cin>>k;
    if(k<=0) throw invalid_argument("K must be positive");
    if(k>trainSz) throw out_of_range("K can't be greater than the training-dataset size");

    int n;
    cout<<"Find KNN for how many vectors : \n";
    cin>>n;
    if(n<=0) throw invalid_argument("N must be positive");
    if(n>testSz) throw out_of_range("N can't be greater than the test-dataset size");

    //Finding KNN for each of n vectors
    start=chrono::steady_clock::now();
    for(int i=0;i<n;i++)
    {
        cout<<"Test Vector "<<i+1<<"\n";
        ofstream output;
        output.open("testvector_"+to_string(i+1)+".csv");
        output<<TreeIndex::GetInstance()->SearchWrapper(testData.getVector(i),k);
        output.close();
    }
    end=chrono::steady_clock::now();
    elapsed_seconds=end-start;
    cout<<"Time for training "<<n<<" vectors: " <<elapsed_seconds.count()<<"sec\n";

    delete TreeIndex::GetInstance();
}

//g++ DataVector.cpp VectorDataset.cpp TreeIndex.cpp nearest_neighbour1.cpp