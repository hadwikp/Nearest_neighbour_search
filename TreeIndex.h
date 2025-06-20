#include"VectorDataset.h"
#include<utility>
#include<algorithm>
#include<queue>
#include<climits>
#include<random>
using namespace std;


class TreeNode
{
    public:
        TreeNode* left;
        TreeNode* right;
        vector<int> indices;
        DataVector dir;
        double split;

        TreeNode();
        TreeNode(vector<int>,TreeNode* left=NULL,TreeNode* right=NULL);
        ~TreeNode();
};

class TreeIndex
{
    protected:
        VectorDataset dataSet;
        TreeNode* root;
        int minSize;
        static TreeIndex *Instance;

        TreeIndex(VectorDataset&,int);
        void MakeTree(TreeNode*);
        void Search(TreeNode*,const DataVector&, priority_queue<pair<double,int>>&, int);

    public:
        virtual ~TreeIndex();
        static TreeIndex* GetInstance();
        void MakeTreeWrapper();
        VectorDataset SearchWrapper(const DataVector&, int);
        void AddData(const DataVector&);
        void RemoveData(const DataVector&);
        virtual pair<DataVector,int> ChooseRule(const vector<int>&)=0;
};


class KDTreeIndex:public TreeIndex
{
    public:
        static TreeIndex* GetInstance(VectorDataset& ,int);
        pair<DataVector,int> ChooseRule(const vector<int>&);

    private:
        KDTreeIndex(VectorDataset&, int);
        ~KDTreeIndex();
};


class RPTreeIndex:public TreeIndex
{
    public:
        static TreeIndex* GetInstance(VectorDataset& ,int);
        pair<DataVector,int> ChooseRule(const vector<int>&);
    private:
        RPTreeIndex(VectorDataset&, int);
        ~RPTreeIndex();
};

enum ANN_Index
{
    KD=1,RP=2
};