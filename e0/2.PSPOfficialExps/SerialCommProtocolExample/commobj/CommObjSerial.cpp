
//
// CLASS: CCommSerial
//
// Author: Steve Kuznicki
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _forLinux
#include <bool.h>
#include <sys/select.h>	
#include <unistd.h>
#endif
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "CommObjSerial.h"
#include "asciidef.h"

// #define VERBOSE_READ_PKT

#ifdef _forLinux // function prototypes
bool ReadFile(HANDLE hFile,char *lpBuffer,long nNumberOfBytesToRead, unsigned long *lpNumberOfBytesRead,void *lpOverlapped);
bool WriteFile(HANDLE hFile,char *lpBuffer,long nNumberOfBytesToWrite, unsigned long *lpNumberOfBytesWritten,void *lpOverlapped);
#endif


CCommSerial::CCommSerial() : CComm(CComm::opServer) 
{
	m_hComm = INVALID_HANDLE_VALUE;
}

CCommSerial::CCommSerial(opMode om) : CComm(om) 
{
	whatIAm = om;
	m_hComm = INVALID_HANDLE_VALUE;
}

CCommSerial::CCommSerial(char *configStr, opMode om) : CComm(om) 
{
	m_hComm = INVALID_HANDLE_VALUE;
	Init(configStr);
}

CCommSerial::~CCommSerial()
{
	// free buffers which were allocated by the Comm class
	if(inputBuffer)
	{
		free(inputBuffer);
		inputBuffer = NULL;
	}
	if(outputBuffer)
	{
		free(outputBuffer);
		outputBuffer = NULL;
	}
	if(argBuffer)
	{
		free(argBuffer);
		argBuffer = NULL;
	}
	if (m_serialData.pcInitString)
	{
		free(m_serialData.pcInitString);
		m_serialData.pcInitString = NULL;
	}
}

int CCommSerial::Init(char *configString)
{
	int rc = COMMRET_SUCCESS;

	m_readTimeout = 200;

	if(strlen(configString) == 0)
	{
		rc = COMMRET_ERROR;
		goto EXIT_INIT;
	}

	// initialize the serial communications
	if(whatIAm == opClient || whatIAm == opServer)
	{
		char cfgstr[300];
		strcpy_s(cfgstr, configString);
#ifndef _forLinux
		char *stmp = NULL;
		int nModeLen = 0;
		stmp = strchr(cfgstr, ':');
		if(stmp){
			stmp[0] = 0;
		}
		m_serialData.comPort = (short)atoi(&(cfgstr[3]));
		stmp[0] = ':';
		if(stmp){
			nModeLen = (int)strlen(cfgstr)+1;
			if ((m_serialData.pcInitString = (char *)malloc(nModeLen)) == NULL)
			{
				rc = COMMRET_ERROR;
				goto EXIT_INIT;
			}
			strncpy_s(m_serialData.pcInitString, nModeLen, cfgstr, nModeLen);
		}
		else{
			m_serialData.pcInitString = NULL;
		}
#else
		m_serialData.pcInitString = configString;
		m_serialData.comPort = atoi(cfgstr);
#endif
	}
	else 
	{
		// if not a client or server, then do NOT init
		rc = COMMRET_ERROR;
		goto EXIT_INIT;
	}

	if((rc = initSerialComm()) == COMMRET_SUCCESS)
		commActive = true;

EXIT_INIT:
	return(rc);
}

