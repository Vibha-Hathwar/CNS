#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;
const int ch_MAX = 26;

string RandomString(int ch)
{
    set<char> st;
    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z' };
    string result = "";
    for (int i = 0;; i++){
        if(st.size()==26) break;
          char k=alpha[rand() % ch_MAX];
        if(st.find(k)==st.end())
            result = result + k;
        st.insert(k);    
    }
    return result;
}
string encrypt(string s,map<char,char> m){
    string e="";
    for(auto i:s)
        if(isalpha(i))
            e+=m[i];
        else e+=" ";
    return e;
}
void freq(string p,string c){
    map<char,int> f;
    map<char,char> mc;
    for(int i=0;i<p.size();i++)
        mc[p[i]]=c[i];
    for(auto i:p)
        if(isalpha(i))
            f[i]++;
    cout<<"Freq\t"<<"Plaintext\t"<<"Ciphertext\t"<<endl;
    for(auto i:m)
        cout<<i.second<<"\t\t"<<i.first<<"\t\t"<<mc[i.first]<<endl;
}
int main()
{
   map<char,char> m;
   srand(time(NULL));
   int ch = 26;
   string r=RandomString(ch);
   string alp="abcdefghijklmnopqrstuvwxyz"; 
   for(int i=0;i<alp.size();i++)
       m[alp[i]]=r[i];
   cout<<endl<<"Table : "<<endl<<"Alphabet set : \t\t";
   for(auto i:m)
       cout<<i.first<<" ";
   cout<<endl;
   cout<<"Selected key : \t\t";
   for(auto i:m)
       cout<<i.second<<" ";
   cout<<endl;
   ifstream myfile ("plaintext.txt");
   string p="";   
   if ( myfile.is_open() ) 
       while(myfile)
           p+=myfile.get();
   cout<<"Plain text (from file) : "<<p<<endl;
   string c=encrypt(p,m);
   cout<<"Encrypted text (to file) : "<<c<<endl<<endl;
   fstream file("ciphertext.txt", ios_base::out);
   if(!file.is_open())
   {
       cout<<"Unable to open the file.\n";
       return 0;
   }
   freq(p,c);
   file<<c;
   file.close();
   return 0;
}
