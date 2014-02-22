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
#include <vector>

char* convert(unsigned int);
int sub_msk(std::vector<char*>, std::vector<char*>, std::vector<char*>);

int main() {
		// Vectors of char arrays to hold binary addresses
		// Int arrays to hold decimal addresses
		//
		std::vector<char*> IP_1;
		std::vector<char*> mask;
		std::vector<char*> IP_2;
		unsigned int IP_int1[4], mask_int[4], IP_int2[4];

		// Asks user for address input
		// Converts decimal addresses to binary
		//
		printf("Please input the first IP address: \n");
		scanf("%d.%d.%d.%d", &IP_int1[0], &IP_int1[1], &IP_int1[2], &IP_int1[3]);
		IP_1.push_back(convert(IP_int1[0]));
		IP_1.push_back(convert(IP_int1[1]));
		IP_1.push_back(convert(IP_int1[2]));
		IP_1.push_back(convert(IP_int1[3]));

		printf("Please input the subnet mask: \n");
		scanf("%d.%d.%d.%d", &mask_int[0], &mask_int[1], &mask_int[2], &mask_int[3]);
		mask.push_back(convert(mask_int[0]));
		mask.push_back(convert(mask_int[1]));
		mask.push_back(convert(mask_int[2]));
		mask.push_back(convert(mask_int[3]));

		printf("Please input the second IP address: \n");
		scanf("%d.%d.%d.%d", &IP_int2[0], &IP_int2[1], &IP_int2[2], &IP_int2[3]);
		IP_2.push_back(convert(IP_int2[0]));
		IP_2.push_back(convert(IP_int2[1]));
		IP_2.push_back(convert(IP_int2[2]));
		IP_2.push_back(convert(IP_int2[3]));

		// Checks to see if address are in the same subnet
		// Prints out status
		//
		int sub = 0;
		sub = sub_msk(IP_1, mask, IP_2);
		if(sub == 1) 
			printf("The two IP addresses are in the same subnet.\n");
		else
			printf("The two IP addresses are not in the same subnet.\n");

		return 0;
}

// Converts int value to binary stored in a char array
//
char* convert(unsigned int val) {
	char* t_buff = new char [8];
	char* r_buff = new char [8];
	for (int i = 0; i < 8; ++i) {
		t_buff[i] = '0' + (val & (1 << i) ? 1 : 0);
	}
	for (int a = 0, b = 7; a < 8; ++a, --b) {
		r_buff[a] = t_buff[b];
	}
	r_buff[8] = '\0';
	return r_buff;
}

// Applies subnet mask check
//
int sub_msk(std::vector<char*> add1, std::vector<char*> mask, std::vector<char*> add2) {
	int ret = 1;
	char* temp1 = new char[8];
	char* temp2 = new char[8];

	for (int r = 0; r < 8; ++r) {
		if((mask[0][r] == '1') && (mask[0][r] == add1[0][r]))
			temp1[r] = '1';
		else 
			temp1[r] = '0';
		if((mask[0][r] == '1') && (mask[0][r] == add2[0][r]))
			temp2[r] = '1';
		else 
			temp2[r] = '0';
	}

	temp1[8] = '\0'; temp2[8] = '\0'; 

	if((temp1[0] == temp2[0]) && (temp1[1] == temp2[1]) && (temp1[2] == temp2[2]) && (temp1[3] == temp2[3]) &&
		(temp1[4] == temp2[4]) && (temp1[5] == temp2[5]) && (temp1[6] == temp2[6]) && (temp1[7] == temp2[7])) 
		ret = 1;
	else 
		ret = 0;

	return ret;
}
