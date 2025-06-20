#include"TreeIndex.h"

///TreeNode

TreeNode::TreeNode(): left(NULL),right(NULL) {}
TreeNode::TreeNode(vector<int> arr,TreeNode* l,TreeNode* r): left(l),right(r),indices(arr) {}
TreeNode::~TreeNode()
{
    delete left;
    delete right;
}

///TrreeIndex

TreeIndex::TreeIndex(VectorDataset& arr,int size): dataSet(arr),minSize(size),root(NULL) {}
TreeIndex::~TreeIndex() {delete root;}

void TreeIndex::MakeTree(TreeNode* root)
{
    auto rule=ChooseRule(root->indices);
    root->dir=rule.first;
    root->split=rule.second;

    vector<int> leftvec,rightvec;
    int numVDS=root->indices.size();
    for(int i=0;i<numVDS;i++)
    {
        if(dataSet.getVector(root->indices[i])*(root->dir) <= root->split)
        {
            leftvec.push_back(root->indices[i]);
        }
        else rightvec.push_back(root->indices[i]);
    }

    if(leftvec.size()<minSize||rightvec.size()<minSize) return;

    root->left=new TreeNode(leftvec);
    root->right=new TreeNode(rightvec);
    MakeTree(root->left);
    MakeTree(root->right);
}

void TreeIndex::Search(TreeNode* root,const DataVector& point,priority_queue<pair<double,int>>& pq,int k)
{
    if(root==NULL) return;
    if(root->left==NULL&&root->right==NULL)
    {
        for(int idx:root->indices)
        {
            double neigh_dist=dataSet.getVector(idx).dist(point);
            if(pq.size()<k)
            {
                pq.push({neigh_dist,idx});
                continue;
            }
            if(pq.top().first>neigh_dist)
            {
                pq.pop();
                pq.push({neigh_dist,idx});
            }
        }
        return;
    }

    if(root->dir*point<=root->split)
    {
        Search(root->left,point,pq,k);
        if(pq.size()<k||abs(root->dir*point)<pq.top().first)
        {
            Search(root->right,point,pq,k);
        }
    }
    else{
        Search(root->right,point,pq,k);
        if(pq.size()<k||abs(root->dir*point)<pq.top().first)
        {
            Search(root->left,point,pq,k);
        }
    }
}

TreeIndex* TreeIndex::GetInstance()
{
    if(Instance==nullptr)
    {
        throw invalid_argument("Construct a tree index first");
    }
    return Instance;
}

void TreeIndex::MakeTreeWrapper()
{
    delete root;
    int sz=dataSet.getDatasetSize();
    vector<int> idx(sz);
    for(int i=0;i<sz;i++)
    {
        idx[i]=i;
    }
    root=new TreeNode(idx);
    MakeTree(root);
}

VectorDataset TreeIndex::SearchWrapper(const DataVector& point,int k)
{
    priority_queue<pair<double,int>> pq;
    Search(root,point,pq,k);
    VectorDataset ANN(k);

    int i=1;
    while(!pq.empty())
    {
        ANN.setVector(k-i,dataSet.getVector(pq.top().second));
        pq.pop();
        i++;
    }
    return ANN;
}

void TreeIndex::AddData(const DataVector& temp)
{
    dataSet.addVector(temp);
    MakeTreeWrapper();
}

void TreeIndex::RemoveData(const DataVector& temp)
{
    bool isRemoved=dataSet.removeVector(temp);
    if(isRemoved==false) return;
    MakeTreeWrapper();
}

//KDTreeIndex

KDTreeIndex::KDTreeIndex(VectorDataset& VDS,int size): TreeIndex(VDS,size) {}
KDTreeIndex::~KDTreeIndex() {}

TreeIndex* KDTreeIndex::GetInstance(VectorDataset& VDS,int size)
{
    if(Instance==nullptr)
    {
        Instance=new KDTreeIndex(VDS,size);
    }
    return Instance;
}

pair<DataVector,int> KDTreeIndex::ChooseRule(const vector<int>& idx)
{
    int numVDS=idx.size(),dim=dataSet.getVector(0).getDimension();
    //coordinate with maximum spread
    vector<double> upperRange(dim,INT_MIN),lowerRange(dim,INT_MAX);
    for(int i=0;i<numVDS;i++)
    {
        DataVector temp=dataSet.getVector(idx[i]);
        for(int j=0;j<dim;j++)
        {
            upperRange[j]=max(upperRange[j],temp.getCoordinate(j));
            lowerRange[j]=min(lowerRange[j],temp.getCoordinate(j));
        }
    }
    double maxSpread=-1,coord=0;
    for(int j=0;j<dim;j++)
    {
        double spread=upperRange[j]-lowerRange[j];
        if(spread>maxSpread)
        {
            maxSpread=spread;
            coord=j;
        }
    }
    //
    vector<double> allCoord(numVDS);
    for(int i=0;i<numVDS;i++)
    {
        allCoord[i]=dataSet.getVector(idx[i]).getCoordinate(coord);
    }
    sort(allCoord.begin(),allCoord.end());

    DataVector dir(dim);
    dir.setCoordinate(coord,1);
    double median=allCoord[numVDS/2];

    return {dir,median};
}

//RPTree

RPTreeIndex::RPTreeIndex(VectorDataset& VDS,int size): TreeIndex(VDS,size) {}
RPTreeIndex::~RPTreeIndex() {}

TreeIndex* RPTreeIndex::GetInstance(VectorDataset& VDS,int size)
{
    if(Instance==nullptr)
    {
        Instance=new RPTreeIndex(VDS,size);
    }
    return Instance;
}

pair<DataVector,int> RPTreeIndex::ChooseRule(const vector<int>& idx)
{
    int numVDS=idx.size(),dim=dataSet.getVector(0).getDimension();
    //generate random vector
    vector<double> random_v(dim);
    for(int i=0;i<dim;i++)
    {
        random_v[i]=2*((double)rand()/RAND_MAX)-1;//[-1,1]
    }
    double norm=DataVector(random_v).norm();
    for(int j=0;j<dim;j++)
    {
        random_v[j]/=norm;
    }
    DataVector dir(random_v);

    DataVector x=dataSet.getVector(idx[rand()%numVDS]);//choose a random vector
    vector<double> allCord(numVDS);
    double maxdist=0;
    for(int i=0;i<numVDS;i++)
    {
        maxdist=max(maxdist,x.dist(dataSet.getVector(idx[i])));
        allCord[i]=dataSet.getVector(idx[i])*dir;
    }

    sort(allCord.begin(),allCord.end());
    double delta=(2*((double)rand()/RAND_MAX)-1)*6*(maxdist/sqrt(dim));

    return {dir,allCord[numVDS/2]+delta};
}
