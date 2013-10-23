//
//  main.cpp
//  amazon
//
//  Created by Wenjie Yang on 7/25/13.
//  Copyright 2013 Lehigh University. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include "/Users/paul880828/Documents/workspace/GLUT/linkedlist2.1/linkedlist2/linkedList.h"
#include <queue>
#include <ext/hash_map>
#include <string>
#include <math.h>
#include <stack>
using namespace std;
using namespace __gnu_cxx;

typedef node<int> ListNode;

string s;


int findMaxFre(int a[],int n){
    hash_map< int, int> myMap;
    int count=0; 
    int number;    
    for (int i=0; i<n; i++){
    //    map<int,int>::iterator iter;
    
        myMap[a[i]]++; 
        if(myMap[a[i]]>count){
                 number=a[i];
                 count=myMap[a[i]];
                 }    //else myMap.insert(pair<int, int>(a[i],1));
    }
    /*
    pair<int,int> p(0,0);
    for( hash_map<int,int>::iterator iter=myMap.begin(); iter!=myMap.end(); iter++){
        if(iter->second>p.second){
            p.first=iter->first;
            p.second=iter->second;
        }
        
    }
    */    
    //cout<<p.first<<"  "<<p.second<<endl;
    //cout<<sizeof(char *)<<endl;
    return number;
}

double dist(pair<double, double> a) {
    return a.first*a.first+a.second*a.second;
}

vector<pair<double,double> > findMaxDistace(node<pair<double,double> > *head,int k){
    for(int i=0; i<k; i++){
        for(node<pair<double,double> > *temp=head; temp->next!=NULL; temp=temp->next){
            //double distance=(temp->data.first)*(temp->data.first)+(temp->data.second)*(temp->data.second);
            double distance1=dist(temp->data);
            double distance2=dist(temp->next->data);
            if (distance1<distance2){
            pair<double,double> t  =  temp->data;
                temp->data=temp->next->data;
                temp->next->data=t;   
            }
        }
    }
    node<pair<double,double> > * fast=head, *slow=head;
    for (int i=0; i<k; i++){
        fast=fast->next;
    }
    while (fast && fast->next){
        fast=fast->next;
        slow=slow->next;
    }
    
    vector<pair<double, double> > out;
    while (slow->next) {
        out.push_back(slow->next->data);
        slow=slow->next;
    }
    
    return out;
}

struct compare{
    bool operator() (const pair<double,double> &a, const pair<double,double> &b){
        return a.first*a.first+a.second*a.second<b.first*b.first+b.second*b.second;
    }
};

vector<pair<double, double> > findMaxDistanceByheap( node<pair<double, double> > *head, int k){
    
    priority_queue<pair<double,double>, vector<pair<double,double> >, compare> myMaxheap;
    vector<pair<double, double> > a;
    for (int i=0; i<k; i++){
        myMaxheap.push(head->data);
        head=head->next;
    }
    while(head){
        if(dist(myMaxheap.top())>dist(head->data)){ 
            myMaxheap.pop();
            myMaxheap.push(head->data);
        }
        head=head->next;
    }
    
    while(!myMaxheap.empty()){
        a.push_back(myMaxheap.top());
        myMaxheap.pop();
    }
    
    //vector<pair<double, double> > ::iterator iter;
    return a; 
}

int uniquePaths(int m, int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int sum=1;
    for (int i=1; i<m+n-2; i++)
        sum=sum*i;
    cout<<sum<<endl;
    int sumM=1;
    for(int i=1; i<m; i++)
        sumM=sumM*i;
    cout<<sumM<<endl;
    int sumN=1;        
    for (int i=1; i<n; i++)
        sumN=sumN*i;
    cout<<sumN<<endl;
    
    
    return sum/sumM/sumN;
}


vector<int> findIntersect(vector<int> a, vector<int> b){
    hash_map<int, bool> hm;
    vector<int> out;
    for (vector<int> ::iterator iter=a.begin(); iter!=a.end(); ++iter){
        if (hm[*iter]==false)
            hm[*iter]=true;
    }
    
    for (vector<int> ::iterator iter=b.begin(); iter!=b.end(); ++iter){
        if (hm[*iter]==true)
            out.push_back(*iter);
    }
    for (hash_map<int, bool>:: iterator iter=hm.begin(); iter!=hm.end(); iter++){
        cout<<"outting"<<iter->first<<endl;
    }
    
    return out;
}

