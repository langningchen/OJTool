#include <Codeforces.hpp>
#include <Tool.hpp>

const std::string AES_JS = R"(var slowAES={aes:{keySize:{SIZE_128:16,SIZE_192:24,SIZE_256:32},sbox:[0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16],rsbox:[0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d],rotate:function(word){var c=word[0];for(var i=0;i<3;i++)word[i]=word[i+1];word[3]=c;return word},Rcon:[0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb,0x8d,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,0xb3,0x7d,0xfa,0xef,0xc5,0x91,0x39,0x72,0xe4,0xd3,0xbd,0x61,0xc2,0x9f,0x25,0x4a,0x94,0x33,0x66,0xcc,0x83,0x1d,0x3a,0x74,0xe8,0xcb],G2X:[0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,0x20,0x22,0x24,0x26,0x28,0x2a,0x2c,0x2e,0x30,0x32,0x34,0x36,0x38,0x3a,0x3c,0x3e,0x40,0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,0x92,0x94,0x96,0x98,0x9a,0x9c,0x9e,0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb4,0xb6,0xb8,0xba,0xbc,0xbe,0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xf0,0xf2,0xf4,0xf6,0xf8,0xfa,0xfc,0xfe,0x1b,0x19,0x1f,0x1d,0x13,0x11,0x17,0x15,0x0b,0x09,0x0f,0x0d,0x03,0x01,0x07,0x05,0x3b,0x39,0x3f,0x3d,0x33,0x31,0x37,0x35,0x2b,0x29,0x2f,0x2d,0x23,0x21,0x27,0x25,0x5b,0x59,0x5f,0x5d,0x53,0x51,0x57,0x55,0x4b,0x49,0x4f,0x4d,0x43,0x41,0x47,0x45,0x7b,0x79,0x7f,0x7d,0x73,0x71,0x77,0x75,0x6b,0x69,0x6f,0x6d,0x63,0x61,0x67,0x65,0x9b,0x99,0x9f,0x9d,0x93,0x91,0x97,0x95,0x8b,0x89,0x8f,0x8d,0x83,0x81,0x87,0x85,0xbb,0xb9,0xbf,0xbd,0xb3,0xb1,0xb7,0xb5,0xab,0xa9,0xaf,0xad,0xa3,0xa1,0xa7,0xa5,0xdb,0xd9,0xdf,0xdd,0xd3,0xd1,0xd7,0xd5,0xcb,0xc9,0xcf,0xcd,0xc3,0xc1,0xc7,0xc5,0xfb,0xf9,0xff,0xfd,0xf3,0xf1,0xf7,0xf5,0xeb,0xe9,0xef,0xed,0xe3,0xe1,0xe7,0xe5],G3X:[0x00,0x03,0x06,0x05,0x0c,0x0f,0x0a,0x09,0x18,0x1b,0x1e,0x1d,0x14,0x17,0x12,0x11,0x30,0x33,0x36,0x35,0x3c,0x3f,0x3a,0x39,0x28,0x2b,0x2e,0x2d,0x24,0x27,0x22,0x21,0x60,0x63,0x66,0x65,0x6c,0x6f,0x6a,0x69,0x78,0x7b,0x7e,0x7d,0x74,0x77,0x72,0x71,0x50,0x53,0x56,0x55,0x5c,0x5f,0x5a,0x59,0x48,0x4b,0x4e,0x4d,0x44,0x47,0x42,0x41,0xc0,0xc3,0xc6,0xc5,0xcc,0xcf,0xca,0xc9,0xd8,0xdb,0xde,0xdd,0xd4,0xd7,0xd2,0xd1,0xf0,0xf3,0xf6,0xf5,0xfc,0xff,0xfa,0xf9,0xe8,0xeb,0xee,0xed,0xe4,0xe7,0xe2,0xe1,0xa0,0xa3,0xa6,0xa5,0xac,0xaf,0xaa,0xa9,0xb8,0xbb,0xbe,0xbd,0xb4,0xb7,0xb2,0xb1,0x90,0x93,0x96,0x95,0x9c,0x9f,0x9a,0x99,0x88,0x8b,0x8e,0x8d,0x84,0x87,0x82,0x81,0x9b,0x98,0x9d,0x9e,0x97,0x94,0x91,0x92,0x83,0x80,0x85,0x86,0x8f,0x8c,0x89,0x8a,0xab,0xa8,0xad,0xae,0xa7,0xa4,0xa1,0xa2,0xb3,0xb0,0xb5,0xb6,0xbf,0xbc,0xb9,0xba,0xfb,0xf8,0xfd,0xfe,0xf7,0xf4,0xf1,0xf2,0xe3,0xe0,0xe5,0xe6,0xef,0xec,0xe9,0xea,0xcb,0xc8,0xcd,0xce,0xc7,0xc4,0xc1,0xc2,0xd3,0xd0,0xd5,0xd6,0xdf,0xdc,0xd9,0xda,0x5b,0x58,0x5d,0x5e,0x57,0x54,0x51,0x52,0x43,0x40,0x45,0x46,0x4f,0x4c,0x49,0x4a,0x6b,0x68,0x6d,0x6e,0x67,0x64,0x61,0x62,0x73,0x70,0x75,0x76,0x7f,0x7c,0x79,0x7a,0x3b,0x38,0x3d,0x3e,0x37,0x34,0x31,0x32,0x23,0x20,0x25,0x26,0x2f,0x2c,0x29,0x2a,0x0b,0x08,0x0d,0x0e,0x07,0x04,0x01,0x02,0x13,0x10,0x15,0x16,0x1f,0x1c,0x19,0x1a],G9X:[0x00,0x09,0x12,0x1b,0x24,0x2d,0x36,0x3f,0x48,0x41,0x5a,0x53,0x6c,0x65,0x7e,0x77,0x90,0x99,0x82,0x8b,0xb4,0xbd,0xa6,0xaf,0xd8,0xd1,0xca,0xc3,0xfc,0xf5,0xee,0xe7,0x3b,0x32,0x29,0x20,0x1f,0x16,0x0d,0x04,0x73,0x7a,0x61,0x68,0x57,0x5e,0x45,0x4c,0xab,0xa2,0xb9,0xb0,0x8f,0x86,0x9d,0x94,0xe3,0xea,0xf1,0xf8,0xc7,0xce,0xd5,0xdc,0x76,0x7f,0x64,0x6d,0x52,0x5b,0x40,0x49,0x3e,0x37,0x2c,0x25,0x1a,0x13,0x08,0x01,0xe6,0xef,0xf4,0xfd,0xc2,0xcb,0xd0,0xd9,0xae,0xa7,0xbc,0xb5,0x8a,0x83,0x98,0x91,0x4d,0x44,0x5f,0x56,0x69,0x60,0x7b,0x72,0x05,0x0c,0x17,0x1e,0x21,0x28,0x33,0x3a,0xdd,0xd4,0xcf,0xc6,0xf9,0xf0,0xeb,0xe2,0x95,0x9c,0x87,0x8e,0xb1,0xb8,0xa3,0xaa,0xec,0xe5,0xfe,0xf7,0xc8,0xc1,0xda,0xd3,0xa4,0xad,0xb6,0xbf,0x80,0x89,0x92,0x9b,0x7c,0x75,0x6e,0x67,0x58,0x51,0x4a,0x43,0x34,0x3d,0x26,0x2f,0x10,0x19,0x02,0x0b,0xd7,0xde,0xc5,0xcc,0xf3,0xfa,0xe1,0xe8,0x9f,0x96,0x8d,0x84,0xbb,0xb2,0xa9,0xa0,0x47,0x4e,0x55,0x5c,0x63,0x6a,0x71,0x78,0x0f,0x06,0x1d,0x14,0x2b,0x22,0x39,0x30,0x9a,0x93,0x88,0x81,0xbe,0xb7,0xac,0xa5,0xd2,0xdb,0xc0,0xc9,0xf6,0xff,0xe4,0xed,0x0a,0x03,0x18,0x11,0x2e,0x27,0x3c,0x35,0x42,0x4b,0x50,0x59,0x66,0x6f,0x74,0x7d,0xa1,0xa8,0xb3,0xba,0x85,0x8c,0x97,0x9e,0xe9,0xe0,0xfb,0xf2,0xcd,0xc4,0xdf,0xd6,0x31,0x38,0x23,0x2a,0x15,0x1c,0x07,0x0e,0x79,0x70,0x6b,0x62,0x5d,0x54,0x4f,0x46],GBX:[0x00,0x0b,0x16,0x1d,0x2c,0x27,0x3a,0x31,0x58,0x53,0x4e,0x45,0x74,0x7f,0x62,0x69,0xb0,0xbb,0xa6,0xad,0x9c,0x97,0x8a,0x81,0xe8,0xe3,0xfe,0xf5,0xc4,0xcf,0xd2,0xd9,0x7b,0x70,0x6d,0x66,0x57,0x5c,0x41,0x4a,0x23,0x28,0x35,0x3e,0x0f,0x04,0x19,0x12,0xcb,0xc0,0xdd,0xd6,0xe7,0xec,0xf1,0xfa,0x93,0x98,0x85,0x8e,0xbf,0xb4,0xa9,0xa2,0xf6,0xfd,0xe0,0xeb,0xda,0xd1,0xcc,0xc7,0xae,0xa5,0xb8,0xb3,0x82,0x89,0x94,0x9f,0x46,0x4d,0x50,0x5b,0x6a,0x61,0x7c,0x77,0x1e,0x15,0x08,0x03,0x32,0x39,0x24,0x2f,0x8d,0x86,0x9b,0x90,0xa1,0xaa,0xb7,0xbc,0xd5,0xde,0xc3,0xc8,0xf9,0xf2,0xef,0xe4,0x3d,0x36,0x2b,0x20,0x11,0x1a,0x07,0x0c,0x65,0x6e,0x73,0x78,0x49,0x42,0x5f,0x54,0xf7,0xfc,0xe1,0xea,0xdb,0xd0,0xcd,0xc6,0xaf,0xa4,0xb9,0xb2,0x83,0x88,0x95,0x9e,0x47,0x4c,0x51,0x5a,0x6b,0x60,0x7d,0x76,0x1f,0x14,0x09,0x02,0x33,0x38,0x25,0x2e,0x8c,0x87,0x9a,0x91,0xa0,0xab,0xb6,0xbd,0xd4,0xdf,0xc2,0xc9,0xf8,0xf3,0xee,0xe5,0x3c,0x37,0x2a,0x21,0x10,0x1b,0x06,0x0d,0x64,0x6f,0x72,0x79,0x48,0x43,0x5e,0x55,0x01,0x0a,0x17,0x1c,0x2d,0x26,0x3b,0x30,0x59,0x52,0x4f,0x44,0x75,0x7e,0x63,0x68,0xb1,0xba,0xa7,0xac,0x9d,0x96,0x8b,0x80,0xe9,0xe2,0xff,0xf4,0xc5,0xce,0xd3,0xd8,0x7a,0x71,0x6c,0x67,0x56,0x5d,0x40,0x4b,0x22,0x29,0x34,0x3f,0x0e,0x05,0x18,0x13,0xca,0xc1,0xdc,0xd7,0xe6,0xed,0xf0,0xfb,0x92,0x99,0x84,0x8f,0xbe,0xb5,0xa8,0xa3],GDX:[0x00,0x0d,0x1a,0x17,0x34,0x39,0x2e,0x23,0x68,0x65,0x72,0x7f,0x5c,0x51,0x46,0x4b,0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b,0xbb,0xb6,0xa1,0xac,0x8f,0x82,0x95,0x98,0xd3,0xde,0xc9,0xc4,0xe7,0xea,0xfd,0xf0,0x6b,0x66,0x71,0x7c,0x5f,0x52,0x45,0x48,0x03,0x0e,0x19,0x14,0x37,0x3a,0x2d,0x20,0x6d,0x60,0x77,0x7a,0x59,0x54,0x43,0x4e,0x05,0x08,0x1f,0x12,0x31,0x3c,0x2b,0x26,0xbd,0xb0,0xa7,0xaa,0x89,0x84,0x93,0x9e,0xd5,0xd8,0xcf,0xc2,0xe1,0xec,0xfb,0xf6,0xd6,0xdb,0xcc,0xc1,0xe2,0xef,0xf8,0xf5,0xbe,0xb3,0xa4,0xa9,0x8a,0x87,0x90,0x9d,0x06,0x0b,0x1c,0x11,0x32,0x3f,0x28,0x25,0x6e,0x63,0x74,0x79,0x5a,0x57,0x40,0x4d,0xda,0xd7,0xc0,0xcd,0xee,0xe3,0xf4,0xf9,0xb2,0xbf,0xa8,0xa5,0x86,0x8b,0x9c,0x91,0x0a,0x07,0x10,0x1d,0x3e,0x33,0x24,0x29,0x62,0x6f,0x78,0x75,0x56,0x5b,0x4c,0x41,0x61,0x6c,0x7b,0x76,0x55,0x58,0x4f,0x42,0x09,0x04,0x13,0x1e,0x3d,0x30,0x27,0x2a,0xb1,0xbc,0xab,0xa6,0x85,0x88,0x9f,0x92,0xd9,0xd4,0xc3,0xce,0xed,0xe0,0xf7,0xfa,0xb7,0xba,0xad,0xa0,0x83,0x8e,0x99,0x94,0xdf,0xd2,0xc5,0xc8,0xeb,0xe6,0xf1,0xfc,0x67,0x6a,0x7d,0x70,0x53,0x5e,0x49,0x44,0x0f,0x02,0x15,0x18,0x3b,0x36,0x21,0x2c,0x0c,0x01,0x16,0x1b,0x38,0x35,0x22,0x2f,0x64,0x69,0x7e,0x73,0x50,0x5d,0x4a,0x47,0xdc,0xd1,0xc6,0xcb,0xe8,0xe5,0xf2,0xff,0xb4,0xb9,0xae,0xa3,0x80,0x8d,0x9a,0x97],GEX:[0x00,0x0e,0x1c,0x12,0x38,0x36,0x24,0x2a,0x70,0x7e,0x6c,0x62,0x48,0x46,0x54,0x5a,0xe0,0xee,0xfc,0xf2,0xd8,0xd6,0xc4,0xca,0x90,0x9e,0x8c,0x82,0xa8,0xa6,0xb4,0xba,0xdb,0xd5,0xc7,0xc9,0xe3,0xed,0xff,0xf1,0xab,0xa5,0xb7,0xb9,0x93,0x9d,0x8f,0x81,0x3b,0x35,0x27,0x29,0x03,0x0d,0x1f,0x11,0x4b,0x45,0x57,0x59,0x73,0x7d,0x6f,0x61,0xad,0xa3,0xb1,0xbf,0x95,0x9b,0x89,0x87,0xdd,0xd3,0xc1,0xcf,0xe5,0xeb,0xf9,0xf7,0x4d,0x43,0x51,0x5f,0x75,0x7b,0x69,0x67,0x3d,0x33,0x21,0x2f,0x05,0x0b,0x19,0x17,0x76,0x78,0x6a,0x64,0x4e,0x40,0x52,0x5c,0x06,0x08,0x1a,0x14,0x3e,0x30,0x22,0x2c,0x96,0x98,0x8a,0x84,0xae,0xa0,0xb2,0xbc,0xe6,0xe8,0xfa,0xf4,0xde,0xd0,0xc2,0xcc,0x41,0x4f,0x5d,0x53,0x79,0x77,0x65,0x6b,0x31,0x3f,0x2d,0x23,0x09,0x07,0x15,0x1b,0xa1,0xaf,0xbd,0xb3,0x99,0x97,0x85,0x8b,0xd1,0xdf,0xcd,0xc3,0xe9,0xe7,0xf5,0xfb,0x9a,0x94,0x86,0x88,0xa2,0xac,0xbe,0xb0,0xea,0xe4,0xf6,0xf8,0xd2,0xdc,0xce,0xc0,0x7a,0x74,0x66,0x68,0x42,0x4c,0x5e,0x50,0x0a,0x04,0x16,0x18,0x32,0x3c,0x2e,0x20,0xec,0xe2,0xf0,0xfe,0xd4,0xda,0xc8,0xc6,0x9c,0x92,0x80,0x8e,0xa4,0xaa,0xb8,0xb6,0x0c,0x02,0x10,0x1e,0x34,0x3a,0x28,0x26,0x7c,0x72,0x60,0x6e,0x44,0x4a,0x58,0x56,0x37,0x39,0x2b,0x25,0x0f,0x01,0x13,0x1d,0x47,0x49,0x5b,0x55,0x7f,0x71,0x63,0x6d,0xd7,0xd9,0xcb,0xc5,0xef,0xe1,0xf3,0xfd,0xa7,0xa9,0xbb,0xb5,0x9f,0x91,0x83,0x8d],core:function(word,iteration){word=this.rotate(word);for(var i=0;i<4;++i)word[i]=this.sbox[word[i]];word[0]=word[0]^this.Rcon[iteration];return word},expandKey:function(key,size){var expandedKeySize=(16*(this.numberOfRounds(size)+1));var currentSize=0;var rconIteration=1;var t=[];var expandedKey=[];for(var i=0;i<expandedKeySize;i++)expandedKey[i]=0;for(var j=0;j<size;j++)expandedKey[j]=key[j];currentSize+=size;while(currentSize<expandedKeySize){for(var k=0;k<4;k++)t[k]=expandedKey[(currentSize-4)+k];if(currentSize%size==0)t=this.core(t,rconIteration++);if(size==this.keySize.SIZE_256&&((currentSize%size)==16))for(var l=0;l<4;l++)t[l]=this.sbox[t[l]];for(var m=0;m<4;m++){expandedKey[currentSize]=expandedKey[currentSize-size]^t[m];currentSize++}}return expandedKey},addRoundKey:function(state,roundKey){for(var i=0;i<16;i++)state[i]^=roundKey[i];return state},createRoundKey:function(expandedKey,roundKeyPointer){var roundKey=[];for(var i=0;i<4;i++)for(var j=0;j<4;j++)roundKey[j*4+i]=expandedKey[roundKeyPointer+i*4+j];return roundKey},subBytes:function(state,isInv){for(var i=0;i<16;i++)state[i]=isInv?this.rsbox[state[i]]:this.sbox[state[i]];return state},shiftRows:function(state,isInv){for(var i=0;i<4;i++)state=this.shiftRow(state,i*4,i,isInv);return state},shiftRow:function(state,statePointer,nbr,isInv){for(var i=0;i<nbr;i++){if(isInv){var tmp=state[statePointer+3];for(var j=3;j>0;j--)state[statePointer+j]=state[statePointer+j-1];state[statePointer]=tmp}else{var tmp=state[statePointer];for(var j=0;j<3;j++)state[statePointer+j]=state[statePointer+j+1];state[statePointer+3]=tmp}}return state},galois_multiplication:function(a,b){var p=0;for(var counter=0;counter<8;counter++){if((b&1)==1)p^=a;if(p>0x100)p^=0x100;var hi_bit_set=(a&0x80);a<<=1;if(a>0x100)a^=0x100;if(hi_bit_set==0x80)a^=0x1b;if(a>0x100)a^=0x100;b>>=1;if(b>0x100)b^=0x100}return p},mixColumns:function(state,isInv){var column=[];for(var i=0;i<4;i++){for(var j=0;j<4;j++)column[j]=state[(j*4)+i];column=this.mixColumn(column,isInv);for(var k=0;k<4;k++)state[(k*4)+i]=column[k]}return state},mixColumn:function(column,isInv){var mult=[];if(isInv)mult=[14,9,13,11];else mult=[2,1,1,3];var cpy=[];for(var i=0;i<4;i++)cpy[i]=column[i];column[0]=this.galois_multiplication(cpy[0],mult[0])^this.galois_multiplication(cpy[3],mult[1])^this.galois_multiplication(cpy[2],mult[2])^this.galois_multiplication(cpy[1],mult[3]);column[1]=this.galois_multiplication(cpy[1],mult[0])^this.galois_multiplication(cpy[0],mult[1])^this.galois_multiplication(cpy[3],mult[2])^this.galois_multiplication(cpy[2],mult[3]);column[2]=this.galois_multiplication(cpy[2],mult[0])^this.galois_multiplication(cpy[1],mult[1])^this.galois_multiplication(cpy[0],mult[2])^this.galois_multiplication(cpy[3],mult[3]);column[3]=this.galois_multiplication(cpy[3],mult[0])^this.galois_multiplication(cpy[2],mult[1])^this.galois_multiplication(cpy[1],mult[2])^this.galois_multiplication(cpy[0],mult[3]);return column},round:function(state,roundKey){state=this.subBytes(state,false);state=this.shiftRows(state,false);state=this.mixColumns(state,false);state=this.addRoundKey(state,roundKey);return state},invRound:function(state,roundKey){state=this.shiftRows(state,true);state=this.subBytes(state,true);state=this.addRoundKey(state,roundKey);state=this.mixColumns(state,true);return state},main:function(state,expandedKey,nbrRounds){state=this.addRoundKey(state,this.createRoundKey(expandedKey,0));for(var i=1;i<nbrRounds;i++)state=this.round(state,this.createRoundKey(expandedKey,16*i));state=this.subBytes(state,false);state=this.shiftRows(state,false);state=this.addRoundKey(state,this.createRoundKey(expandedKey,16*nbrRounds));return state},invMain:function(state,expandedKey,nbrRounds){state=this.addRoundKey(state,this.createRoundKey(expandedKey,16*nbrRounds));for(var i=nbrRounds-1;i>0;i--)state=this.invRound(state,this.createRoundKey(expandedKey,16*i));state=this.shiftRows(state,true);state=this.subBytes(state,true);state=this.addRoundKey(state,this.createRoundKey(expandedKey,0));return state},numberOfRounds:function(size){var nbrRounds;switch(size){case this.keySize.SIZE_128:nbrRounds=10;break;case this.keySize.SIZE_192:nbrRounds=12;break;case this.keySize.SIZE_256:nbrRounds=14;break;default:return null;break}return nbrRounds},encrypt:function(input,key,size){var output=[];var block=[];var nbrRounds=this.numberOfRounds(size);for(var i=0;i<4;i++)for(var j=0;j<4;j++)block[(i+(j*4))]=input[(i*4)+j];var expandedKey=this.expandKey(key,size);block=this.main(block,expandedKey,nbrRounds);for(var k=0;k<4;k++)for(var l=0;l<4;l++)output[(k*4)+l]=block[(k+(l*4))];return output},decrypt:function(input,key,size){var output=[];var block=[];var nbrRounds=this.numberOfRounds(size);for(var i=0;i<4;i++)for(var j=0;j<4;j++)block[(i+(j*4))]=input[(i*4)+j];var expandedKey=this.expandKey(key,size);block=this.invMain(block,expandedKey,nbrRounds);for(var k=0;k<4;k++)for(var l=0;l<4;l++)output[(k*4)+l]=block[(k+(l*4))];return output}},modeOfOperation:{OFB:0,CFB:1,CBC:2},getBlock:function(bytesIn,start,end,mode){if(end-start>16)end=start+16;return bytesIn.slice(start,end)},encrypt:function(bytesIn,mode,key,iv){var size=key.length;if(iv.length%16){throw'iv length must be 128 bits.';}var byteArray=[];var input=[];var output=[];var ciphertext=[];var cipherOut=[];var firstRound=true;if(mode==this.modeOfOperation.CBC)this.padBytesIn(bytesIn);if(bytesIn!==null){for(var j=0;j<Math.ceil(bytesIn.length/16);j++){var start=j*16;var end=j*16+16;if(j*16+16>bytesIn.length)end=bytesIn.length;byteArray=this.getBlock(bytesIn,start,end,mode);if(mode==this.modeOfOperation.CFB){if(firstRound){output=this.aes.encrypt(iv,key,size);firstRound=false}else output=this.aes.encrypt(input,key,size);for(var i=0;i<16;i++)ciphertext[i]=byteArray[i]^output[i];for(var k=0;k<end-start;k++)cipherOut.push(ciphertext[k]);input=ciphertext}else if(mode==this.modeOfOperation.OFB){if(firstRound){output=this.aes.encrypt(iv,key,size);firstRound=false}else output=this.aes.encrypt(input,key,size);for(var i=0;i<16;i++)ciphertext[i]=byteArray[i]^output[i];for(var k=0;k<end-start;k++)cipherOut.push(ciphertext[k]);input=output}else if(mode==this.modeOfOperation.CBC){for(var i=0;i<16;i++)input[i]=byteArray[i]^((firstRound)?iv[i]:ciphertext[i]);firstRound=false;ciphertext=this.aes.encrypt(input,key,size);for(var k=0;k<16;k++)cipherOut.push(ciphertext[k])}}}return cipherOut},decrypt:function(cipherIn,mode,key,iv){var size=key.length;if(iv.length%16){throw'iv length must be 128 bits.';}var ciphertext=[];var input=[];var output=[];var byteArray=[];var bytesOut=[];var firstRound=true;if(cipherIn!==null){for(var j=0;j<Math.ceil(cipherIn.length/16);j++){var start=j*16;var end=j*16+16;if(j*16+16>cipherIn.length)end=cipherIn.length;ciphertext=this.getBlock(cipherIn,start,end,mode);if(mode==this.modeOfOperation.CFB){if(firstRound){output=this.aes.encrypt(iv,key,size);firstRound=false}else output=this.aes.encrypt(input,key,size);for(i=0;i<16;i++)byteArray[i]=output[i]^ciphertext[i];for(var k=0;k<end-start;k++)bytesOut.push(byteArray[k]);input=ciphertext}else if(mode==this.modeOfOperation.OFB){if(firstRound){output=this.aes.encrypt(iv,key,size);firstRound=false}else output=this.aes.encrypt(input,key,size);for(i=0;i<16;i++)byteArray[i]=output[i]^ciphertext[i];for(var k=0;k<end-start;k++)bytesOut.push(byteArray[k]);input=output}else if(mode==this.modeOfOperation.CBC){output=this.aes.decrypt(ciphertext,key,size);for(i=0;i<16;i++)byteArray[i]=((firstRound)?iv[i]:input[i])^output[i];firstRound=false;for(var k=0;k<end-start;k++)bytesOut.push(byteArray[k]);input=ciphertext}}if(mode==this.modeOfOperation.CBC)this.unpadBytesOut(bytesOut)}return bytesOut},padBytesIn:function(data){var len=data.length;var padByte=16-(len%16);for(var i=0;i<padByte;i++){data.push(padByte)}},unpadBytesOut:function(data){var padCount=0;var padByte=-1;var blockSize=16;if(data.length>16){for(var i=data.length-1;i>=data.length-1-blockSize;i--){if(data[i]<=blockSize){if(padByte==-1)padByte=data[i];if(data[i]!=padByte){padCount=0;break}padCount++}else break;if(padCount==padByte)break}if(padCount>0)data.splice(data.length-padCount,padCount)}}};)";

