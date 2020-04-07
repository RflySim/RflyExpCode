#include "stdafx.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
	
/* @function: Converts a two byte hex ascii number to binary.  Returns
   the binary form, or -1 for illegal hex number. */
int hex_to_binary(unsigned char *hex)	/* ptr to 2 byte hex code */
{
	int i, binary[2];
	_strupr((char *)hex);

	for(i=0; i<2; ++i)
	{
		if('0' <= hex[i]   &&   hex[i] <= '9')  
			binary[i] = hex[i] - '0';
		else if('A' <= hex[i]   &&   hex[i] <= 'F')
			binary[i] = hex[i] - 'A' + 10;
		else
			return -1;
	}
	return binary[0]*16 + binary[1];
}

/*********************************
*
* Function: char *strip(char *in)
*   Inputs: char *in - a pointer to a string variable
*  Outputs: the resulting string, striped of white space from the end
*   Return: a pointer to the string
*
**********************************/
char *strip(char *in){
	size_t len = strlen(in);
	while(len--){
		if(isspace(in[len]))
			in[len] = 0;
		else
			break;
	}
	return(in);
}
	
/*********************************
*
* Function: unsigned long htol(char *in) 
*   Inputs: char *in - a pointer to a string variable
*  Outputs: none 
*   Return: a long value corresponding to the value of the hex string 
*
**********************************/
unsigned long htol(char *in){
	static int hexVal[] = {0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,10,11,12,13,14,15};
	unsigned long val = 0L;
	size_t len;
	int i = 0;
	_strupr(in);
	if(in[1] == 'X')
		in += 2;
	strip(in);
    len = strlen(in);
    while(len--){
		val = val + (hexVal[in[(int)len]-'0'] * (unsigned long)(pow((float)16,(float)i++)));
    }
    return(val);
}