struct testResult{
    int id;
    int date;
    int score;
};

/*
map <int, double> findMaxScore(vector<testResult> &results){
    map<int, vector<int> > scoreMap;
    map<int,double> output;
    for (vector<testResult>::iterator iter=results.begin(); iter!=results.end(); ++iter){
        map<int, vector<int> >::iterator it;
        if((it=scoreMap.find(iter->id))!=scoreMap.end()){
            it->second.push_back(iter->score);
        }
        else {
            pair<int,vector<int> > temp;
            temp.first=iter->id;
            temp.second.push_back(iter->score);
            scoreMap.insert(temp);
        }
            
    }
    
    for (map<int,vector<int> > ::iterator iter=scoreMap.begin(); iter!=scoreMap.end(); ++iter){
        priority_queue<int,vector<int>, std::greater<int> > minheap;
        for(int i=0; i<5; ++i){
            minheap.push(iter->second[i]);
        }
        for(int i=5; i<iter->second.size(); i++){
            if(iter->second[i]>minheap.top()){
                minheap.pop();
                minheap.push(iter->second[i]);
            }
                
        }
        int maxAverage=0;
        while(!minheap.empty()){
            maxAverage+=minheap.top();
            minheap.pop();
        }
        maxAverage=maxAverage/5;
        pair<int,double> a(iter->first,maxAverage);
        //output.insert(iter->first,maxAverage);
        output.insert(a);
    }
    
    return output;    
}
*/
string findOdd(string s, int i){

    string temp;
    for (int j=i,k=i; j>=0 &&k<s.length(); j--, k++){
        //string temp;
        if(s[j]==s[k]){
            temp=s.substr(j,k-j+1);
            
        }
        else return temp;
    }
    
    return temp;
}

string findEven(string s, int i){

    string temp;
    for (int j=i,k=i+1; j>=0 && k<s.length(); j--,k++){
        //string temp;
        if(s[j]==s[k]){
            temp=s.substr(j,k-j+1);
            
        }
        else return temp;
    }
    
    
    return temp;
}

string longestPalindrome(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    
    string longest("");
    for (int i=0; i<s.length(); i++){
        string odd=findOdd(s, i);
        string even=findEven(s,i);
        if (longest.length()<odd.length()){
            longest=odd;
        }
        if(longest.length()<even.length()){
            longest=even;
        }
        
        
    }
    
    return longest;
}


string longestCommonPrefix(vector<string> &strs) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (strs.size()==0)
        return "";
    size_t minSize=strs[0].size();
    for (vector<string> ::iterator iter=strs.begin(); iter!=strs.end(); ++iter){
        if (iter->length()<minSize){
            minSize=iter->length();
        }
    }
    
    string s("");
    for (int i=0; i<minSize; i++){
        char temp=strs[0][i];
        for (vector<string> ::iterator iter=strs.begin(); iter!=strs.end(); ++iter){
            if ((*iter)[i]!=temp)
                return s;
            
        }
        s=s+temp;
    }
    
    return s;
}

vector<vector<int> > generate(int numRows) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector <vector<int> > triangle;
    triangle.reserve(numRows);
    for (int i=0; i<numRows; i++){
        //vector<int> temp;
        //for(int j=0; j<i+1; j++)
        //temp.push_back(1);
        //temp.reserve(i+1);
        triangle[i].resize(i+1);
        //triangle.push_back(temp);
        for(int j=0; j<i+1; j++){
            triangle[j][0]=1;
            triangle[j][j]=1;
            //triangle[j].push_back(1);
        }
        
    }    
    if (numRows<=2){
        return triangle;
    }
    
    for(int i=2; i<numRows; i++){
        for(int j=1; j<i; j++)
            triangle[i][j]=triangle[i-1][j-1]+triangle[i-1][j];
    }
    
    return triangle;
}

vector<vector<int> > subsets(vector<int> &S) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > sub;
    vector<int> temp;
    
    for (int i=0; i<pow(2,S.size()); i++){
        int j=i;
        int pos=S.size();
        while (j>0){
            if (j%2){
                temp.push_back(S[pos-1]);
            }
            j=j>>1;            
            
        }
        sub.push_back(temp);
    }
    
    
    
}