// 
// FUNCTION: int initSerialComm(short port)
int CCommSerial::initSerialComm()
{
	int rc = COMMRET_SUCCESS;
#ifndef _forLinux
	// Initialize DCB structure
	if(!BuildCommDCB(m_serialData.pcInitString, &(m_serialData.dcbControlBlock)))
	{
		rc = COMMRET_ERROR;
	}
#else
	// run stty here to set the serial port attributes...
	char setupStr[100];
	sprintf(setupStr,"stty baud=9600 stopb=1 bits=8 par=none < /dev/ttyS%1d",m_serialData.comPort);
	system(setupStr);
#endif

/*
	m_serialData.dcbControlBlock.DCBlength;				// sizeof(DCB) 
	m_serialData.dcbControlBlock.fBinary  = 1;			// binary mode, no EOF check 
	m_serialData.dcbControlBlock.fParity  = 1;			// enable parity checking 
	m_serialData.dcbControlBlock.fOutxCtsFlow = 1;		// CTS output flow control 
	m_serialData.dcbControlBlock.fOutxDsrFlow = 1;		// DSR output flow control 
	m_serialData.dcbControlBlock.fDtrControl = 2;		// DTR flow control type 
	m_serialData.dcbControlBlock.fDsrSensitivity = 1;	// DSR sensitivity 
	m_serialData.dcbControlBlock.fTXContinueOnXoff = 1;	// XOFF continues Tx 
	m_serialData.dcbControlBlock.fOutX =  1;			// XON/XOFF out flow control 
	m_serialData.dcbControlBlock.fInX  = 1;				// XON/XOFF in flow control 
	m_serialData.dcbControlBlock.fErrorChar =  1;		// enable error replacement 
	m_serialData.dcbControlBlock.fNull =  1;			// enable null stripping 
	m_serialData.dcbControlBlock.fRtsControl = 2;		// RTS flow control 
	m_serialData.dcbControlBlock.fAbortOnError = 1;		// abort reads/writes on error 
	m_serialData.dcbControlBlock.fDummy2 = 17;			// reserved 
	m_serialData.dcbControlBlock.wReserved;				// not currently used 
	m_serialData.dcbControlBlock.XonLim;				// transmit XON threshold 
	m_serialData.dcbControlBlock.XoffLim;				// transmit XOFF threshold 
	m_serialData.dcbControlBlock.ByteSize;				// number of bits/byte, 4-8 
	m_serialData.dcbControlBlock.XonChar;				// Tx and Rx XON character 
	m_serialData.dcbControlBlock.XoffChar;				// Tx and Rx XOFF character 
	m_serialData.dcbControlBlock.ErrorChar;				// error replacement character 
	m_serialData.dcbControlBlock.EofChar;				// end of input character 
	m_serialData.dcbControlBlock.EvtChar;				// received event character 
	m_serialData.dcbControlBlock.wReserved1;			// reserved; do not use 
*/
	return(rc);
}

int CCommSerial::Receive(bool bResponse)
{ // option is for blocking or non-blocking
	int rc = COMMRET_SUCCESS;

	if (commActive == false)
		rc = COMMRET_ERROR;

#ifdef _forLinux   // select the serial port to see if data pending first...
	// do a select first to see if there is data there
	fd_set serSet;
	timeval waitFor = {0L,timeout}; // do non-blocking select
	timeval *waitForPtr;
	// these are the two timeval members
	//long    tv_sec;         /* seconds */
	//long    tv_usec;        /* and microseconds */

	if(timeout == -1){
		waitForPtr = NULL;
	}
	else{
		waitForPtr = &waitFor; 
	}

	FD_ZERO(&serSet);	//Initializes the set to the NULL set.
	FD_SET(m_hComm, &serSet);	// Adds descriptor s to set.
	rc = select(m_hComm+1,&serSet,NULL,NULL,waitForPtr);
	// select() returns the number of ready fd's, or zero for timeout, or -1 for error.

	if (rc >= 1) { // normal condition
		rc = packet_read(bResponse);
	}
	else if (rc == 0) { // timed out:
		rc = COMMRET_TIMED_OUT;
	}
	else { // rc < 0; error:
		rc = COMMRET_ERROR;
	}

#else
	rc = packet_read(bResponse);

#ifdef VERBOSE_READ_PKT
	if (rc == COMMRET_ERROR)
		TRACE("Error Receiving\n");
#endif

#endif

	return(rc);
}

