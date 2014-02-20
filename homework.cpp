// homework.cpp
// bit shifting
// John Beedlow
// 2/16/14
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <new>
#include <math.h>

void convert(unsigned int, char*); 
int sub_msk(struct Add, struct Add, struct Add);

// Structure to hold binary values
struct Add {
	char* bin_1;
	char* bin_2;
	char* bin_3;
	char* bin_4;
	int	  subnet;

	Add() {
		bin_1 = new char[8];
		bin_2 = new char[8];
		bin_3 = new char[8];
		bin_4 = new char[8];
	}
	void del() {
		delete [] bin_1;
		delete [] bin_2;
		delete [] bin_3;
		delete [] bin_4;
	}

};

int main() {
	
	struct Add IP_1, mask, IP_2;
	unsigned int IP_int1[3], mask_int[3], IP_int2[3];
	
	// Asks user input for address
	// Converts input to binary
	//
	printf("Please input the first IP address: \n");
	scanf("%d.%d.%d.%d", &IP_int1[0] , &IP_int1[1], &IP_int1[2], &IP_int1[3]); IP_int1[4] = 0;
	convert(IP_int1[0], IP_1.bin_1); IP_1.bin_1[8] = '\0';
	convert(IP_int1[1], IP_1.bin_2); IP_1.bin_2[8] = '\0';
	convert(IP_int1[2], IP_1.bin_3); IP_1.bin_3[8] = '\0';
	convert(IP_int1[3], IP_1.bin_4); IP_1.bin_4[8] = '\0';
	

	printf("Please input the subnet mask: \n");
	scanf("%d.%d.%d.%d", &mask_int[0] , &mask_int[1], &mask_int[2], &mask_int[3]); mask_int[4] = 0;
	convert(mask_int[0], mask.bin_1); mask.bin_1[8] = '\0';
	convert(mask_int[1], mask.bin_2); mask.bin_2[8] = '\0';
	convert(mask_int[2], mask.bin_3); mask.bin_3[8] = '\0';
	convert(mask_int[3], mask.bin_4); mask.bin_4[8] = '\0';

	printf("Please input the second IP address: \n");
	scanf("%d.%d.%d.%d", &IP_int2[0] , &IP_int2[1], &IP_int2[2], &IP_int2[3]); IP_int2[4] = 0;
	convert(IP_int2[0], IP_2.bin_1); IP_2.bin_1[8] = '\0';
	convert(IP_int2[1], IP_2.bin_2); IP_2.bin_2[8] = '\0';
	convert(IP_int2[2], IP_2.bin_3); IP_2.bin_3[8] = '\0';
	convert(IP_int2[3], IP_2.bin_4); IP_2.bin_4[8] = '\0';
	
	// Prints addresses in binary
	printf("\n Binary value of first IP Address: %s %s %s %s", IP_1.bin_1, IP_1.bin_2, IP_1.bin_3, IP_1.bin_4);
	printf("\n Binary value of first IP Address: %s %s %s %s", mask.bin_1, mask.bin_2, mask.bin_3, mask.bin_4);
	printf("\nBinary value of second IP Address: %s %s %s %s", IP_2.bin_1, IP_2.bin_2, IP_2.bin_3, IP_2.bin_4);

	// Applies subnet mask
	printf("\n Now checking with subnet mask");
	int foo;
	foo = sub_msk(IP_1, mask, IP_2);
	if(foo==1) 
		printf("\n They are in the same subnet.");
	else
		printf("\n They are not in the same subnet.");
	
	IP_1.del(); mask.del(); IP_2.del();
	return 0;
}

// Converts int value to binary stored in a char array
//
void convert(unsigned int val, char* buff) {
	char t_buff[8];
	for (int i = 0; i < 8; ++i) {
		t_buff[i] = '0' + (val & (1 << i) ? 1 : 0);
	}
	for (int a = 0, b = 7; a < 8; ++a, --b) {
		buff[a] = t_buff[b];
	}

}

// Applies subnet mask check
//
int sub_msk(Add add1, Add mask, Add add2) {
	int s = 1;
	for(int i = 0; i < 8; ++i) {
		if(add1.bin_1[i] != add2.bin_1[i])
			s = 0;
	}

	for(int i = 0; i < 8; ++i) {
		if(add1.bin_2[i] != add2.bin_2[i])
			s = 0;
	}
	//////////////////////////////////////////////////////////////////
	// Excluded b/c subnet mask is only for first two digits
	/*
	for(int i = 0; i < 8; ++i) {
		if(add1.bin_3[i] != add2.bin_3[i])
			s = 0;

	}

	for(int i = 0; i < 8; ++i) {
		if(add1.bin_4[i] != add2.bin_4[i])
			s = 0;
	}
	*/
	//////////////////////////////////////////////////////////////////
	if(s == 1) 
		return 1;
	else
		return 0;

}