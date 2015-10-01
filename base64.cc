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
char getBase64Char (int index) {

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
std::string base64Encode3Bytes (char* bytes) {

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
std::string base64Encode2Bytes (char* bytes) {

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
std::string base64Encode1Byte (char byte) {

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
std::string base64Encode (const char* input,
                          const unsigned long len ) {

  std::string encoded;
  char* inputChars = (char*)malloc(3*sizeof(char));
  unsigned int index = 0;

  //encode all the string in 3 byte sections, don't encode the last 1 or 2 
  // bytes if the len is not divisible by 3
  for ( ; index <= len - 3; index += 3 ) {
    inputChars[0] = input[index];
    inputChars[1] = input[index+1];
    inputChars[2] = input[index+2];
    encoded += base64Encode3Bytes(inputChars);
  }

  //encode the last 2 bytes if there are 2 bytes left at the end of the string
  // i.e. if (len % 3 == 2)
  if ( len - index == 2 ) {
    free(inputChars);
    inputChars = (char*)malloc(2*sizeof(char));
    inputChars[0] = input[index];
    inputChars[1] = input[index+1];
    encoded += base64Encode2Bytes(inputChars);
    index += 2;
  }

  //encode the last 1 byte if there is one byte left at the end of the string
  // i.e. if (len % 3 == 1)
  if ( len - index == 1 ) {
    free(inputChars);
    char inputChar = input[index];
    encoded += base64Encode1Byte(inputChar);
    index++;
  }

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
std::string base64Decode (std::string encoded) {

  std::string decoded;
  
  return decoded;
}


int main (int argc, char** argv) {

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

  //test7, encode({'a','b','c','d','e','f'}) == "YWJjZGVm"
  char* testStr6 = (char*)malloc(6*sizeof(char));
  testStr6[0] = 'a';
  testStr6[1] = 'b';
  testStr6[2] = 'c';
  testStr6[3] = 'd';
  testStr6[4] = 'e';
  testStr6[5] = 'f';
  assert(base64Encode(testStr6, 6) == "YWJjZGVm");

  //test8, encode({'u','v','w','x','y','z'}) == "dXZ3eHl6"
  testStr6[0] = 'u';
  testStr6[1] = 'v';
  testStr6[2] = 'w';
  testStr6[3] = 'x';
  testStr6[4] = 'y';
  testStr6[5] = 'z';
  assert(base64Encode(testStr6, 6) == "dXZ3eHl6");

  //test9, encode({'a','b','c','d','e','f','g'}) == "YWJjZGVmZw=="
  char* testStr7 = (char*)malloc(7*sizeof(char));
  testStr7[0] = 'a';
  testStr7[1] = 'b';
  testStr7[2] = 'c';
  testStr7[3] = 'd';
  testStr7[4] = 'e';
  testStr7[5] = 'f';
  testStr7[6] = 'g';
  assert(base64Encode(testStr7, 7) == "YWJjZGVmZw==");

  //test10, encode({'t','u','v','w','x','y','z'}) == "dHV2d3h5eg=="
  testStr7[0] = 't';
  testStr7[1] = 'u';
  testStr7[2] = 'v';
  testStr7[3] = 'w';
  testStr7[4] = 'x';
  testStr7[5] = 'y';
  testStr7[6] = 'z';
  assert(base64Encode(testStr7, 7) == "dHV2d3h5eg==");

  //test11, encode({'a','b','c','d','e','f','g','h'}) == "YWJjZGVmZ2g="
  char* testStr8 = (char*)malloc(7*sizeof(char));
  testStr8[0] = 'a';
  testStr8[1] = 'b';
  testStr8[2] = 'c';
  testStr8[3] = 'd';
  testStr8[4] = 'e';
  testStr8[5] = 'f';
  testStr8[6] = 'g';
  testStr8[7] = 'h';
  assert(base64Encode(testStr8, 8) == "YWJjZGVmZ2g=");

  //test12, encode({'s','t','u','v','w','x','y','z'}) == "c3R1dnd4eXo="
  testStr8[0] = 's';
  testStr8[1] = 't';
  testStr8[2] = 'u';
  testStr8[3] = 'v';
  testStr8[4] = 'w';
  testStr8[5] = 'x';
  testStr8[6] = 'y';
  testStr8[7] = 'z';
  assert(base64Encode(testStr8, 8) == "c3R1dnd4eXo=");

  std::cout << "Tests pass!" << std::endl;

  return 0;
}