int CCommSerial::Send(int nLoops)
{
	int rc = COMMRET_SUCCESS;
	// bool bSuccess = false;
	// unsigned long dwRead;
	// char ch = NAK;
	int flags = 0;
	m_error = COMMRET_ERROR;

	if (commActive == false)
	{
		rc = COMMRET_ERROR;
		goto EXIT_S;
	}
	int maxLoops = nLoops;
	do	/*  Loop until packet received correctly, ACK received  */
	{
		TRACE("Sending Packet x %d\n", (maxLoops - nLoops + 1));
		// clear the flags before sending again
		flags = m_flags;
		rc = packet_send();	/*  send body of command  */
		// if this is a ACK/NAK send, then do NOT wait for response!
		if(m_flags & (FLAGS_MSG_TYPE_NAK|FLAGS_MSG_TYPE_ACK))
			break;
		resetInBuffer();
		TRACE("Waiting for Response Packet x %d\n", (maxLoops - nLoops + 1));

		if ((rc = Receive(true)) == COMMRET_SUCCESS) {
			if (m_flags & FLAGS_MSG_TYPE_NAK) {
				TRACE("Recv x %d: NAK. Error = %d (%s)\n", (maxLoops - nLoops + 1), m_error, ErrorString(m_error));
			}
			else {
				if (m_flags & FLAGS_MSG_TYPE_ACK) {
					TRACE("Recv x %d: ACK\n", (maxLoops - nLoops + 1));
					break;
				}
			}
		}

		m_flags = flags;
		nLoops--;
	}
	while(nLoops > 0);

	// reset the output length and pointer
	resetOutBuffer();

EXIT_S:
	return(rc);
}

int CCommSerial::SendSync()
{
	int rc = COMMRET_SUCCESS;
	unsigned char c = 'S';
	unsigned long  dwWrote;

	if (commActive == false)
	{
		rc = COMMRET_ERROR;
		goto EXIT_SS;
	}

	if(!WriteFile(m_hComm, (char *)&c, 1, &dwWrote, NULL))
	{
		rc = COMMRET_ERROR;
	}

EXIT_SS:
	return(rc);
}

int CCommSerial::Close()
{
	int rc = COMMRET_SUCCESS;

#ifdef _forLinux
	if(close(m_hComm) == 0)
		rc = COMMRET_ERROR;
#else
	if(CloseHandle(m_hComm) == 0)
		rc = COMMRET_ERROR;
#endif
	return(rc);
}

int CCommSerial::Open()
{
	int rc = COMMRET_ERROR;

	if(commActive == true )
	{
		switch(whatIAm)
		{
			case opClient:
				rc = Connect();
				break;
			case opServer:
				rc = Connect();
				break;
			default:
				rc = COMMRET_ERROR;
				break;
		}
	}
	return(rc);
}

int CCommSerial::Connect()
{
	int rc = COMMRET_SUCCESS;

#ifdef _forLinux
	char serStr[20];
	sprintf(serStr,"/dev/ttyS%1d",m_serialData.comPort);
	if((m_hComm = open(serStr,O_RDWR)) == -1){
		rc = COMMRET_ERROR;
	}
#else
	DCB dcb;
	char strPortName[5];
	sprintf_s(strPortName, "COM%.1d", m_serialData.comPort);
	m_hComm = CreateFile((const char *)strPortName,
						 GENERIC_READ | GENERIC_WRITE, 
						 0,		// comm devices must be opened w/exclusive-access
						 NULL,	// no security attrs
						 OPEN_EXISTING,	// comm devices must use OPEN_EXISTING
						 0,		// not overlapped I/O
						 NULL	// hTemplate must be NULL for comm devices
						);

	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		rc = COMMRET_ERROR;
		// MessageBox(NULL,"BAD Handle on CreateFile connect.",NULL,MB_OK);
		MessageBox(NULL,"Another application has this COM port open. \nEither close the application that is using \nthis COM port or choose another COM port.",NULL,MB_OK);
	}
	else
	{
		if(!GetCommState(m_hComm, &dcb))
		{
			rc = COMMRET_ERROR;
			MessageBox(NULL,"Error getting Comm State",NULL,MB_OK);
		}
		else
		{
			dcb.BaudRate = m_serialData.dcbControlBlock.BaudRate;
			dcb.ByteSize = m_serialData.dcbControlBlock.ByteSize;
			dcb.Parity   = m_serialData.dcbControlBlock.Parity;
			dcb.StopBits = m_serialData.dcbControlBlock.StopBits;

			if(!SetCommState(m_hComm, &dcb))
			{
				rc = COMMRET_ERROR;
				char str[100];
				long perr = GetLastError();
				sprintf_s(str, "Error Setting Comm State: %d, %s", perr, strerror(perr) );
				MessageBox(NULL,str,NULL,MB_OK);
			}
			SetTimeout(m_readTimeout);
		}
	}
#endif

	return(rc);
}