std::string CODEFORCES::GetCSRF() {
    // Get csrf token
    std::string Token = GetStringBetween(GetDataFromFileToString(),
                                         "<input type='hidden' name='csrf_token' value='", "'/>");
    if (Token == "")
        TRIGGER_ERROR("Can not find csrf token");
    return Token;
}
std::string CODEFORCES::OutputPre(TiXmlElement *Input) {
    // Output pre tag
    std::string Output;
    Output += "```\n";
    for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
        // If the node is text, output it
        if (i->Type() == TiXmlNode::TINYXML_TEXT)
            Output += i->ToText()->Value();

        // If the node is br, output a newline
        else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
            if (std::string(i->Value()) == "br")
                Output += "\n";

    // If the last character is not a newline, add a newline
    if (Output[Output.size() - 1] != '\n')
        Output += "\n";
    Output += "```";
    return Output;
}
std::string CODEFORCES::Output(TiXmlElement *Input, bool InLatex) {
    std::string OutputValue = "";
    std::string Value = Input->Value();

    // If the node is pre, call OutputPre to output it
    if (Value == "pre") {
        OutputValue += "\n" + OutputPre(Input) + "\n";
        return OutputValue;
    }

    // If the node is img, output it as a markdown image
    else if (Value == "img") {
        OutputValue += " ![](" + std::string(Input->Attribute("src")) + ") ";
        return OutputValue;
    }

    // If the node is a ul output as a newline
    else if (Value == "ul")
        OutputValue += "\n";

    // If the node is a li output as a list
    else if (Value == "li")
        OutputValue += "- ";

    // If the node is a span, output it as it should be
    else if (Value == "span" && Input->Attribute("class") != NULL) {
        std::string Class = Input->Attribute("class");

        // If it is bold
        if (Class == "tex-font-style-bf")
            OutputValue += " **";

        // If it is italic
        else if (Class == "tex-font-style-tt")
            OutputValue += " `";

        // Else it is a latex expressions
        else
            OutputValue += " $";
        InLatex = true;
    }

    // If the node is a sup, output it as a superscript
    else if (Value == "sup")
        OutputValue += "^{";

    // If the node is a sub, output it as a subscript
    else if (Value == "sub")
        OutputValue += "_{";

    // Output the node's children
    for (TiXmlNode *i = Input->FirstChild(); i != NULL; i = i->NextSibling())
        // If the node is text, output it
        if (i->Type() == TiXmlNode::TINYXML_TEXT)
            OutputValue += i->ToText()->Value();

        // If the node is element, call Output to output it
        else if (i->Type() == TiXmlNode::TINYXML_ELEMENT)
            OutputValue += Output(i->ToElement(), InLatex);

    // End all expressions as above
    if (Value == "span" && Input->Attribute("class") != NULL) {
        std::string Class = Input->Attribute("class");
        if (Class == "tex-font-style-bf")
            OutputValue += "** ";
        else if (Class == "tex-font-style-tt")
            OutputValue += "` ";
        else
            OutputValue += "$ ";
    } else if (Value == "li")
        OutputValue += "\n";
    else if (Value == "ul")
        OutputValue += "\n";
    else if (Value == "sup")
        OutputValue += "}";
    else if (Value == "sub")
        OutputValue += "}";
    else if (Value == "p")
        OutputValue += "\n";
    return OutputValue;
}
std::string CODEFORCES::ToNormalName(std::string Input) {
    // Convert the Codeforces name to normal judge name
    if (Input == "OK")
        return "AC";
    if (Input == "FAILED")
        return "FAIL";
    if (Input == "PARTIAL")
        return "PRT";
    if (Input == "COMPILATION_ERROR")
        return "CE";
    if (Input == "RUNTIME_ERROR")
        return "RE";
    if (Input == "WRONG_ANSWER")
        return "WA";
    if (Input == "PRESENTATION_ERROR")
        return "PE";
    if (Input == "TIME_LIMIT_EXCEEDED")
        return "TLE";
    if (Input == "MEMORY_LIMIT_EXCEEDED")
        return "MLE";
    if (Input == "IDLENESS_LIMIT_EXCEEDED")
        return "ILE";
    if (Input == "SECURITY_VIOLATED")
        return "SV";
    if (Input == "CRASHED")
        return "CRS";
    if (Input == "INPUT_PREPARATION_CRASHED")
        return "IPC";
    if (Input == "CHALLENGED")
        return "CHL";
    if (Input == "SKIPPED")
        return "SKP";
    if (Input == "TESTING")
        return "TST";
    if (Input == "REJECTED")
        return "REJ";
    return Input;
}
void CODEFORCES::Login(std::string Username, std::string Password) {
    // Check if the user is already logged in
    int HTTPResponseCode = 0;
    std::cout << "Checking login... " << std::flush;
    GetDataToFile("https://codeforces.com/enter",
                  "",
                  "",
                  false,
                  "",
                  NULL,
                  &HTTPResponseCode);
    if (HTTPResponseCode == 302) {
        std::cout << "Already logged in" << std::endl;
        return;
    }
    std::cout << "Not logged in" << std::endl;
    HTTPResponseCode = 0;

    // Login
    std::cout << "Logging in... " << std::flush;
    GetDataToFile("https://codeforces.com/enter",
                  "",
                  "",
                  true,
                  std::string("csrf_token=" + GetCSRF() +
                              "&action=enter" +
                              "&ftaa=" + ftaa +
                              "&bfaa=" + bfaa +
                              "&handleOrEmail=" + URLEncode(Username.c_str()) +
                              "&password=" + URLEncode(Password.c_str()) +
                              "&_tta=176" +
                              "&remember=on")
                      .c_str(),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200) {
        // Login failed
        std::string LoginPageData = GetDataFromFileToString();

        // If the login failed because of the check of javascript
        if (LoginPageData.find("toNumbers")) {
            // Get the javascript code and write it to a file
            SetDataFromStringToFile("/tmp/Run.js",
                                    // Get the javascript library
                                    AES_JS + "\n\n\n\nfunction " +
                                        // Remove set cookie code and replace it with a variable
                                        StringReplaceAll(
                                            GetStringBetween(LoginPageData,
                                                             "<script>function ",
                                                             "document.location.href="),
                                            "document.cookie", "var Output") +
                                        "\n\nconsole.log(Output);\n");

            // Run the javascript code
            system(std::string("nodejs /tmp/Run.js >> /tmp/Output.tmp").c_str());

            // Get the output of the javascript code and try to login again
            GetDataToFile(GetStringBetween(LoginPageData, "document.location.href=\"", "\";</script>"),
                          "",
                          "",
                          true,
                          std::string("csrf_token=" + GetCSRF() +
                                      "&action=enter" +
                                      "&ftaa=" + ftaa +
                                      "&bfaa=" + bfaa +
                                      "&handleOrEmail=" + URLEncode(Username.c_str()) +
                                      "&password=" + URLEncode(Password.c_str()) +
                                      "&_tta=176" +
                                      "&remember=on")
                              .c_str(),
                          NULL,
                          &HTTPResponseCode,
                          FORM,
                          // Set the cookie
                          "#HttpOnly_codeforces.com\tFALSE\t/\tFALSE\t0\tRCPC\t" + GetStringBetween(GetDataFromFileToString("/tmp/Output.tmp"), "RCPC=", ";"));

            if (HTTPResponseCode == 200)
                TRIGGER_ERROR("Login failed");
        } else
            TRIGGER_ERROR("Login failed");
    }
    std::cout << "Succeed" << std::endl;
}
void CODEFORCES::GetProblemDetail(std::string ProblemID) {
    if (!IfFileExist("/tmp/Codeforces-" + ProblemID + ".md")) {
        // Get the problem detail
        std::cout << "Getting problem detail... " << std::flush;
        GetDataToFile("https://codeforces.com/problemset/problem/" +
                      ProblemID.substr(0, ProblemID.size() - 1) + "/" +
                      ProblemID.substr(ProblemID.size() - 1));
        std::cout << "Succeed" << std::endl;

        // Format the problem detail and prase it
        std::cout << "Parsing problem detail... " << std::flush;
        TiXmlDocument ProblemXmlDocument;
        ProblemXmlDocument.Parse(TOOL::TidyHTMLDocument(GetDataFromFileToString()).c_str());
        if (ProblemXmlDocument.Error())
            TRIGGER_ERROR("Parse problem detail error: "s + ProblemXmlDocument.ErrorDesc());
        std::ofstream OutputFileStream(std::string("/tmp/Codeforces-" + ProblemID + ".md").c_str());
        std::cout << "Succeed" << std::endl;

        // Find the problem detail
        TiXmlHandle ProblemXmlHandle = TiXmlHandle(&ProblemXmlDocument)
                                           .FirstChild("html")
                                           .FirstChild("body")
                                           .Child("div", 3)
                                           .Child("div", 4)
                                           .Child("div", 1)
                                           .Child("div", 2)
                                           .Child("div", 1)
                                           .Child("div", 0);

        // Output the problem detail
        OutputFileStream << "# " << ProblemXmlHandle.Child(0).Child(0).ToElement()->GetText()
                         << std::endl
                         << std::endl
                         << "## Description" << std::endl
                         << Output(ProblemXmlHandle.Child(1).ToElement()) << std::endl
                         << std::endl;
        for (TiXmlNode *i = ProblemXmlHandle.Child(2).Node(); i != NULL; i = i->NextSibling()) {
            TiXmlNode *j = i->ToElement()->FirstChild();
            OutputFileStream << "## " << j->ToElement()->FirstChild()->ToText()->Value() << std::endl
                             << std::endl;
            j = j->NextSibling();
            for (; j != NULL; j = j->NextSibling())
                OutputFileStream << Output(j->ToElement()) << std::endl;
            OutputFileStream << std::endl;
        }
        OutputFileStream << "## More details" << std::endl
                         << std::endl
                         << "|Name|Value|" << std::endl
                         << "|:---:|:---:|" << std::endl
                         << "|Time Limit|" << ProblemXmlHandle.Child(0).Child(1).Child(1).ToText()->Value() << "|" << std::endl
                         << "|Memory Limit|" << ProblemXmlHandle.Child(0).Child(2).Child(1).ToText()->Value() << "|" << std::endl
                         << "|Input|" << ProblemXmlHandle.Child(0).Child(3).Child(1).ToText()->Value() << "|" << std::endl
                         << "|Output|" << ProblemXmlHandle.Child(0).Child(4).Child(1).ToText()->Value() << "|" << std::endl
                         << std::endl;
        OutputFileStream.close();
    }

    // Open the problem detail file
    if (system(std::string("code-insiders /tmp/Codeforces-" + ProblemID + ".md").c_str()))
        std::cout << "Open file \"/tmp/Codeforces-" << ProblemID << ".md\" failed, please open it manually" << std::endl;
}
void CODEFORCES::SubmitCode(std::string ProblemID) {
    // Get the code
    std::string Code = GetDataFromFileToString("Codeforces/" + ProblemID + ".cpp");

    // Add a number to the code to avoid submitting the same code
    Code += "\n\n// " + std::to_string(time(NULL)) + "\n";

    // Get submit page data
    std::cout << "Getting submit page data... " << std::flush;
    GetDataToFile("https://codeforces.com/problemset/submit");
    std::cout << "Succeed" << std::endl;

    // Submit the code
    int HTTPResponseCode = 0;
    std::cout << "Submitting... " << std::flush;
    GetDataToFile("https://codeforces.com/problemset/submit?csrf_token=" + GetCSRF(),
                  "",
                  "",
                  true,
                  std::string(
                      "csrf_token=" + GetCSRF() +
                      "&ftaa=" + ftaa +
                      "&bfaa=" + bfaa +
                      "&action=submitSolutionFormSubmitted" +
                      "&contestId=" + ProblemID.substr(0, ProblemID.size() - 1) +
                      "&submittedProblemIndex=" + ProblemID.substr(ProblemID.size() - 1) +
                      "&programTypeId=50" +
                      "&source=" + URLEncode(Code) +
                      "&tabSize=4&sourceFile=&_tta=153")
                      .c_str(),
                  NULL,
                  &HTTPResponseCode,
                  FORM);
    if (HTTPResponseCode == 200)
        TRIGGER_ERROR("Submit failed");
    std::cout << "Succeed" << std::endl;

    // Crate a header list
    curl_slist *HeaderList = NULL;
    HeaderList = curl_slist_append(HeaderList,
                                   "Referer: https://codeforces.com/problemset/status/page/1?my=on");

    // Get the submission list page data
    std::cout << "Getting submission ID... " << std::flush;
    GetDataToFile("https://codeforces.com/problemset/status/page/1?my=on");
    std::cout << "Succeed" << std::endl;

    // Parse the submission list
    TiXmlDocument SubmitListXmlDocument;
    SubmitListXmlDocument.Parse(TOOL::TidyHTMLDocument(GetDataFromFileToString()).c_str());
    if (SubmitListXmlDocument.Error())
        TRIGGER_ERROR("Parse submission list error: "s + SubmitListXmlDocument.ErrorDesc());

    // Get the submission ID
    std::string SubmitID = TiXmlHandle(&SubmitListXmlDocument)
                               .FirstChild("html")
                               .FirstChild("body")
                               .Child("div", 3)
                               .Child("div", 4)
                               .FirstChild("div")
                               .Child("div", 3)
                               .Child("div", 5)
                               .FirstChild("table")
                               .Child("tr", 1)
                               .ToElement()
                               ->Attribute("data-submission-id");
    std::cout << "Judging... " << std::flush;

    // Get the submission result
    json result;
    do {
        GetDataToFile("https://codeforces.com/data/submitSource",
                      "",
                      "",
                      true,
                      std::string("submissionId=" + SubmitID +
                                  "&csrf_token=" + GetCSRF()),
                      HeaderList,
                      NULL,
                      FORM);
        result = json::parse(GetDataFromFileToString());
    } while (!result["waiting"].is_null() && result["waiting"].as_string() == "true");
    std::cout << "Succeed" << std::endl;

    // Get the submission result
    int ACNumber = 0;
    int TestNumber = atoi(result["testCount"].as_string().c_str());
    for (int i = 1; i <= TestNumber; i++) {
        // Save the input and output file
        SetDataFromStringToFile("Codeforces/" + ProblemID + "_" + std::to_string(i) + ".in",
                                result["input#" + std::to_string(i)].as_string());
        SetDataFromStringToFile("Codeforces/" + ProblemID + "_" + std::to_string(i) + ".out",
                                result["answer#" + std::to_string(i)].as_string());

        // Print the result
        std::cout << "#" << i << " "
                  << ToNormalName(result["verdict#" + std::to_string(i)].as_string()) << " "
                  << result["timeConsumed#" + std::to_string(i)].as_string() << "ms "
                  << result["memoryConsumed#" + std::to_string(i)].as_string() << "B     "
                  << result["checkerStdoutAndStderr#" + std::to_string(i)].as_string();
        if (result["rejected#" + std::to_string(i)].as_string() == "false")
            ACNumber++;
    }
    std::cout << int(ACNumber * 1.0 / TestNumber) << "pts" << std::endl;
}
