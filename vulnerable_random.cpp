using namespace std;

#include <cmath>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>


/* 
    Assume a Diffie-Hellman Key exchange for any real world use.
    The following program uses a random value for the private key
    and emulates the key exchange steps to create a public key,
    a private shared key, and encrypt a message. For the purposes of demonstration
    the publicly available information is written into a public_information.txt.
    This emulates what a malicious actor would see if they ran a packet sniffer during
    the communication process.
*/

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

int main(int argc, char* argv[]){

    string secret_message;

    // check if user ran program without commandline arguments
    if (argc == 2){
        secret_message = argv[1];
    } 
    else{
        printf("Please provide a message to encrypt as an argument\n");
        return 0;
    }
    
    ofstream myfile;
    
    long long int prime_number_P, prime_number_G, private_key, public_key, shared_private_key;
    // open file to write public information to a file
    // Only write values that a 3rd party can see, and the encrypted message
    myfile.open ("public_information.txt");
    if(myfile.is_open()){
        // the exchange of prime numbers is public and is emulated by having the values printed to a file
        prime_number_P = 23;
        myfile << prime_number_P << endl;

        prime_number_G = 5;
        myfile << prime_number_G << endl;

        // use current time as seed, which is also unsafe due to a malicious actor
        // being able to guess it based on things like when the program ran
        // or when a message was sent
        srand(time(0));

        // A random private key is generated with the restriction of it being 
        // less than the prime number
        private_key = rand()%(prime_number_P-1);

        // A public key is generated and shared with the intended recipient of
        // the encrypted message
        public_key = calculate_key(prime_number_G, private_key, prime_number_P);
        myfile << public_key << endl;

        // A shared_private_key key is generated and and used to encrypt 
        // the message
        shared_private_key = calculate_key(public_key, private_key, prime_number_P);


        for(char& letter : secret_message) {
            // simple encryption by adding the shared private key's
            // value to every char in the secret message
            letter += shared_private_key;
        }

        myfile << secret_message.c_str() << endl;
        myfile.close();
    }
    else 
        printf("Unable to open file");

    return 0;
}