#ifdef _forLinux
bool CCommSerial::SetTimeout(int timeout) {
	bool rb = true;
	return rb;
}
int CCommSerial::GetTimeout() {
	return m_readTimeout;
}
#else
bool CCommSerial::SetTimeout(int timeout){
	COMMTIMEOUTS cto;
	bool rb = true;
	if (m_hComm != INVALID_HANDLE_VALUE){
		if(!GetCommTimeouts(m_hComm, &cto))
		{
			rb = false;
			MessageBox(NULL,"Error getting Comm Timeouts",NULL,MB_OK);
		}
		else
		{
			cto.ReadTotalTimeoutConstant = timeout;
			cto.ReadTotalTimeoutMultiplier = 1;

			if(!SetCommTimeouts(m_hComm, &cto))
			{
				rb = false;
				char str[100];
				long perr = GetLastError();
				sprintf_s(str, "Error Setting Comm Timeouts: %d, %s", perr, strerror(perr) );
				MessageBox(NULL,str,NULL,MB_OK);
			}
		}
	}
	return rb;
}

int CCommSerial::GetTimeout(){
	COMMTIMEOUTS cto;
	if (m_hComm != INVALID_HANDLE_VALUE){
		if(!GetCommTimeouts(m_hComm, &cto))
		{
			MessageBox(NULL,"Error getting Comm Timeouts",NULL,MB_OK);
		}
		else
		{
			m_readTimeout = cto.ReadTotalTimeoutConstant;
		}
	}
	return m_readTimeout;
}
#endif

unsigned short CCommSerial::CRC_Calc(unsigned char * s, unsigned short msglen, unsigned short CRCval)
{
	short i;

	i = msglen;
	while (--i >= 0)
	{
		CRCval += (unsigned short)(*s++);
	}

	return (CRCval);
}

unsigned char CCommSerial::CRC_Calc8(unsigned char * buf, unsigned short nbytes)
{
	unsigned char poly, j, bit_point, crc_reg = ~0;
	unsigned short i;

	for (i = 0; i < nbytes; ++i, ++buf)
	{
		for (j = 0, bit_point = 0x80; j<8; ++j, bit_point >>= 1)
		{
			if (bit_point & *buf)        // case for new bit =1
			{
				poly = (crc_reg & 0x80) ? 1 : 0x1c;
				crc_reg = ((crc_reg << 1) | 1) ^ poly;
			}
			else                    // case for new bit =0
			{
				poly = (crc_reg & 0x80) ? 0 : 0x1d;
				crc_reg = (crc_reg << 1) ^ poly;
			}
		}
	}
	return ~crc_reg;
}

