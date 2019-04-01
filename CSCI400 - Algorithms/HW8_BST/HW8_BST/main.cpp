//
//  main.cpp
//  HW8_BST
//
//  Created by Cu Hauw Hung on 11/16/17.
//  Copyright © 2017 Cu Hauw Hung. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <numeric>
#include <queue>
#include <stack>

using namespace std;

struct CustomType{
    string name;
    double prob;
};

// TREE SECTION
struct TreeNode{
    string name;
    TreeNode *left;
    TreeNode *right;
};

queue <string> savedOutputs;
TreeNode *root;

TreeNode *tree (int i, int j, vector<vector<double>> R, vector<CustomType> Data){

    TreeNode *p = new TreeNode();
    
    int k=R[i][j];
    if(k==0){
        return nullptr;
    }
    
    else{
        p -> name= Data[k-1].name;
        p -> left = tree(i, k-1, R, Data);
        p -> right = tree(k, j, R, Data);
    }

    return p;
}

void TreeInfo(){
    queue<TreeNode> q;
    cout << "Root of the tree: " << root -> name << endl;
    
    q.push(*root);
    
    while (!q.empty()){
        TreeNode n=q.front();
        q.pop();

        cout << "Left child of " << n.name << ": ";
        if (n.left!=NULL){
            cout << n.left->name << endl;
            q.push(*n.left);
        }
        else if (n.left==NULL)
            cout << "nil" << endl;

        cout << "Right child of " << n.name << ": ";
        if (n.right!=NULL){
            cout << n.right->name << endl;
            q.push(*n.right);
        }
        else if (n.right==NULL)
            cout << "nil" << endl;

    }
    
}

void printTree(TreeNode* p, int indent){
    if(p != NULL) {
        cout<< setw(indent) << p->name << endl;
        if(p->left) printTree(p->left, indent-5);
        if(p->right) printTree(p->right, indent+5);
    }
}

int height(TreeNode *root){
    int l,r;
    if (root == NULL){
        return NULL;
    }
    else {
        l=height(root -> left);
        r=height(root -> right);
    }
    
    if( l >= r){
        return (l + 1);
    }
    
    return (r + 1);
}

void Display(TreeNode *root){
    
//    int hi = height(root);
//    cout << hi << endl;
    printTree(root, 3*height(root));
    cout << " ###################### " << endl;
    TreeInfo();
}

void OutputValues(vector<vector<double>> Temp){
    for (int a=0; a<Temp.size(); a++){
        for (int b=0; b<Temp[a].size(); b++){
            if (b!=Temp.size()-1){
                cout << Temp[a][b] << " -- ";
            }
            else{
                cout << Temp[a][b];
            }
        }
        cout << endl;
    }
}

double CalcSumOf(vector<CustomType> p, int i, int j){
    double sum = 0;
    for (int m=i; m<j; m++){
        sum=sum+p[m].prob;
    }
    return sum;
}

double FindMin(vector<vector<double>> &A, int i, int j, double &KRecord){
    double minValue=1;
    for (int k=i; k<j; k++){
        
        if (A[i][k]+A[k+1][j] < minValue){
            minValue=A[i][k]+A[k+1][j];
            KRecord=k+1;
        }
    }
    return minValue;
}

double optimalBinarySearchTree(int n, vector<vector<double>> &A, vector<vector<double>> &R, vector<CustomType> p){
    
    double AST, K=0;
    
    for (int i=0; i<R.size(); i++){
        for (int j=0; j<R[i].size() ; j++){
            if (j==i+1){
                R[i][j]= double (i+1);
                A[i][j]=p[i].prob;
            }
        }
    }
    
    for (int diagonal=1; diagonal<=n-1; diagonal++){
        for (int i=0; i<n-diagonal; i++){
            int j = i+diagonal+1;
            A[i][j]= FindMin(A, i, j, K) + CalcSumOf(p, i, j);
            R[i][j]= K;
        }
    }
    return AST=A[0][n];
}

bool my_cmp(const CustomType& a, const CustomType& b){
    return a.prob > b.prob;
}

int main() {
    
    int i=0, number_of_keys=0;
    vector<CustomType> Data;
    vector<vector<double>> A; vector<vector<double>> R;

    double tempDouble;
    string tempString;
    
    // Obtain information
    cout << "Enter the total number of keys: " << endl;
    cin >> number_of_keys;

	string *name_of_keys; double *prob_of_keys;
	name_of_keys = new string[number_of_keys];
	prob_of_keys = new double[number_of_keys];


    cout << "Enter the 3 keys separated by at least 1 space" << endl;
    do{
        cin >> tempString;
        name_of_keys[i]=tempString;
        i++;
    } while(i<number_of_keys);
    
    i=0;
    
    cout << "Enter the probability for the 3 keys separated by at least 1 space" << endl;
    do{
        cin >> tempDouble;
        prob_of_keys[i]=tempDouble;
        i++;
    } while(i<number_of_keys);
    
    A.resize(number_of_keys+1); R.resize(number_of_keys+1);
    for (int i = 0; i <number_of_keys+1; i++){
        A[i].resize(number_of_keys+1);
        R[i].resize(number_of_keys+1);
    }

//    name_of_keys[0]="Don";
//    name_of_keys[1]="Isabelle";
//    name_of_keys[2]="Ralph";
//    name_of_keys[3]="Wally";
//
//    prob_of_keys[0]=0.375;
//    prob_of_keys[1]=0.375;
//    prob_of_keys[2]=0.125;
//    prob_of_keys[3]=0.125;

//    name_of_keys[0]="John";
//    name_of_keys[1]="Adam";
//    name_of_keys[2]="Mary";
//
//    prob_of_keys[0]=0.2;
//    prob_of_keys[1]=0.7;
//    prob_of_keys[2]=0.1;

    for (int i=0; i<number_of_keys; i++){
        CustomType temp1;
        temp1.name=name_of_keys[i];
        temp1.prob=prob_of_keys[i];
        Data.push_back(temp1);
    }
    
    sort(Data.begin(), Data.end(), my_cmp);
    
    double AST = optimalBinarySearchTree(number_of_keys, A, R, Data);
    
    cout << "Here is the A and R matrix respsectively: " << endl;
    OutputValues(A);
    cout << " ###################### " << endl;
    OutputValues(R);
    cout << " ###################### " << endl;
    root = tree(0, number_of_keys, R, Data);
    Display(root);
    cout << " ###################### " << endl;

    cout << "The AST is: " << AST << endl;

	system("pause");
}

