#include <string>
#include <stdlib.h>

#include "base64.h"

// ===========================================================================
// =========================================================================== 
//  Implementation of base64.h. documentation of functions found in base64.h 
// ===========================================================================
// ===========================================================================

static const std::string base64EncodeTable =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "abcdefghijklmnopqrstuvwxyz"
                                              "0123456789+/=";

// ===========================================================================

char getBase64Char (int index) {

  return base64EncodeTable[index];

}

// ===========================================================================

std::string base64Encode3Bytes (char* bytes) {

  std::string encoded;

  //first 6 bits of byte1
  encoded += getBase64Char((bytes[0] >> 2) & 0x3F); 

  //last 2 bits of byte1 and the first 4 of byte2
  encoded += getBase64Char( ((bytes[0] << 4) & 0x30) | ((bytes[1] >> 4) & 0x0F));

  //last 4 bits of byte2 and the first 2 of byte3
  encoded += getBase64Char( ((bytes[1] << 2) & 0x3C) | ((bytes[2] >> 6) & 0x03));

  //last 6 of byte3
  encoded += getBase64Char( bytes[2] & 0x3F ); 

  return encoded;
}

// ===========================================================================

std::string base64Encode2Bytes (char* bytes) {

  std::string encoded;

  //first 6 bits of byte1
  encoded += getBase64Char((bytes[0] >> 2) & 0x3F); 

  //last 2 bits of byte1 combined with the the first 4 of byte2
  encoded += getBase64Char( ((bytes[0] << 4) & 0x30) | ((bytes[1] >> 4) & 0x0F));

  //last 4 bits of byte2 combined with the first 2 of byte3
  encoded += getBase64Char( ((bytes[1] << 2) & 0x3C) );

  //add a padding char since there is no byte 3
  encoded += '=';

  return encoded;
}

// ===========================================================================

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

// ===========================================================================


std::string base64Encode (const char* input,
                          const unsigned long len ) {

  std::string encoded;
  char* inputChars = (char*)malloc(3*sizeof(char));
  unsigned int index = 0;

  //encode all the string in 3 byte sections, this loop won't encode the last
  // 1 or 2 bytes if the len is not divisible by 3
  for ( ; index <= len - 3; index += 3 ) {
    inputChars[0] = input[index];
    inputChars[1] = input[index+1];
    inputChars[2] = input[index+2];
    encoded += base64Encode3Bytes(inputChars);
  }

  //encode the last 2 bytes if there are 2 bytes left at the end of the string
  // i.e. if (len % 3 == 2)
  if ( len - index == 2 ) {
    inputChars[0] = input[index];
    inputChars[1] = input[index+1];
    encoded += base64Encode2Bytes(inputChars);
    index += 2;
  }

  //encode the last 1 byte if there is one byte left at the end of the string
  // i.e. if (len % 3 == 1)
  if ( len - index == 1 ) {
    char inputChar = input[index];
    encoded += base64Encode1Byte(inputChar);
    index++;
  }

  free(inputChars);

  return encoded;
}

// ===========================================================================

std::string base64Decode4Bytes (char* bytes){
  std::string decoded;

  return decoded;
}

// ===========================================================================

// TODO: PR4: Implement
std::string base64Decode (std::string encoded) {

  std::string decoded;
  
  return decoded;
}

// ===========================================================================
// ===========================================================================
