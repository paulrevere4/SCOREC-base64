#include <iostream>
#include <string>
#include <cassert>


static const std::string base64EncodeTable = 	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
												"abcdefghijklmnopqrstuvwxyz"
												"0123456789+/=";

char getBase64Char(int index){
	return base64EncodeTable[index];
}

std::string base64Encode3Bytes(char* bytes){
	std::string encoded;

	encoded += getBase64Char( (bytes[0] >> 2) & 0x3F ); //first 6 bits of byte1

	encoded += getBase64Char( ((bytes[0] << 4) & 0x30)  //last 2 bits of byte1
								| ((bytes[1] >> 4) & 0x0F) ); //first 4 of byte2

	encoded += getBase64Char( ((bytes[1] << 2) & 0x3C)  //last 4 bits of byte2
								| ((bytes[2] >> 6) & 0x03) ); //first 2 of byte3

	encoded += getBase64Char( bytes[2] & 0x3F ); //last 6 of byte3

	return encoded;
}

/*
Function base64Encode:
	Encodes a series of bytes specified by the arguments into a string of Base64
	chars that will represent them

Arguments:
	char* input - pointer to start of byte string to be encoded
	long len - number of bytes to be encoded

Returns:
	std::string - Base64 encoded string of the input bytes

*/
std::string base64Encode(	const unsigned char* input,
							const unsigned long len){
	std::string encoded;

	return encoded;
}

/*
Function base64Decode:
	Decodes a string of Base64 chars to the bytes they represent

Arguments:
	std::string encoded - Base64 encoded string

Returns:
	std::string - decoded string of bytes from the encoded data
*/
std::string base64Decode(std::string encoded){
	std::string decoded;
	
	return decoded;
}


int main(int argc, char** argv){

	//test1, encode("aaa") == "YWFh"
	char* testStr1 = (char*)malloc(3*sizeof(char));
	testStr1[0] = 'a';
	testStr1[1] = 'a';
	testStr1[2] = 'a';
	assert(base64Encode3Bytes(testStr1) == "YWFh");

	//test2, endcode("xyz") == "eHl6"
	char* testStr2 = (char*)malloc(3*sizeof(char));
	testStr2[0] = 'x';
	testStr2[1] = 'y';
	testStr2[2] = 'z';
	assert(base64Encode3Bytes(testStr2) == "eHl6");

	std::cout << "Tests pass!" << std::endl;

	return 0;
}





