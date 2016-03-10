#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> InsertTwo(vector<int > &a,vector<int > &b){
    vector<int> ret;
    for(int i=0,j=0;i<a.size() && j<b.size();){
        if(a[i]<b[j]){
            i++;
        }else if (a[i]>b[j]){
            j++;
        }else{
            ret.push_back(a[i]);
            i++;
            j++;
        }
    }
    return ret;
}

int main2(int argc, const char * argv[]) {
    int n;
    vector<vector<int> > arr(3);
    for(int i=0;i<3;i++){
        cin >> n;
        arr[i].assign(n, 0);
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
        sort(arr[i].begin(),arr[i].end());
    }
    vector<int> tmp = InsertTwo(arr[0], arr[1]);
    vector<int> ret = InsertTwo(tmp, arr[2]);
    for(int i=0;i<ret.size();i++){
        cout<< ret[i];
        if(i<ret.size()-1){
            cout <<" ";
        }else{
            cout << endl;
        }
    }
    
    
    return 0;
}


vector<int> getVersionArray(string str,string pattern){
    string::size_type pos;
    vector<int> result;
    str+=pattern;//扩展字符串以方便操作
    int len = str.size();
    
    for(int i=0; i<str.size(); i++)
    {
        pos=str.find(pattern,i);
        if(pos<len)
        {
            string s=str.substr(i,pos-i);
            int tmp = atoi(s.c_str());
            result.push_back(tmp);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

bool static compare0(const vector<int> &a,const vector<int> &b){
    auto lena=a.size();
    auto lenb=b.size();
    
//    cout << a[0] <<"." << a[1]<<"." << a[2]<<endl;
//    cout << b[0] <<"." << b[1]<<"." << b[2]<<endl;
//    cout << "com"<<endl;
    
    if(a[0]<b[0]){
        return true;
    }else if(a[0]>b[0]){
        return false;
    }
    
    if(a[1]<b[1]){
        return true;
    }else if(a[1]>b[1]){
        return false;
    }
    
    if(lena==2 && lenb==2){
        return true;
    }else if(lena==3 && lenb==3){
        return a[2]<=b[2];
    }else if(lena==3){
        return false;
    }else if(lenb==3){
        return true;
    }else {
        return true;
    }
}

/*
 7
 10.3.5
 9.2.16
 11.4.20
 11.3.14
 2.1.12
 12.4
 13.5
 
 7
 10.3.5
 9.2.16
 11.4.20
 11.4.14
 2.1.12
 12.7
 13.5
 */

int main(int argc, const char * argv[]) {
    int n;
    string version;
    vector<int> ver;
    vector<vector<int>> vers;
    cin>>n;
    for(int i=0;i<n;i++){
        cin >> version;
        ver=getVersionArray(version, ".");
        vers.push_back(ver);
//        cout << version<< endl;
    }
    sort(vers.begin(),vers.end(),compare0);  //sort不通过，stable_sort通过
    
    for(int i=vers.size()-1;i>=0;i--){
        if(vers[i][1]%2==0){
            cout<< vers[i][0]<<"."<<vers[i][1];
            if(vers[i].size()==3){
                cout<<"."<<vers[i][2];
            }
            cout <<endl;
            return 0;
        }
    }
    
    cout<<"no stable available"<<endl;
    return 0;
}
