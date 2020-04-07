//
// CLASS: CComm
//
// Author: Steve Kuznicki
//

#ifndef __INCCComm
#define __INCCComm

#pragma pack(push,4)

#ifdef _forLinux

#define CommDllExImport

#include <errno.h>
#include <bool.h>

#else // _forLinux is not defined, use WINDOWS version:

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

#include <windows.h>

#endif // _forLinux, else clause

// MACHINE SPECIFIC DEFINE, set to TRUE or FALSE depending on
// machine architecture (Motorola = FALSE, Intel = TRUE)
// ONLY Supports Big and Little Endian byte ORDER right now
// Typically TRUE = 1, and FALSE = 0 if not defined in your environment
#define LITTLE_ENDIAN true

#define COMMRET_ERROR  -1
#define COMMRET_SUCCESS 0
#define COMMRET_NO_DATA 1
#define COMMRET_TIMED_OUT 2 
#define COMMRET_ALIVE   3

#define COMM_HEADER 'X'

#define FLAG_SIZE			1
#define COMMAND_SIZE		1
#define CRC_SIZE			1
#define LENGTH_SIZE			1
#define HEADER_SIZE			5
#define DATA_OFFSET			5
#define DEFAULT_MAX_NAKS	3
#define MAX_PACKET_SIZE		262
#define PACKET_OVERHEAD		(HEADER_SIZE+CRC_SIZE)
#define CRCTAB_SIZE			256

enum COMM_FLAGS
{
	FLAGS_MSG_TYPE_CMD  = 0x00,
	FLAGS_MSG_TYPE_NAK = 0x01,
	FLAGS_MSG_TYPE_ACK = 0x02,
	FLAGS_DL_DATA_BYTE = 0x04,
	FLAGS_MSG_TYPE_MASK = 0x08
};

enum COMM_ERR_MSGS
{
	ERR_NONE = 0,
	ERR_INVALID_HDR_CRC = 1,
	ERR_INVALID_DATA_CRC = 2,
	ERR_UNSUPPORTED_CMD = 3,
	ERR_INVALID_HDR = 4,
	ERR_INVALID_LENGTH_PARAM = 5,
	ERR_DATA_LENGTH_EXCEEDS_BLK_SIZE = 6,
	ERR_INVALID_FLAGS_COMBINATION = 7,
};

#ifdef _forLinux
#define COMMRET_WOULD_BLOCK 4
#else  // for winsuck
#define COMMRET_WOULD_BLOCK WSAEWOULDBLOCK
//#define EWOULDBLOCK WSAEWOULDBLOCK
#endif

#ifndef NULL
#define NULL 0
#endif

char *ErrorString(int err);

static char *errMsgStr[] = {
	"No Error",
	"Invalid Header CRC",
	"Invalid Data CRC",
	"Unsupported Command",
	"Invalid Header",
	"Invalid Length Parameter",
	"Data Length Exceeds Block Size",
	"Invalid Flags Combination",
	"Special Command Invalid Parameter",
	"Special Command Timed Out",
	"Special Command Failed",
};

const int DEFAULT_IN_BUFF_LEN = 262;
const int DEFAULT_OUT_BUFF_LEN = 262;

class CommDllExImport CComm {
	public:
		enum opMode {opClient = 0, opServer, opSpecial};
	protected:
		unsigned char *inputBuffer, *inPtr;
		unsigned char *outputBuffer, *outPtr;
		int inMaxLen, outMaxLen;
		int inLen, outLen;
		char *argBuffer;
		bool commActive;
		opMode whatIAm;
		bool waiting_for_command;
		bool bSwapData;
		int  m_readTimeout;
		short connectionTimeout;  // time in seconds for connection timeout
		inline bool IamLittleEndian(){return LITTLE_ENDIAN;}
		inline bool NeedDataSwapped(){return bSwapData;}
		unsigned short swapShort(unsigned short value);
		unsigned int swapInt(unsigned int value);
		unsigned int swapTriByte(unsigned int value);
		unsigned long swapLong(unsigned long value);
		unsigned long long swapLongLong(unsigned long long value);
		bool bOpened; // TRUE when link (eg: socket) opened, FALSE when link is not open or was closed.

