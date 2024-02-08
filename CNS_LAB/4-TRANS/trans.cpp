#include <bits/stdc++.h>
using namespace std;
string encrypt(string pt, string key)
{
    string ct = "";
    
    int cols = key.length();
    while(pt.length()%cols!=0)
        pt+='x';
    int rows = pt.length() / cols;
    char mat[rows][cols];
    int k = 0;
    cout << "\nEncryption Matrix :" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
                cout << (mat[i][j] = pt[k++]) << " ";

        }
        cout << endl;
    }
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
            ct += mat[j][key.find(i + '1')];
    }
    cout << "\nEncrypted text \t: " << ct << endl;
    return ct;
}
string decrypt(string ct, string key)
{
    string pt = "";
    int cols = key.length();
    int rows = ct.length() /cols;
    char mat[rows][cols];
    int k = 0;
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            mat[j][key.find(i + '1')] = ct[k++];
           
        }
    }
    cout << "\nDecryption Matrix :" << endl;
    for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << mat[i][j] << " ";
                pt += mat[i][j];
            }
            cout << endl;
        }
    cout << "\nDecrypted text \t: " << pt << endl;
    return pt;
}
string format(string key)
{   string sortkey=key,newkey="";
    sort(sortkey.begin(),sortkey.end());
    for(int i=0;i<key.length();i++)
    {
        newkey+=to_string(sortkey.find(key[i])+1);
    }
    
    return newkey;
}int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    string plaintext, key,k, ciphertext, decryptext;
    cout << "Enter text : ";
    cin >> plaintext;
    cout << "Enter key : ";
    cin >> k;   
    key=format(k);
    
    int i = 1;
    while (n > 0)
    {
        cout << "LEVEL " << i << endl;
        ciphertext = encrypt(plaintext, key);
        plaintext = ciphertext;
        n--;
        i++;
    }
    n = i - 1, i = 1;
    while (n > 0)
    {
        cout << "LEVEL " << i << endl;
        decryptext = decrypt(ciphertext, key);
        ciphertext = decryptext;
        n--;
        i++;
    }
    return 0;
}

/*#include<bits/stdc++.h>
using namespace std;

map<int,int> keyMap;

void setPermutationOrder(string key)
{             
    for(int i=0; i < key.length(); i++)
    {
        keyMap[key[i]] = i;
    }
}

string encryptMessage(string msg,string key)
{
    int row,col,j;
    string cipher = "";
    
    col = key.length(); 
    row = msg.length()/col; 
    
    if (msg.length() % col)
        row += 1;

    char matrix[row][col];

    for (int i=0,k=0; i < row; i++)
    {
        for (int j=0; j<col; )
        {
            if(msg[k] == '\0')
            {
                matrix[i][j] = '_';     
                j++;
            }
            
            if( isalpha(msg[k]) || msg[k]==' ')
            { 
                matrix[i][j] = msg[k];
                j++;
            }
            k++;
        }
    }

    for (map<int,int>::iterator ii = keyMap.begin(); ii!=keyMap.end(); ++ii)
    {
        j=ii->second;

        for (int i=0; i<row; i++)
        {
            if( isalpha(matrix[i][j]) || matrix[i][j]==' ' || matrix[i][j]=='_')
                cipher += matrix[i][j];
        }
    }
    cout<<"Encryption Matrix : "<<endl;
        for(int i=0;i<key.size();i++)
        {
            cout<<key[i]<<"\t";
        }
        cout<<endl;
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                cout<<matrix[i][j]<<"\t";
            }
            cout<<endl;
        }

    return cipher;
}
string decryptMessage(string cipher,string key)
{
    int col = key.length();

    int row = cipher.length()/col;
    char cipherMat[row][col];

    for (int j=0,k=0; j<col; j++)
        for (int i=0; i<row; i++)
            cipherMat[i][j] = cipher[k++];
    
    int index = 0;
    for( map<int,int>::iterator ii=keyMap.begin(); ii!=keyMap.end(); ++ii)
        ii->second = index++;

    char decCipher[row][col];
    map<int,int>::iterator ii=keyMap.begin();
    int k = 0;
    for (int l=0,j; key[l]!='\0'; k++)
    {
        j = keyMap[key[l++]];
        for (int i=0; i<row; i++)
        {
            decCipher[i][k]=cipherMat[i][j];
        }
    }

    string msg = "";
    for (int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(decCipher[i][j] != '_')
                msg += decCipher[i][j];
        }
    }
    cout<<"Decryption Matrix : "<<endl;
        for(int i=0;i<key.size();i++)
        {
            cout<<key[i]<<"\t";
        }
        cout<<endl;
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                cout<<decCipher[i][j]<<"\t";
            }
            cout<<endl;
        }
    return msg;
}

int main(void)
{
    
    string msg; 
    string key,cip,cipher;
    int n;
    cout<<"Enter the value of n : ";
    cin>>n;
    cout<<"Enter the plain text : ";
    cin>>msg;
    string temp = msg;
    cout<<"Enter the key : ";
    cin>>key;
    setPermutationOrder(key);
    cout<<key<<endl;
    for(int i=0;i<n;i++)
    {
        cip = encryptMessage(msg,key);
        msg = cip;
    }
    cout << "Message after"<<n<<" Encryptions : " << cip << endl;
    for(int i=0;i<n;i++)
    {
        string dec = decryptMessage(cip,key);
        cip=dec;
    }
    cout << "Message after " <<n<<" decryptions : " << temp << endl;

    return 0;
}*/