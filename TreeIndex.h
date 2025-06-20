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