bool sumOF(vector<int> result , vector<int> remain, int target){
   // result.i
}

bool sum4(vector<int> a, int target){
    for (vector<int>::iterator it=a.begin(); it!=a.end(); it++){
        //vector<int> temp=a;
        vector<int> result;
        result.push_back(*it);
        vector<int> remain=a;
        vector<int>::iterator iter=remain.begin();
        remain.erase(iter+(it-a.begin()));
        sumOF(result,remain,target);
    }
}

struct node1{
    int i;
    int j;
    int count;
    node1(int ii,int jj, int countt):i(ii),j(jj),count(countt){}
};

bool bfs(vector<vector<char> > &board, int i, int j,string word){
    vector<vector<bool> > mark (board.size(), vector<bool> (board[0].size(), false) );
    queue<node1> q;
    node1 a(i,j,0);
    mark[i][j]=true;
    q.push(a);
    while(!q.empty()){
        //pair<int,int> pop_temp=q.front();
        node1 pop_temp=q.front();
        
        q.pop();
        //int c=0;
        if (board[pop_temp.i][pop_temp.j]==word[pop_temp.count]&&word.length()>pop_temp.count){
            //mark[pop_temp.i][pop_temp.j]=true;
            if(pop_temp.count==word.length()-1)   
                return true;
            pop_temp.count++;
            
            //else continue;
            if(pop_temp.i-1>=0&&!mark[pop_temp.i-1][pop_temp.j]){
                node1 temp(pop_temp.i-1,pop_temp.j,pop_temp.count);
                q.push(temp);
               // mark[pop_temp.i-1][pop_temp.j]=true;
            }
            if(pop_temp.j-1>=0&&!mark[pop_temp.i][pop_temp.j-1]){
                node1 temp(pop_temp.i,pop_temp.j-1,pop_temp.count);    
                q.push(temp);
                //mark[pop_temp.i][pop_temp.j-1]=true;
            }
            if(pop_temp.i+1<board.size()&&!mark[pop_temp.i+1][pop_temp.j]){
                node1 temp(pop_temp.i+1,pop_temp.j,pop_temp.count);
                q.push(temp);
                //mark[pop_temp.i+1][pop_temp.j]=true;
                
            }
            if(pop_temp.j+1<board[0].size()&&!mark[pop_temp.i][pop_temp.j+1]){
                node1 temp(pop_temp.i,pop_temp.j+1,pop_temp.count);
                q.push(temp);
                //mark[pop_temp.i][pop_temp.j+1]=true;
            }
        }
        
    }
    
    return false;
}


bool exist(vector<vector<char> > &board, string word) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    for (int i=0; i<board.size(); i++){
        for (int j=0; j<board[0].size(); j++){
            //if (word[0]==board[i][j])
                if (bfs(board, i,j,word))
                    return true;
        }
        
    }
    return false;
}

int reverse(int x) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> digits;
    bool sign;
    if (x>0)
        sign=true;
    else false;
    while(x>0){
        digits.push_back(x%10);
        
    }
    int result=0;
    for(vector<int>::iterator it=digits.begin(); it!=digits.end(); ++it){
        result=*it*pow(10,digits.size()-(it-digits.begin())-1);
    }
    
    if (!sign)
        return result*-1;
    else return result;
}
     
int atoi(const char *str) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    bool sign=false;
    if (str[0]=='-')
        sign=false;
    else sign=true;
    if (!str)
        return 0;
    
    vector<int> digits;
    
    for(int i=0; str[i]!='/0'; i++){
        if(str[i]=='-'||str[i]=='+')
            continue;
        
        digits.push_back((int)(str[i]-'0'));
    }
    
    int result=0;
    for(vector<int> ::iterator it=digits.begin(); it!=digits.end(); ++it){
        result+=*it*pow(10,digits.size()-(it-digits.begin())-1);
    }
    
    if (sign)
        return result;
    else return result*-1;
}
int maxArea(vector<int> &height) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int i=0;
    int j=height.size()-1;
    int maxArea=0;
    int nextLeft=i;
    int nextRight=j;
    while (nextLeft<nextRight){
        
        int area=min(height[nextLeft],height[nextRight])*(nextRight-nextLeft);
        //if(maxArea<area)
        
        //maxArea=max(area,maxArea);
       // if (area>maxArea){
             i=nextLeft;
             j=nextRight;
        //}
        maxArea=max(area,maxArea);
        //int nextLeft=i;
        //int nextRight=j;
        while(height[nextLeft]<=height[i]){
            nextLeft++;
            if(nextLeft>=nextRight)
                return maxArea;
        }
        
        while(height[nextRight]<=height[j]){
            nextRight--;
            if(nextRight<=nextLeft)
                return maxArea;
        }
        
    }
    return maxArea;
}

