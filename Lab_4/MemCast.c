#include <stdio.h>

int main() {
	int i; // int as loop counter
	int four_ints[4]; //array of 4 int
	char* four_c; //pointer to char in mem

//initialize integer array
	for(i = 0; i < 4; i++) //set all ints to 2
        four_ints[i] = 2;

	printf("%x\n", four_ints[0]); //prints first integer in hexaadecimal

//Type casting - changes how a pointer accesses memory; not move the data.
    four_c = (char*)four_ints; //four_c point to the first byte of the integer array

// Change the bytes - Writes four characters into the first four bytes of the array.
	for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII value of 'A' is 65 or 0x41 in Hex.
    
    // Add your code for the exercises here:

	//Print the changed integers - Shows how changing bytes affects the integer values.
	printf("%x\n", four_ints[0]); //first int in array
	printf("%x\n", four_ints[1]); 

	//Print the starting addresses
	printf("four_ints address: %p\n", (void*)four_ints); // adress of first element of int array
	printf("four_c address: %p\n", (void*)four_c);
	
	//Print each integer's address and value
	for(i = 0; i < 4; i++) { //increaase by one after each loop
    printf("four_ints[%d] address: %p value: %x\n",
           i, (void*)&four_ints[i], four_ints[i]);
	}
	
	//Print each character's address and value - Each successive character address is one byte apart.
	for(i = 0; i < 4; i++) {
    printf("four_c[%d] address: %p value: %x\n",
           i, (void*)&four_c[i], four_c[i]);
}

	return 0;
}