#include "math-base.h"

unsigned long long int E;
unsigned long long int D;

// TODO generate or hardcode P and Q variables.
/* If difficult just hardcode it.
And initialize "p" and "q" */
void generatePQ(unsigned long long int *P, unsigned long long int *Q);

// TODO select public key
/* Select the public exponent e ∈ {1, 2, . . . ,Φ(n) − 1}
such that
gcd(e,Φ(n)) = 1.
This function will work directly with global variables
*/
void choosePublicKey(unsigned long long int phiOfN);

// TODO compute private key
/* d · e ≡ modΦ(n)
This function will work directly with global variables
*/
void computePrivateKey(unsigned long long int phiOfN);

void generateKeys() {
  const unsigned long long int P;
  const unsigned long long int Q;
  const unsigned long long int *pointerP = &P;
  const unsigned long long int *pointerQ = &Q;
  generatePQ(pointerP, pointerQ);

  unsigned long long int N = P * Q;
  unsigned long long int phiOfN = phi(N);
  choosePublicKey(phiOfN);
  computePrivateKey(phiOfN);
}