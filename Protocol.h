#pragma once
#define MAX_MESSAGE_SIZE 30

/*

-----------------------------------------------------------------
struct C2S_Message
{
	unsigned short protocolId = 1;
	char message[MAX_MESSAGE_SIZE];
};

-----------------------------------------------------------------
struct S2C_Message
{
	unsigned short protocolId = 1;
	char message[MAX_MESSAGE_SIZE];
}

*/

enum ProtocolId
{
	// C2S
	C2S_Message = 1,

	// S2C
	S2C_Message = 10001,
};