int CCommSerial::packet_read(bool bResponse)
{
	int rc = COMMRET_SUCCESS;
	unsigned long dwRead, dwWrote, totalRead;
	short packetLen;
	unsigned char crc8a = 0;
	unsigned char crc8b = 0;
	int hdrIdx = 0;
	bool resync = true;
	int dataLen, max, readHdrAttempts = 0;
	unsigned char cBuf[HEADER_SIZE] = { '0', '1', '2', '3', '4' };
	unsigned char sentinel[HEADER_SIZE] = { '0', '1', '2', '3', '4' };
	static unsigned char nak[HEADER_SIZE] = { COMM_HEADER, FLAGS_MSG_TYPE_NAK | FLAGS_DL_DATA_BYTE, 0, 0, 0 };

	/*  maximum times to try reading packet  */
	max = DEFAULT_MAX_NAKS;
	inPtr = &inputBuffer[0];
	m_bCancelRead = false;
#ifdef VERBOSE_READ_PKT
	TRACE("START packet_read \n");
#endif
	do
	{
#ifdef VERBOSE_READ_PKT
		TRACE("Reading Header : Size = %d (x %d)\n", HEADER_SIZE, (DEFAULT_MAX_NAKS - max + 1));
#endif
		ReadFile(m_hComm, (char *)&cBuf[0], 1, &dwRead, NULL);
		int resyncCount = inMaxLen + 1;
		while (cBuf[0] != COMM_HEADER && resyncCount-- > 0) {
			ReadFile(m_hComm, (char *)&cBuf[0], 1, &dwRead, NULL);
		}
		hdrIdx = 1;
		if (!ReadFile(m_hComm, (char *)&cBuf[hdrIdx], HEADER_SIZE-hdrIdx, &dwRead, NULL)) {
			if ((rc = GetLastError()) == 0) {
				if (m_bCancelRead)
					break;
				continue;
			}
			rc = COMMRET_ERROR;
			break;
		}
		if (dwRead != HEADER_SIZE-hdrIdx) {
			rc = GetLastError();
			TRACE("Read Attempt did not read HEADER_SIZE (rc=%d). Trying AGAIN (Read %d bytes).\n", rc, dwRead);
			if (rc == 0) {
				totalRead = dwRead+hdrIdx;
				hdrIdx += dwRead;
				while (++readHdrAttempts <= 20 && totalRead != HEADER_SIZE) {
					TRACE("    Read Header Attempt %d/20\n", readHdrAttempts);
					if (!ReadFile(m_hComm, (char *)&cBuf[hdrIdx], HEADER_SIZE - totalRead, &dwRead, NULL)) {
						if ((rc = GetLastError()) == 0) {
							if (m_bCancelRead)
								break;
							continue;
						}
						else { // Read Comm error
							rc = COMMRET_ERROR;
							break;
						}
					}
					totalRead += dwRead;
					hdrIdx += dwRead;
					TRACE("    Read: %d Total: %d ->cBuf[%d]\n", dwRead, totalRead, hdrIdx);
				}
			}
			else {
				rc = COMMRET_ERROR;
				continue;
			}
		}
		if (!memcmp(&cBuf[0], &sentinel[0], HEADER_SIZE)) {
			rc = GetLastError();
#ifdef VERBOSE_READ_PKT
			TRACE("Read Attempt did not read Valid Buffer (rc=%d). Trying AGAIN.\n", rc);
#endif
			rc = COMMRET_ERROR;
			continue;
		}
		m_flags   = cBuf[1];
		m_command = cBuf[2];
		packetLen = cBuf[3];
		crc8a     = cBuf[4];

		TRACE("READ Header: %02X %02X %02X %02X %02X \n",
			cBuf[0],
			cBuf[1],
			cBuf[2],
			cBuf[3],
			cBuf[4]);

		nak[2] = m_command;
		nak[4] = CRC_Calc8(nak, 4);

		// if NOT a ACK or NAK, then check validity first...
		// check validity of header
		if (cBuf[0] != COMM_HEADER) {
			TRACE("*** Header Corrupt. header = %c\n", cBuf[0]);
			rc = COMMRET_ERROR;
			if (!bResponse) {
				TRACE("*** sending NAK, Error = 0xEE\n");
				nak[3] = ERR_INVALID_HDR; //  0xEE;
				WriteFile(m_hComm, &nak[0], HEADER_SIZE, &dwWrote, NULL);/*  send not-acknowledge, reread packet  */
				continue;
			}
		}

		// check Header CRC
		crc8b = CRC_Calc8(&cBuf[0], 4);
		if (crc8a != crc8b) {
			/*  Checksum not correct  */
			TRACE("*** Header CRC incorrect, calc = %04x, read = %04x\n", crc8b, crc8a);
			rc = COMMRET_ERROR;
			if (!bResponse) {
				TRACE("*** sending NAK, Error = 0x02\n");
				/*  send not-acknowledge, reread packet  */
				nak[3] = ERR_INVALID_HDR_CRC;
				if (!WriteFile(m_hComm, &nak[0], HEADER_SIZE, &dwWrote, NULL))/*  send not-acknowledge, reread packet  */
				{
					continue;
				}
			}
		}
		// reset the inLen
		inLen = 0;
		if (m_flags & FLAGS_DL_DATA_BYTE) {
			// save the single data byte in the Error field
			m_error = cBuf[3];
#ifdef VERBOSE_READ_PKT
			TRACE("Single Data Byte (0x%x = %s). Return COMMRET_SUCCESS.\n", m_error, ErrorString(m_error));
#endif
			rc = COMMRET_SUCCESS;
			break;
		}
		else { // copy the data into the input buffer
			m_error = 0;
			/*  Read body of command  */
			dataLen = packetLen;
			if (dataLen > inMaxLen)
			{
				/*  inBuffer too small for all characters  */
				TRACE("*** Buffer too small, size = %d, data = %d\n", inMaxLen, dataLen);
				TRACE("*** sending NAK, Error = 0x03\n");
				nak[3] = ERR_DATA_LENGTH_EXCEEDS_BLK_SIZE; // 0xEF;
				if (!WriteFile(m_hComm, &nak[0], HEADER_SIZE, &dwWrote, NULL))/*  send not-acknowledge, reread packet  */
				{
					rc = COMMRET_ERROR;
					continue;
				}
			}
			else
			{
				inLen = dataLen;
				totalRead = 0;
				// NOTE: need to check - if NO data - do we still have a CRC? (of 0)
				if (inLen > 0) {
					TRACE("Reading Data Payload: Size = %d ( + CRC_SIZE of %d)\n", dataLen, CRC_SIZE);
					if (!ReadFile(m_hComm, (char *)inputBuffer, (dataLen + CRC_SIZE), &dwRead, NULL)) {
						rc = COMMRET_ERROR;
						break;
					}
					totalRead = dwRead;
					if (dwRead != (dataLen + CRC_SIZE)) {
						int toRead = (dataLen + CRC_SIZE) - totalRead;
						TRACE("ERROR. Did NOT Read in (dataLen+CRC_SIZE) = %d.  Read %d bytes.\n", (dataLen + CRC_SIZE), dwRead);
						int nLoops = 10;
						while (totalRead != (dataLen + CRC_SIZE)) {
							if (nLoops-- == 0) {
								nLoops = -1;
								break;
							}
							if (!ReadFile(m_hComm, (char *)&inputBuffer[totalRead], toRead, &dwRead, NULL)) {
								nLoops = -1;
								break;
							}
							totalRead += dwRead;
							toRead = (dataLen + CRC_SIZE) - totalRead;
						}
						if (nLoops == -1) {
							rc = COMMRET_ERROR;
							break;
						}
					}
					crc8a = inputBuffer[dataLen];
					crc8b = CRC_Calc8(inputBuffer, dataLen);

					rc = COMMRET_SUCCESS;
					/*  Verify CRC  */
					if (crc8a == crc8b)
					{
						/*  the upper protocol needs to send acknowledge */
						break;
					}
					TRACE("*** CRC incorrect, read = %04x, calc = %04x\n", crc8a, crc8b);
					if (!bResponse) {
						/*  Checksum not correct  */
						TRACE("*** sending NAK, Error = 0x04\n");
						/*  send not-acknowledge, reread packet  */
						nak[3] = ERR_INVALID_DATA_CRC;
						if (!WriteFile(m_hComm, &nak[0], HEADER_SIZE, &dwWrote, NULL))/*  send not-acknowledge, reread packet  */
						{
							rc = COMMRET_ERROR;
							continue;
						}
					}
					else
					{
						TRACE("*** CRC incorrect on a ACK/NAK response, read = %04x, calc = %04x\n", crc8a, crc8b);
						rc = COMMRET_ERROR;
					}
				}
				else
				{
#ifdef VERBOSE_READ_PKT
					TRACE("No Input Buffer Length. Returning COMMRET_SUCCESS.\n");
#endif
					rc = COMMRET_SUCCESS;
					break;
				}
			}
		}
	} while (--max);

#ifdef VERBOSE_READ_PKT
	TRACE("END packet_read (rc = %d)\n", rc);
#endif

	return rc;
}