string intToRoman(int num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function    
    hash_map<int,string> table;
    table[1]="I";
    table[5]="V";
    table[10]="X";
    table[50]="L";
    table[100]="C";
    table[500]="D";
    table[1000]="M";
    int count=0;
    int number=num;
    for( count=0; number!=0; count++)
    {
        number=number/10;
    }
    string result;
    for (int i=count; i!=0; i--){
        int digit=num/pow(10,i-1);
        int k=pow(10,i-1);
        num=num%k;
        if (digit==9)
            result=result+table[pow(10,i-1)]+table[pow(10,i)];
        else if (digit>=5 &&digit<9){
            result=result+table[5*pow(10,i-1)];
            for( int i=0; i<digit-5; i++)
                result=result+table[pow(10,i-1)];
        }
        else if (digit==4){
            result=result+table[pow(10,i-1)]+table[5*pow(10,i-1)];
        }
        else {
            for (int j=0; j<digit; j++)
                result+=table[pow(10,i-1)];    
            
        }
        
        
    }
    
    return result;
}

vector<vector<int> > threeSum(vector<int> &num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    //if(num.size()<3)
    
    sort(num.begin(),num.end());
    
    vector<vector<int> > result;
    if (num.size()<3)
        return result;
    for (vector<int> ::iterator iter=num.begin(); iter!=num.end();++iter){
        int current=*iter;
        int i=0; int j=num.size()-1;
        while(i<j){
            if (iter-num.begin()==i)
                i++;
            if(iter-num.begin()==j)
                j--;
            if(num[i]+num[j]==-(*iter)){
                vector<int> temp;
                temp.push_back(num[i]);
                temp.push_back(num[j]);
                temp.push_back(*iter);
                sort(temp.begin(),temp.end());
                bool flag=0;
                for(int g=0; g<result.size(); g++){
                    if(result[g][1]==temp[1]&&result[g][2]==temp[2]&&result[g][3]==temp[3])
                    {
                        i++;
                        j--;
                        flag=1;
                        break;
                    }
                }
                if(flag==0){
                    result.push_back(temp);
                    i++;
                    j--;
                }
            }
            
            else if (num[i]+num[j]>*iter)
                j--;
            else i++;
            
        }
    }
    
    return result;
}

