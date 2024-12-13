#if ! defined(STORED_SECRET) 
#error STORED_SECRET not defined
#endif

using namespace std;

#include <cmath>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>


// Assume a Diffie-Hellman Key exchange for any real world use
// Based on https://www.geeksforgeeks.org/implementation-diffie-hellman-algorithm/


// function to calculate key by getting the value of G ^ secret mod P
long long int calculate_key(long long int G, long long int secret,
                    long long int P)
{
    if (secret == 1)
        return G;

    else
        return (((long long int)pow(G, secret)) % P);
}

int main(){

    ofstream myfile;
    string secret_message = string(STORED_SECRET);

    long long int prime_number_P, prime_number_G, private_key, public_key, shared_private_key;

    myfile.open ("public_information.txt");
    if(myfile.is_open()){
        // the exchange of prime numbers is public and is emulated by having the values printed to a file
        prime_number_P = 23;
        myfile << prime_number_P << endl;

        prime_number_G = 5;
        myfile << prime_number_G << endl;

        srand(time(0));

        // A random private key is generated with the restriction of it being
        private_key = rand()%(prime_number_P-1);


        public_key = calculate_key(prime_number_G, private_key, prime_number_P);
        myfile << public_key << endl;


        shared_private_key = calculate_key(public_key, private_key, prime_number_P);

        // printf("%lld\n", shared_private_key);


        for(char& letter : secret_message) {
            letter += shared_private_key;
        }

        myfile << secret_message.c_str() << endl;
        myfile.close();
    }
    else 
        printf("Unable to open file");

    return 0;
}