int CCommSerial::packet_send()
{
	int rc = COMMRET_SUCCESS;
	unsigned char pchPacketBuffer[MAX_PACKET_SIZE];
	short packetLen;
	unsigned short crc1 = 0;
	unsigned long dwWrote;
	unsigned char crc8;

	TRACE("START packet_send (buffer: %6.6s)\n", outputBuffer);

	//packetLen = outLen + PACKET_OVERHEAD;	/*  send 2 bytes for byte count  */
	//pchPacketBuffer[0]   = (unsigned char)packetLen;
	pchPacketBuffer[0] = COMM_HEADER;					/*  header character  */
	pchPacketBuffer[1] = (unsigned char)m_flags;		/*  flag character  */
	pchPacketBuffer[2] = (unsigned char)m_command;	/*  command character  */
	pchPacketBuffer[3] = (unsigned char)outLen;		/*  byte count  (or Single Data Byte) */
	crc8 = CRC_Calc8(pchPacketBuffer, 4);
	pchPacketBuffer[4] = (unsigned char)crc8;			/*  Header CRC */

	if (outLen > 0) {
		packetLen = HEADER_SIZE + outLen + CRC_SIZE; // header size + outlen + data crc8
	}
	else {
		packetLen = HEADER_SIZE;
	}

	// check to see if datalen field is length or a data byte
	crc8 = 0;
	if (!(m_flags & FLAGS_DL_DATA_BYTE)) {

		if (outLen > 0) {
			TRACE("Copying Data Payload into outBuffer (size=%d) \n", outLen);
			memcpy(pchPacketBuffer + DATA_OFFSET, outputBuffer, outLen);
			// Calculate CRC value
			crc8 = CRC_Calc8(outputBuffer, outLen);
		}
	}
	else {
		pchPacketBuffer[3] = (unsigned char)m_error;
		// Calculate CRC value
		crc8 = CRC_Calc8(outputBuffer, outLen);
	}

	// Write CRC value to buffer
	pchPacketBuffer[DATA_OFFSET + outLen] = (unsigned char)crc8;			/*  Header CRC */

	TRACE("SEND Header: %02X %02X %02X %02X %02X : Data CRC : %02X \n",
		pchPacketBuffer[0],
		pchPacketBuffer[1],
		pchPacketBuffer[2],
		pchPacketBuffer[3],
		pchPacketBuffer[4],
		pchPacketBuffer[DATA_OFFSET + outLen]);

	// Write Buffer
	if (!WriteFile(m_hComm, (char *)pchPacketBuffer, packetLen, &dwWrote, NULL))
	{
		rc = COMMRET_ERROR;
		goto EXIT_PS;
	}
	if (dwWrote != (unsigned long)(packetLen))
	{
		rc = COMMRET_ERROR;
		TRACE("ERROR. number bytes in buffer != number sent (%d)\n", dwWrote);
	}
EXIT_PS:
	TRACE("END packet_send \n");
	return(rc);
}