void permutation(string digits, int pos, string input,vector<vector <char> > &number,vector<string> &result){
    if (digits=="")
        return;
    int count=number[(int)(digits[pos]-'0')].size();
    if (pos==digits.length()){
        result.push_back(input);
        return;
        
    }
    for(int i=0; i<count; i++){
        string temp=input;
        //number[digits[pos]][i];
        char * t=new char[2];
        t[0]=number[(int)(digits[pos]-'0')][i];
        t[1]='\0';
        //a[0]=number[digits[pos]][i];
        temp=temp+t;
        //string a(number[digits[pos]][i]);
        //temp=temp+a;//number[digits[pos]][i];
        permutation(digits,pos+1,temp,number,result);
        
    }
}
ListNode *reverseKGroup(ListNode *head, int k) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    ListNode *fast=head;
    ListNode *slow=head;
    ListNode *temp=head;
    ListNode *tail=head;
    if (!head)
        return NULL;
    if (k==1)
        return head;
    for(int i=0; i<k-1; i++){
        if(head&&head->next)
            head=head->next;
        else return 
            temp;
    }
    
    
    //slow->next=NULL;
    if(fast&&fast->next){
        temp=fast->next->next;
        fast=fast->next;
        slow->next=NULL;
    }
    if( !fast->next){
        fast->next=slow;
        return head;
    }
    while(fast){
        
        ListNode *temp2=slow;
        for(int i=0; i<k-1; i++){
            fast->next=slow;
            //temp->next=fast;
            slow=fast;
            fast=temp;
            if(temp->next)
                temp=temp->next;
            else  {slow->next=temp;
                
               return head;}
            
        }
        //if(temp2&&temp2)
        temp2->next=fast;
        slow=fast;
        fast=temp;
        temp=temp->next;
        //temp=slow;
        ListNode *probe=temp;
        for(int i=0; i<k-1; i++){
            
            if(probe&&probe->next)
                probe=probe->next;
            else    { 
                
                return head;
                
            }
        }
    }
    return head;
}
vector<string> letterCombinations(string digits) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    
    
    char k='a';
    vector<vector <char> > number;
    vector<char> temp(1,' ');
    number.push_back(temp);
    number.push_back(temp);
    for(int i=2; i<=6; i++){
        vector<char> temp;
        for (int j=0;j<3; j++)
            temp.push_back(k++);
        number.push_back(temp);
    }
    
    vector<char> temp2;
    temp2.push_back('p');
    temp2.push_back('q');
    temp2.push_back('r');
    temp2.push_back('s');
    number.push_back(temp2);
    
    temp2.clear();
    temp2.push_back('t');
    temp2.push_back('u');
    temp2.push_back('v');
    number.push_back(temp2);
    
    temp2.clear();
    temp2.push_back('w');
    temp2.push_back('x');
    temp2.push_back('y');
    temp2.push_back('z');
    number.push_back(temp2);
    
    
    
    string input("");
    vector<string> a;
    permutation(digits,0, input,number, a);   
    return a;
}

vector<int> findSubstring(string S, vector<string> &L) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int *mark =new int [S.length()];
    int length=L[0].length();
    
    for (vector<string>::iterator iter=L.begin(); iter!=L.end(); ++iter){
        for (int i=0; i<S.length(); i++){
            for(int j=0; j<iter->length(); j++){
                if(j==iter->length()-1 &&iter->c_str()[j]==S[i+j])
                    mark[i]=(iter-L.begin()+1);
                if(iter->c_str()[j]!=S[i+j])
                    break;
                
            }
            
            
        }
    }
    
    vector<int> result;
    for (int i=0; i<S.length(); i++){
        bool *flag=new bool[L.size()];
        for (int i=0; i<L.size(); i++)
            flag[i]=0;
        for (int j=0; j<L.size(); j++){
            if (mark[i+j*length]>0){
                cout<<"nodt"<<i+j*length<<endl;
                if(i+j*length>S.length()){
                    delete mark;
                    delete flag;
                    return result;
                }
                else 
                flag[mark[i+j*length]-1]=true;
            }
        }
        for (int k=0; k<L.size(); k++){
            if(flag[k]!=true)
                break;
            if(k==L.size()-1 &&flag[k]==true)
                result.push_back(i);
        }
        delete flag;
    }
    delete mark;
    return result;
}

int binSearch(int A[], int n, int target){
    int i=n/2;
    int L=0;
    int R=n-1;
    for(;L!=R; ){
        if(target>A[i]){
            L=i;
        i=(L+R)>>1;
        }
        else if(target<A[i]){
            R=i;
            i=(L+R)>>1;
        }
        else return i;
    }
    return -1;    
}

void dfs(vector<int> &candidates, vector<vector<int> > &result, int i,int target){
    stack<int> myStack;
    int sum=candidates[i];
    myStack.push(candidates[i]);
    int last=0;
    while(!myStack.empty()){
        bool flag=false;
        if(sum>target){
            last=myStack.top();
            myStack.pop();
            sum-=last;
        }
        else if(sum==target){
            vector<int> temp;
            stack<int> helper;
            while(!myStack.empty()){
                int k=myStack.top();
                helper.push(k);
                myStack.pop();
                //temp.push_back(k);
                
            }
            while(!helper.empty()){
                temp.push_back(helper.top());
                myStack.push(helper.top());
                helper.pop();
            }
            result.push_back(temp);
            last=myStack.top();
            sum-=myStack.top();
            myStack.pop();
            
        }
        
        else {
            while(candidates[i]<=last){
                if(i>candidates.size()-1){
                    last=myStack.top();
                    myStack.pop();
                    for(int j=0; j<candidates.size(); j++)
                        if(candidates[j]==last)
                            i=j+1;
                    sum-=last;
                    flag=true;
                    break;
                }
                else
                i++;
            }
            if(i<=candidates.size()-1&&flag==false){
            myStack.push(candidates[i]);
            sum+=candidates[i];
            }
        }
    }
    
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector< vector<int> > result;
    for (int i=0; i<candidates.size(); i++){
        if(candidates[i]<=target)
            dfs(candidates, result,i,target);
    }
    
    return result;
}

