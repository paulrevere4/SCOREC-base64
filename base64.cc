#include <iostream>
#include <string>
#include <cassert>


static const std::string base64EncodeTable =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "abcdefghijklmnopqrstuvwxyz"
                                              "0123456789+/=";

/*
Function getBase64Char:
  gets the char at the index given to it from the encode table
*/
char getBase64Char(int index){
  return base64EncodeTable[index];
}

/*
Function base64Encode3Bytes:
  Encodes 3 bytes sent to it into Base64

Arguments:
  char* bytes - char of array of bytes to be encoded - MUST BE SIZE 3

Returns:
  std::string - string of length 4 of the encoded bytes
*/
std::string base64Encode3Bytes(char* bytes){
  std::string encoded;

  //first 6 bits of byte1
  encoded += getBase64Char((bytes[0] >> 2) & 0x3F); 

  //last 2 bits of byte1 and the first 4 of byte2
  encoded += getBase64Char( ((bytes[0] << 4) & 0x30)|((bytes[1] >> 4) & 0x0F));

  //last 4 bits of byte2 and the first 2 of byte3
  encoded += getBase64Char( ((bytes[1] << 2) & 0x3C)|((bytes[2] >> 6) & 0x03));

  //last 6 of byte3
  encoded += getBase64Char( bytes[2] & 0x3F ); 

  return encoded;
}

/*
Function base64Encode2Bytes:
  Encodes 2 bytes sent to it into Base64. Used a when the end of a string is 
  being encoded and the string is of a length not divisible by 3. Since Base64
  encodes in 3 byte sections a padding char, '=', must be added to take the 
  place of the missing byte.

Arguments:
  char* bytes - char array of bytes to be encoded - MUST BE SIZE 2

Returns:  
  std::string - string of length 4 of the encoded bytes including padding
*/
std::string base64Encode2Bytes(char* bytes){
  std::string encoded;

  //first 6 bits of byte1
  encoded += getBase64Char((bytes[0] >> 2) & 0x3F); 

  //last 2 bits of byte1 combined with the the first 4 of byte2
  encoded += getBase64Char( ((bytes[0] << 4) & 0x30)|((bytes[1] >> 4) & 0x0F));

  //last 4 bits of byte2 combined with the first 2 of byte3
  encoded += getBase64Char( ((bytes[1] << 2) & 0x3C) );

  //add a padding char since there is no byte 3
  encoded += '=';

  return encoded;
}

/*
Function base64Encode1Byte:
  Encodes a single byte sent to it into Base64. Used when the end of a string is
  being encode and the tsring is of a length not divisible by 3. Since Base64
  encodes in 3 byte sections, two padding chars, "==", must be added to take the
  place of the missing bits.

Arguments:
  char byte - char of the byte to be encoded

Returns:
  std::string - string of length 4 of the encoded bytes including padding 
*/
std::string base64Encode1Byte(char byte){
  std::string encoded;

  //first 6 bits of the byte
  encoded += getBase64Char((byte >> 2) & 0x3F); 

  //last 2 bits of the byte
  encoded += getBase64Char((byte << 4) & 0x30);

  //add the padding chars since there is no byte 2 or 3
  encoded += "==";

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
std::string base64Encode( const unsigned char* input,
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

  //test1, encode({'a','a','a'}) == "YWFh"
  char* testStr3 = (char*)malloc(3*sizeof(char));
  testStr3[0] = 'a';
  testStr3[1] = 'a';
  testStr3[2] = 'a';
  assert(base64Encode3Bytes(testStr3) == "YWFh");

  //test2, encode({'x','y','z'}) == "eHl6"
  testStr3[0] = 'x';
  testStr3[1] = 'y';
  testStr3[2] = 'z';
  assert(base64Encode3Bytes(testStr3) == "eHl6");

  //test3, encode({'a','a'}) == "YWE="
  char* testStr2 = (char*)malloc(2*sizeof(char));
  testStr2[0] = 'a';
  testStr2[1] = 'a';
  assert(base64Encode2Bytes(testStr2) == "YWE=");

  //test4, encode({'x','y'}) == "eHk=""
  testStr2[0] = 'x';
  testStr2[1] = 'y';
  assert(base64Encode2Bytes(testStr2) == "eHk=");

  //test5, encode('a') == "YQ=="
  char testStr;
  testStr = 'a';
  assert(base64Encode1Byte(testStr) == "YQ==");

  //test6, encode('z') == "eg=="
  testStr = 'z';
  assert(base64Encode1Byte(testStr) == "eg==");

  std::cout << "Tests pass!" << std::endl;

  return 0;
}