		// protocol specific vars
		int m_command;
		int m_flags;
		int m_error;

	public:
		// Constructors
		CComm(){argBuffer = NULL;inputBuffer=NULL;outputBuffer=NULL;waiting_for_command=false;bSwapData=true;}
		CComm(opMode om);
		virtual ~CComm();

		// these are the commands that need to be provided for each mode of communication
		virtual int Open();
		virtual int Close();
		virtual int CancelReceive();
		virtual int Reset(int delay);
		virtual int serverAcceptConnections();
		virtual int setBufferSizes(int inSize, int outSize);
		virtual int Receive(bool response = false);
		virtual int SendSync();
		virtual int Send(int test = 1);
		virtual int Init(char *configString) = 0;
       	virtual bool ConnectionIsOpen();
		virtual char *GetErrString();
		virtual bool SetTimeout(int to){ return false; }
		virtual int  GetTimeout(){ return m_readTimeout; }

		// Base Class Member Functions
		inline void SetHeaderInfo(int command, int flags){m_command = command; m_flags = flags;}
		inline int getFlags(){return m_flags;}
		inline int getCommand(){return m_command;}
		inline int getError(){return m_error;}
		inline void setError(int err){m_error = err;}

		inline void swapDataIs(bool sw){bSwapData = sw;}
		inline int getInMaxBufferLen(){return inMaxLen;}
		inline int getOutMaxBufferLen(){return outMaxLen;}
		inline int getInLen(){return inLen;}
		inline int getOutLen(){return outLen;}
		inline unsigned char *outBuffer(){return outputBuffer;}
		inline unsigned char *inBuffer(){return inputBuffer;}
		inline unsigned char *getInPtr(){return inPtr;}
		inline unsigned char *getOutPtr(){return outPtr;}
		inline void resetInBuffer(){inLen = 0;inPtr = &inputBuffer[0];}
		inline void resetOutBuffer(){outLen = 0;outPtr = &outputBuffer[0];}
		inline void setOutLen(int rl){ outLen = rl;return;}
		inline void setOutBuffer(unsigned char *ob){outputBuffer = ob; outPtr = ob;}
		inline void setOutPtr(unsigned char *op){outPtr = op;}
		inline void setInLen(int rl){ inLen = rl;return;}
		inline void setInBuffer(unsigned char *ib){inputBuffer = ib; inPtr = ib;}
		inline void setInPtr(unsigned char *ip){inPtr = ip;}
		inline void setConnectionTimeout(short ct){ connectionTimeout = ct;return;}
		// these functions operate on the buffers so they are common to all
		int AllocateBuffers();
		char *ArgBuffer();
		char		  readChar();			// 8-bit
		unsigned char readUChar();			//
		short		  readShort();			// 16-bit
		unsigned short readUShort();		//
		int		      readTriByte();		// 24-bit
		unsigned int  readUTriByte();		//
		long		  readLong();			// 32-bit
		unsigned long readULong();			//
		long long	  readLongLong();		// 64-bit
		unsigned long long readULongLong();	//
		char		 *readString();			// string
		void		 *readBuffer(int len);	// buffer
		float		  readFloat();			// 32-bit single
		double		  readDouble();			// 64-bit double
		int writeChar(char data);				// 8-bit
		int writeUChar(unsigned char data);		//
		int writeShort(short data);				// 16-bit
		int writeUShort(unsigned short data);	//
		int writeTriByte(int data);				// 24-bit
		int writeUTriByte(unsigned int data);	//
		int writeLong(long data);				// 32-bit
		int writeULong(unsigned long);			//
		int writeLongLong(long long data);		// 64-bit
		int writeULongLong(unsigned long long);	// 
		int writeString(char *data);			// string
		int writeBuffer(char *data, int len);	// buffer
		int writeFloat(float data);				// 32-bit single
		int writeDouble(double data);			// 64-bit double
};

#pragma pack(pop)

#endif