void printSum(int candidates[], int index[], int n) {
    for (int i = 1; i <= n; i++)
        cout << candidates[index[i]] << ((i == n) ? "" : "+");
    cout << endl;
}

void solve(int target, int sum, int candidates[], int sz, int index[], int n) {
    if (sum > target)
        return;
    if (sum == target)
        printSum(candidates, index, n);
    
    for (int i = index[n]; i < sz; i++) {
        index[n+1] = i;
        solve(target, sum + candidates[i], candidates, sz, index, n+1);
    }
}

void solve(int target, int candidates[], int sz) {
    int index[10000];
    index[0] = 0;
    solve(target, 0, candidates, sz, index, 0);
}

void sortColors(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int fast=0;
    int slow=0;
    int color=0;
    for(int i=0; i<n; i++){
        if(fast>=n){
            color++;
            fast=slow;        
        }
        if(color>2)
            return;
        if(A[fast]==color &&A[slow]!=color){
            int temp=A[slow];
            A[slow]=A[fast];
            A[fast]=temp;
            slow++;
            fast++;
        }
        else if(A[fast]==color&&A[slow]==color&&fast!=slow)
            slow++;
        else if(A[fast]==color&&A[slow]==color&&fast==slow){
            slow++;
            fast++;
        }
        else if(A[fast]!=color&&A[slow]!=color)
        {
            fast++;
            //slow++;
        }
        else if(A[fast]!=color&&A[slow]==color){
            slow++;
            fast++;
        }
        
    }
}

