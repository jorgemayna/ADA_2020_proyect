#include <iostream>
#include <vector>
using namespace std;
vector<pair<int,int> > bloques_0(string s,int p){
  vector<pair<int,int> > R;  
  bool in = false;
  pair<int,int> temp;
  for(int i =0; i < p; i++){
    if (s[i]=='1' && !in){
      in = true;
      temp.first = i;
    }
    if (s[i]=='0' && in){
      in = false;
      temp.second = i-1;
      R.push_back(temp);      
    }
    if (i+1==p && in){
      temp.second = i;
      R.push_back(temp);
    }
  }
  return R;
}

vector<pair<int,int> > bloques_1(string s,int p){
  vector<pair<int,int> > R;  
  int cont = 0;  
  for(int i =0; i < p; i++){
    if (s[i]=='1'){
      cont++;            
      if(s[i+1] == '0' || i+1 == p){
        R.push_back(make_pair(i+1-cont,i));
        cont = 0;    
      }      
    }    
  }
  return R;
}

vector<pair<int,int> > bloques_2(string s,int p){
  vector<pair<int,int> > R;  
  int first;  
  for(int i =0; i < p; i++){
    if (s[i]=='1'){
      first=i;            
      while(s[i] == '1')i++;          
      R.push_back(make_pair(first,i-1));
    }    
  }
  return R;
}

vector<pair<pair<int,int>,int >> bloques_final(string s,int p){
  vector<pair<pair<int,int>,int >> R;  
  int first;  
  for(int i =0; i < p; i++){
    if (s[i]=='1'){
      first=i;            
      while(s[i] == '1')i++;          
      R.push_back(make_pair(make_pair(first,i-1),i-first));
    }    
  }
  return R;
}