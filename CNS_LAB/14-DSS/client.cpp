# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int connectToServer(const char* ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port),inet_addr(ip)};

    if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 )
    {
        cout << "\nRun server program first." << endl; 
        exit(0);
    }
    else
        cout << "\nClient is connected to Server." << endl; 
    return sock;
}

long mod(long a, long b)
{
	return a >= 0 ? (a%b) : b-(abs(a)%b) ;
}

long powermod(long a, long b, long  c)
{
    long res=1;
    for(int i=0; i<b; i++)
    {
        res = (res * a) % c;
    }
    return res;
}

long findDetInverse(long r2,long r1)
{
	long t1=0,t2=1;
    long N=r1;
	while(r2!=0)
	{
		long q=r1/r2;
		long r=r1-(q*r2);
		long t=t1-(q*t2);
		r1=r2;
		r2=r;
		t1=t2;
		t2=t;
	}
	return mod(t1,N);
}

long H(long M)
{
    return (M ^ 1234); //hash key = 1234 
}

int main()
{
	//get ip and port and connect to server
    char ip[50]; 
    cout << "\nEnter server's IP address: "; 
    cin >> ip;
    int port;    
    cout << "Enter port : "; 
    cin >> port;
    
    //connect to server socket
    int sock = connectToServer(ip, port);

    long p,q,g,y,M,r,s;//prime,prime divisor,g,public key,message,signatures

    recv(sock, &p, sizeof(p), 0);
    recv(sock, &q, sizeof(q), 0);
    recv(sock, &g, sizeof(g), 0);		
    recv(sock, &y, sizeof(y), 0);
    recv(sock, &M, sizeof(M), 0);
    recv(sock, &r, sizeof(r), 0);
    recv(sock, &s, sizeof(s), 0);	

    cout << "Received p =  " << p << endl;
    cout << "Received q =  " << q << endl;
    cout << "Received g =  " << g << endl;
    cout << "Received y =  " << y << endl;
    cout << "Received M'=  " << M << endl;
    cout << "Received r' = " << r << endl;
    cout << "Received s' = " << s << endl;

	//get hashvalue
    long hashval = H(M) ; 
    cout << "\nH(M') = " << hashval << endl;

    //Verifying
    long w = findDetInverse(s,q) % q;  
    cout << "w = " << w << endl;
    
    long u1 = (hashval * w) % q;
    long u2 = (r * w) % q;
    
    long v = ((powermod(g,u1,p)*powermod(y,u2,p)) %p) %q;  
    cout<<"v = "<<v<<endl;
    
    if(v == r) 
    	cout<<"\nDigital Signature Verified. " << endl << endl;
    else	   
    	cout<<"\nDigital Signature is invalid !!!" << endl << endl;	
}
