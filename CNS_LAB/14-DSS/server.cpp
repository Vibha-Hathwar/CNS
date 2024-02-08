# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int createServer(int port)  // TCP connection
{
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};

    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "\nServer Online. Waiting for client...." << endl;

    listen(sersock, 5);
    int sock = accept(sersock, NULL, NULL);
    cout << "Connection Established." << endl;
    return sock;
}

long randInRange(long low, long high) // excluding high and low
{
    return rand()%(high-(low+1)) + (low+1) ;
}

long mod(long a, long b)
{
	return a >= 0 ? (a%b) : b-(abs(a)%b) ;
}

long powermod(long a, long b, long  c)
{
    long res=1;
    for(int i=0; i<b; i++)
        res = (res * a) % c;
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

long H(long M) // Hash Function
{
	return (M ^ 1234); //hash key = 1234 
}

int main()
{
    //getting port number
    int port;  
    cout << "\nEnter port : "; 
    cin >> port;
    
    //create server socket
    int sock = createServer(port);

	//get prime number
    long p, q;
    cout << "\nEnter a large prime number, p : ";   
    cin >> p; 
    cout << "Enter a prime number, q (p-1 divisible by q & q>2) : "; 
    cin >> q;
    if( (p-1)%q != 0 || q<3) 
    { 
    	cout << "\nInvalid input\n"; 
    	exit(-1); 
    }

	//getting messsage
	long M; 
    cout<<"Enter message, M = "; 
    cin >> M;

	//calculating hashvalue of message
	long hashval;
    hashval = H(M); 
    cout << "\nH(M) = " << hashval << endl;

	//calculate g
	long g;
    long h;
    srand(time(NULL));
    do
    {
        h = randInRange(1, p-1);        // 1 < h < p-1
        g = powermod(h,(p-1)/q, p);	    //g > 1
    }while(g<=1);
    cout << "g    = " << g;

	//compute server keys
    long k, x, y;
    x = randInRange(1, q);  
    cout << "\nServer's Private key, x = " << x;
    y = powermod(g, x, p);  
    cout << "\nServer's Public  key, y = " << y;
    k = randInRange(1, q);  
    cout << "\nSecret key, k = " << k << endl;

    //Signing
    long r = powermod(g, k, p) % q;
    
    long s = (findDetInverse(k,q) * (hashval + x*r )) % q; 
    cout << "\nServer's Signature {r,s} = {" << r << ", " << s << "}" << endl;

    send(sock, &p, sizeof(p), 0);
    send(sock, &q, sizeof(q), 0);	
    send(sock, &g, sizeof(g), 0);	
    send(sock, &y, sizeof(y), 0);	
    send(sock, &M, sizeof(M), 0);
    send(sock, &r, sizeof(r), 0);
    send(sock, &s, sizeof(s), 0);	

    cout << "\nSent p, q, g, and public key to client.";
    cout <<"\nSent message along with signature to client." << endl << endl;
}
