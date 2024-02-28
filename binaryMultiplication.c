#include <stdio.h>
#include <stdlib.h>

/**
 * @brief count the number of bit of given integer
 * 
 * @param n integer
 * @return int : number of bit
 */
int numberOfBit(int n)
{
    int count = 0;
    while (n > 0)
    {
        count++;
        n >>= 1; // rightshifting the bit
    }
    return count;
}


/**
 * @brief multiply two integer using partial sum approach in bit level
 * 
 * 
 * @param m Multiplicand
 * @param q Multipler
 * @return int : multiplication of m and q
 */
int  intBinMultiplication(int m, int q)
{
    int ans = 0;
    int nq = numberOfBit( q );
    while (q > 0)
    {
        if(q & 1) // checking whether right bit is 1 or 0
            ans += m << nq;
        ans >>= 1; // Right shifting ans by 1
        q >>= 1; // Right shifting multipler by 1
    }
    return ans;
}


/**
 * @brief convert integer to binary
 * save the binary bit in binaryNumber array
 * 
 * @param n integer to convert
 * @return int* : returning the base address of binaryNumber array
 */
int *intToBin(int n)
{
    int numOfBit = numberOfBit(n);
    int *binaryNumber = (int*)malloc(numOfBit * sizeof(int));
    while(n > 0)
    {
        binaryNumber[numOfBit - 1] = n % 2;
        n /= 2;
        numOfBit--;
    }
    return binaryNumber;
}


/**
 * @brief Right shifting array by 1
 * 
 * 
 * @param arr array to right shift 
 * @param size size of the array
 * @param LeftBit for A(resultant array) leftBit is C and C is reassign to 0 || for Q(multipler) leftBit is the RightBit of A before shifting
 * @return void 
 */
void RightShift(int *arr, int size, int *LeftBit)
{
    for(int i = size - 1; i > 0; i--)
        arr[i] = arr[i-1];
    arr[0] = (*LeftBit);
    (*LeftBit) = 0; // for C = 0
}


/**
 * @brief Implementing FullAdder to add n bit binary numbers
 * A : one bit from first binary number
 * B : one bit from second binary number
 * Cn-1 : previous carry after adding A and B (Cn-1 is 0 for first time)
 * add = (A xor B) xor Cn-1
 * Cn = ( A and B) or Cn-1 and (A or B)
 * 
 * @param a (A register : size bit) binary number (resultant)  (this is the return option)
 * @param m (M register: size bit) binary number of multiplicand
 * @param size size of multiplicand (size of multiplicand and size of A (resutlt binary number) is same (I make this both same for easy use))
 * @param c Original carry regiter for storing carry to right shift with A register
 */
void Fulladder(int  *a,  int *m, int size, int *c)
{
    int carry = 0;
    for(int i = size - 1; i >= 0; i-- )
    {
        int tempA = a[i];
        a[i] = (tempA ^ m[i]) ^ carry; // Full adder addition formula
        carry = ( tempA & m[i]) | (carry & (tempA | m[i]));  // Full adder carry formula
    }
    (*c) = carry;

}

/**
 * @brief implimenting the partial binary multiplication with custom function of FullAdder and RightShift
 * 
 * 
 * @param m  Multiplicand
 * @param q  Multipler
 * @param size size of the resultand array (will return this size for future traversal of resultand arrary)
 * @return int* returning the base address of resultant binary number
 */
int *binMultiplication(int m, int q)
{
    int *result;
    int numOfBit_m = numberOfBit(m);
    int numOfBit_q = numberOfBit(q);
    int *mInBinary = intToBin(m);
    int *qInBinary = intToBin(q);
    int *A = (int*)malloc(numOfBit_m * sizeof(int));
    int C = 0;
    int nq = numOfBit_q; //nq for chekcing nq > 0
    while(nq > 0)
    {
        if(qInBinary[numOfBit_q - 1] == 1)
            Fulladder(A, mInBinary, numOfBit_m, &C);
        
        int rightBit = A[numOfBit_m - 1];
        RightShift(A, numOfBit_m, &C);
        RightShift(qInBinary, numOfBit_q, &rightBit);
        nq--;
    }
    result = (int*)malloc((numOfBit_m + numOfBit_q) * sizeof(int));
    for(int i = 0; i < (numOfBit_m); i++)
    {
        result[i] = A[i];
    }
    for(int i = numOfBit_m; i < (numOfBit_m + numOfBit_q); i++)
    {
        result[i] = qInBinary[i - numOfBit_m];
    }
    return result;
}

/**
 * @brief Convert binary number to integer
 * 
 * @param binaryNumber  binary number array
 * @param size size of the binary number
 * @return int resultant integer number
 */
int binaryToInt(int *binaryNumber, int size)
{
    int result = 0;
    for(int i = 0; i < size; i++)
    {
        result = result * 2 + binaryNumber[i];
    }
    return result;
}

/**
 * @brief print the binary number
 * 
 * @param binaryNumber binary number array
 * @param size size of the binary number
 * @return void
 */
void printBinary(int *binaryNumber, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d", binaryNumber[i]);
    printf("\n");
}


int main()
{
    int Wantcontinue;
    int multiplicand = 11, multipler = 13;
    // int size = 0;
    do {
        printf("Enter the multiplicand and multipler: ");
        scanf("%d %d", &multiplicand, &multipler);

        printf("Multiplication of %d and %d is: %d\n", multiplicand, multipler, intBinMultiplication(multiplicand, multipler));

        printf("Binary of %d (multiplicand): ", multiplicand);
        printBinary(intToBin(multiplicand), numberOfBit(multiplicand));

        printf("Binary of %d (multipler): ", multipler);
        printBinary(intToBin(multipler), numberOfBit(multipler));

        printf("Resultant Binary Number: ");
        printBinary(binMultiplication(multiplicand, multipler), numberOfBit(multiplicand) + numberOfBit(multipler));
        printf("Resultant integer number: %d\n", binaryToInt(binMultiplication(multiplicand, multipler), numberOfBit(multiplicand) + numberOfBit(multipler)));


        printf("Do you want to continue (1 for Continue/ Type anything to Quiut ):  ");
        scanf("%d", &Wantcontinue);
    }while(Wantcontinue == 1);
    return 0;
}