#ifdef _forLinux
bool ReadFile(	HANDLE hFile,				// handle of file to read 
				char *lpBuffer,				// address of buffer that receives data 
				long nNumberOfBytesToRead,	// number of bytes to read 
				unsigned long *lpNumberOfBytesRead,	// address of number of bytes read 
				void *lpOverlapped			// address of structure for data 
){
	bool rc = true;
	lpOverlapped = lpOverlapped;
	int localRc = 0;
	int bytesToRead = nNumberOfBytesToRead;
	*lpNumberOfBytesRead = 0;

	while(*lpNumberOfBytesRead < nNumberOfBytesToRead){
		localRc = read((int)hFile, &lpBuffer[*lpNumberOfBytesRead], bytesToRead);
		if(localRc == -1){
			if(errno != EINTR){ // read was interrupted before it could read anything...
				rc = false;
				break;
			}
		}
		else{
			*lpNumberOfBytesRead += localRc;
			bytesToRead -= localRc;
		}
	}
	// last check for number of bytes actually read
	if(*lpNumberOfBytesRead != nNumberOfBytesToRead)
		rc = false;

	return(rc);
}

bool WriteFile( HANDLE hFile,				// handle to file to write to 
				char *lpBuffer,				// pointer to data to write to file 
				long nNumberOfBytesToWrite,	// number of bytes to write 
				unsigned long *lpNumberOfBytesWritten,// pointer to number of bytes written 
				void *lpOverlapped			// pointer to structure needed for overlapped I/O 
){
	bool rc = true;
	lpOverlapped = lpOverlapped;
	int localRc = 0;
	int bytesToWrite = nNumberOfBytesToWrite;

	*lpNumberOfBytesWritten = 0;

	while(*lpNumberOfBytesWritten < nNumberOfBytesToWrite){
		localRc = write((int)hFile,&lpBuffer[*lpNumberOfBytesWritten], bytesToWrite);
		if(localRc == -1){
			if(errno != EINTR){ // write was interrupted before it could write anything...
				rc = false;
				break;
			}
		}
		else{
			*lpNumberOfBytesWritten += localRc;
			bytesToWrite -= localRc;
		}
	}
	// last check to see if total bytes written are actually written
	if(*lpNumberOfBytesWritten != nNumberOfBytesToWrite)
		rc = false;

	return(rc);
}
#endif