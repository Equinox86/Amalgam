
#include "security.h"

bool amal_sec::genkey(){ 
	printf("Generating a Key\n");

	EVP_PKEY_CTX *ctx;
 	EVP_PKEY *pkey = NULL;

 	ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
 	if (!ctx){ 
 		perror("Error: ");
 		exit(0);
 	}
 	if (EVP_PKEY_keygen_init(ctx) <= 0)
 		perror("Error: ");
     	exit(0);
 	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0)
 		perror("Error: ");
     	exit(0);

 		/* Generate key */
 	if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
 		perror("Error: ");
    	exit(0);

 }