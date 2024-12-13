# CWE 330 Vulnerable code and attack

## Description of the vulnerable code  

The code emulates a weaker [Diffie-Hellman](https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange) key exchange to encrypt a message provided as a command line argument. For the purposes of demonstration the shared private key is generated using the program's own public key to simplify the calculation. 

The exchange contains public information that a malicious actor would be able to see namely:
- The prime `prime_number_P` which is used for modulus
- `prime_number_G` which is used as a base
- `public_key`
- `secret_message` after it is encrypted

This public information is written to a file to emulate what a malicious actor running a packet sniffer would be able to see in a real world scenario

The vulnerable code generates a random private key between 0 and (`prime_number_P` - 1), and uses it to generate the public key and the shared private key. 

The vulnerability being exploited is that the random private key falls in a predicatable range, so the exploit code simply tries all values in the range between 0 and (`prime_number_P` - 1) until a match is found, thus beating the randomness of the vulnerable code.

## How to compile and run the code

Make sure you are in a directory you can create and read files from

1. Simple run `make` in the Repo's directory.
2. run the executable with a commandline argument as follows: 

```./vulnerable_random "Secret to be encrypted"```

Where the argument is a string that you want to encrypt, you should see a `public_information.txt` file created with the public information and encrypted message in it.

## How to compile and run the exploit

Make sure you are in a directory you can create and read files from.

1. Make sure to run the ./vulnerable_random binary in the same directory and that it generated a `public_information.txt` file  
2. Run `make` in the Repo's directory.
3. run the executable as follows: `./exploit`

You should see the shared private key and the original message printed to STDOUT.
