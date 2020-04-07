//
// CLASS: CCommSerial
//
// Author: Steve Kuznicki
//

#ifndef __INCCCommSerial
#define __INCCCommSerial

#pragma pack(push,4)

#ifdef _forLinux

#define CommDllExImport

#include <sys/types.h>

typedef int	HANDLE;
#if	!defined(ERR) || ((ERR) != -1)
#define ERR     (-1)
#endif

#else

#ifdef  EIM_DLL_Compile
#define EIM_DLL_Export
#else
#define EIM_DLL_Import
#endif

#ifdef EIM_DLL_Export
#define CommDllExImport __declspec( dllexport )
#endif

#ifdef EIM_DLL_Import
#define CommDllExImport __declspec( dllimport )
#endif

#ifdef LOCAL_COMM
#undef CommDllExImport
#define CommDllExImport
#endif

#endif

#include "Commobj.h"

enum COMMANDS
{
	CMD_PING = 0,
	CMD_RESET = 1,
	CMD_TELEM_DATA = 2,
	CMD_SPECIAL_COMMAND = 100
};

class CommDllExImport CCommSerial : public CComm {
	private:
		HANDLE m_hComm;
		struct serialStruct {
			unsigned short comPort;
#ifndef _forLinux
			DCB dcbControlBlock;
#endif
			char *pcInitString;
		} m_serialData;

		bool m_bCancelRead;
		unsigned short CRC_Calc(unsigned char *s, unsigned short msglen, unsigned short CRCval);
		unsigned char CRC_Calc8(unsigned char * buf, unsigned short nbytes);
		
		int packet_send();
		int packet_read(bool bResponse = false);
	protected:
		int Connect();
		// int Listen();
		int initSerialComm();
	public:
		// Constructors
		CCommSerial();
		CCommSerial(opMode om);
		CCommSerial(char *configStr, opMode om);
		~CCommSerial();

		// Base Class Member Functions
		// these are the commands that need to be provided for each mode of communication
		int Init(char *configString);
		int Open();
		int Close();
		int Receive(bool response = false);
		int SendSync();
		int Send(int nLoops = DEFAULT_MAX_NAKS);
		bool SetTimeout(int to); 
		int  GetTimeout();

};

#pragma pack(pop)
#endif