int minimumTotal(vector<vector<int> > &triangle) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > matrix;
    for(int i=0; i<triangle.size(); i++)
        matrix.push_back(vector<int> (triangle[i].size(),0));
    
    matrix[0][0]=triangle[0][0];
    for(int j=1;j<matrix.size();j++)
        for(int i=0; i<matrix[j].size(); i++){
            if(i==0)
                matrix[j][i]=matrix[j-1][i]+triangle[j][i];
            else if(i==matrix[j].size()-1)
                matrix[j][i]=matrix[j-1].back()+triangle[j].back();
            else
                matrix[j][i]=max(matrix[j-1][i-1],matrix[j-1][i])+triangle[j][i];
        }
    int temp=99999;
    for (int i=0; i<matrix.back().size(); i++){
        if (matrix.back()[i]<temp)
            temp=matrix.back()[i];
    }
    
    return temp;
    
}
int main (int argc, const char * argv[])
{   
    //hash_map <int,int > a;
    /*
    theList<pair<double, double> > test;
    for (int i=0; i<10; i++){
        pair<double,double>  t(i,10-i);    
    test.addHead(t);
    }
    vector< pair<double,double> >  s= findMaxDistanceByheap(test.head, 4);
    
    for (vector<pair<double,double> >::iterator iter=s.begin(); iter!=s.end(); ++iter){
        cout<<iter->first<<iter->first<<endl;
    }
    //int a[]={1,2,5,6,2,3,6,3,5,6,2,6,5,0,1};
    //cout<<sizeof(a)<<endl;
    //findMaxFre(a, 15);   
    // insert code here...
    
    //cout<<uniquePaths(10, 10)<<endl;
    vector<int> inter2;
    vector<int> inter1;
    
    inter1.push_back(1);
    inter1.push_back(3);
    inter1.push_back(4);
    inter1.push_back(5);
    inter1.push_back(6);
    
    inter2.push_back(3);
    inter2.push_back(5);
    inter2.push_back(1);
    inter2.push_back(8);
    cout<<inter2[3]<<endl;
    vector<int> out=findIntersect(inter1, inter2);
    
    for(vector<int>::iterator iter=out.begin(); iter!=out.end(); ++iter)
        cout<<*iter<<endl;
   
    vector<testResult> v;
    for(int i=0; i<100; i++){
        testResult a;
        a.id=i%10;
        a.date=5;
        a.score=i;
        v.push_back(a);
    }
    
    map<int,double> t=findMaxScore(v);
    for(map<int,double> ::iterator iter=t.begin(); iter!=t.end(); ++iter){
        cout<<iter->first<<" "<<iter->second<<endl;
    }
   
    std::cout << "Hello, World!\n";
    return 0;
     */
    /*
    int a[]={1,2,6,3,5,6,2,6,5,6,1,6,2,2};
    int b=findMaxFre(a, 12);
    cout<<b<<endl;
    string s=("12345");
    //cout<<s.substr(2,4);
    vector<int> tt;
    tt.push_back(1);
    tt[4]=4;
    tt[3]=3;
    tt[2]=2;
    for (int i=0; i<4; i++){
        cout<<tt[i];
    }
    cout<<endl;
   // vector<vector<int> > test=generate(1);
    //for(int i=0;i<1; i++){
    //    cout<<test[i][i]<<endl;
   // }
    //vector<int> te(1,1);
    //vector< vector<int> > tee=subsets(te);
  //  cout<<tee[0][0]<<endl;
    //vector<vector<char> > board(1,vector<char>(2,'ab'));
    //board.push_back(vector<char> (2)
    vector<vector<char> > board;
    vector<char> temp;
    temp.push_back('a');
    temp.push_back('b');
    board.push_back(temp);
    vector<char> temp1;
    temp1.push_back('c');
    temp1.push_back('d');
    board.push_back(temp1);
    string RE("asbd");
    //int ter=(int)RE[2];
    //cout<<reverse(1234)<<endl;
    vector<int> test1;
    test1.push_back(2);
    test1.push_back(0);
    test1.push_back(0);
    //test1.push_back(3);
    //cout<<maxArea(test1)<<endl;
    //cout<<intToRoman(1);
    string tet("32");
    //vector<string> ss=letterCombinations(tet);
    //threeSum(test1);
    //cout<<exist(board, "acdb")<<endl;
    //node<int> *head=new node<int> (1);
    //head->next=new node<int> (2);
    //head->next->next=new node<int> (3);
    node<int> *head;
    theList<int> myList;
    //myList.addHead(6);
    //myList.addHead(5);
    //myList.addHead(4);
    myList.addHead(3);
    myList.addHead(2);
    myList.addHead(1);
    //head->next->next->next=NULL;
    //head=reverseKGroup(myList.head, 2);
    //char *tttt="avcde";
    //cout<<*(tttt+1);
     */
    //string S("abaababbaba");
    //vector<string> L;
    //L.push_back("a");
    //L.push_back("b");
    //L.push_back("ab");
    //L.push_back("ding");
    //L.push_back("wing");            
    //L.push_back("ba");
    //vector<int> cdc=findSubstring(S, L);
    //for(vector<int>::iterator iter=cdc.begin();iter!=cdc.end();++iter)
    //    cout<<*iter<<endl;
    
    //int tese[]={1,2,3,4,5,6,7,8,9,10};
    //cout<<binSearch(tese,10, 7)<<endl;
    //vector<int> a;
    //a.push_back(1);
    //a.push_back(2);
  //  a.push_back(5);
   // a.push_back(7);
    
    //vector<vector<int> > b=combinationSum(a, 4);
    //for(int i=0; i<b[2].size(); i++)
    //    cout<<b[2][i]<<endl;
   // int aa[]={2,3,5,7};
    //solve(7, aa, 4);
    int t[]={2,1};
   // sortColors(t, 2);
    vector<vector<int> > tri(1,-1);
    vector<int> a;
    a.push_back(2);
    a.push_back(3);
    tri.push_back(a);
    vector<int> b;
    b.push_back(1);
    b.push_back(-1);
    b.push_back(-1);
    tri.push_back(b);
    minimumTotal(tri);
    

    return 0;
}

