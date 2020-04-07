//
// CLASS: CComm
//
// Author: Steve Kuznicki
//
// this is the file containing the Comm Object's member functions

#include "stdafx.h"

#ifdef _forLinux
#include <malloc.h>
#include <string.h>
#else
#include <AfxWin.h>
#endif

#include <stdio.h>
#include <time.h>
#include "Commobj.h"

char *ErrorString(int err) {
	if (err >= 0 && err <= (sizeof(errMsgStr) / sizeof(char*))) {
		return errMsgStr[err];
	}
	return "Unknown Error";
}

#ifndef _forLinux
void errorMsg(char *fn, int ln, char *format, ...)
{
	va_list  argptr;
	char str[500];
	CString fStr;

	va_start( argptr, format );
	vsprintf( str, format, argptr );
	va_end( argptr );

	fStr.Format("Error: %s File %s, Line %d",str, fn, ln);
	fprintf(stderr,"%s\n",fStr);
	MessageBox(NULL, fStr, "Communication Error", MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION);
	return;
}
#endif

// message definition
//
//      byte 0:     M  (COMM_HEADER)
//      byte 1:     flags
//      byte 2:     command
//      byte 3:     data length (or 1 data byte - see flags)
//      byte 4:     header crc8
//
//      byte 4...n: data
//      byte n+1:   data crc8
//
// note:  all values are BIG endian
//

// Flags Definitions...
//
//      7 6 5 4 3 2 1 0
//      x x x x x x x x
//      | | | | | | |_|_ 00: message is a  command
//      | | | | | |      01: message is a  NAK
//      | | | | | |      10: message is an ACK
//      | | | | | |      11: reserved
//      | | | | | |          
//      | | | | | |_____ 0: data length field contains length
//      | | | | |        1: data length field contains 1 data byte (or err code for NAK)
//      | | | | |
//      |_|_|_|_|_______ 0: reserved
//                       1: reserved

// Constructors
CComm::CComm(opMode om){
	argBuffer = NULL;
	inputBuffer=NULL;
	outputBuffer=NULL;
	waiting_for_command=false;
	bSwapData=true;
	whatIAm = om;
	commActive = false;
	bOpened = false;
	m_error = 0;
	setConnectionTimeout(1);
	setBufferSizes(DEFAULT_IN_BUFF_LEN, DEFAULT_OUT_BUFF_LEN);
}

// Destructors
CComm::~CComm(){
	//  Buffers which were allocated in AllocateBuffers()
	//  are free'd in the individual sub-classes.
}

// Member Functions
int CComm::AllocateBuffers(){
	int rc = COMMRET_SUCCESS;
    if(inputBuffer != NULL){
		free(inputBuffer);
		inputBuffer = NULL;
	}
    if((inputBuffer = (unsigned char *)malloc(inMaxLen)) == NULL){
		rc = COMMRET_ERROR; // don't exit yet, try the outputBuffer
	}
    if(outputBuffer != NULL){
		free(outputBuffer);
		outputBuffer = NULL;
	}
    if((outputBuffer = (unsigned char *)malloc(outMaxLen)) == NULL){
		rc = COMMRET_ERROR;
		goto EXIT_AB;
	}
EXIT_AB:
	return(rc);
}

int CComm::setBufferSizes(int inSize, int outSize){
	int rc = COMMRET_SUCCESS;
    inMaxLen = inSize;
    outMaxLen = outSize;
	AllocateBuffers();
	return(rc);
}

char *CComm::ArgBuffer(){
    if(!argBuffer)
        argBuffer = (char *)malloc(inMaxLen);
    return argBuffer;
}


int CComm::Close(){
	int rc = COMMRET_SUCCESS;
	return(rc);
}

int CComm::Open(){
	int rc = COMMRET_SUCCESS;
	return(rc);
}

bool CComm::ConnectionIsOpen(){
	return bOpened;
}

int CComm::CancelReceive(){
	int rc = COMMRET_SUCCESS;
	return(rc);
}

int CComm::serverAcceptConnections(){
	int rc = COMMRET_SUCCESS;
	return(rc);
}

int CComm::Receive(bool bResponse){ // option is for checking for commmand for responses
	int rc = COMMRET_SUCCESS;
	if(commActive == false){
		rc = COMMRET_ERROR;
	}
	// to avoid compiler warning:
	bResponse = bResponse;
	return(rc);
}

int CComm::Send(int test){
	int rc = COMMRET_SUCCESS;
	if(commActive == false){
		rc = COMMRET_ERROR;
	}
	return(rc);
}

int CComm::SendSync(){
	int rc = COMMRET_SUCCESS;
	if(commActive == false){
		rc = COMMRET_ERROR;
	}
	return(rc);
}

int CComm::Reset(int delay){
	int rc = COMMRET_SUCCESS;

#ifdef _forLinux
	//  from <time.h>: struct timespec { long tv_sec, tv_nsec; } ;
	struct timespec tspec;
	tspec.tv_sec = 0;
	tspec.tv_nsec = delay*1000; // '*1000' converts millisecs to nanoseconds
	nanosleep( &tspec, NULL ); //ignore the result code; may get no sleep
#else
    Sleep(delay);
#endif

	return(rc);
}

char * CComm::GetErrString(){
	return NULL;
}

char CComm::readChar(){
	char rval = 0;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		rval = (char)inPtr[0];
		inPtr += sizeof(char);
	}
	return(rval);
}

unsigned char CComm::readUChar(){
	unsigned char rval = 0;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		rval = (unsigned char)inPtr[0];
		inPtr += sizeof(char);
	}
	return(rval);
}

short CComm::readShort(){
	short rval = 0;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		rval = (short)inPtr;
		memcpy(&rval,inPtr,sizeof(short));
		inPtr += sizeof(short);
	}
	if(IamLittleEndian() && NeedDataSwapped()){
		rval = (signed short)swapShort((unsigned short)rval);
	}
	return(rval);
}

unsigned short CComm::readUShort(){
	unsigned short rval = 0;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		memcpy(&rval,inPtr,sizeof(short));
		inPtr += sizeof(short);
	}
	if(IamLittleEndian() && NeedDataSwapped()){
		rval = (unsigned short)swapShort((unsigned short)rval);
	}
	return(rval);
}

int CComm::readTriByte(){
	long rval = 0L;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		memcpy(&rval,inPtr,3);
		inPtr += 3;
	}
	if(IamLittleEndian() && NeedDataSwapped()){
		rval = (signed int)swapTriByte((unsigned int)rval);
	}
	return(rval);
}

unsigned int CComm::readUTriByte(){
	unsigned int rval = 0L;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		memcpy(&rval,inPtr,3);
		inPtr += 3;
	}
	if(IamLittleEndian() && NeedDataSwapped()){
		rval = (unsigned int)swapTriByte((unsigned int)rval);
	}
	return(rval);
}

long CComm::readLong(){
	long rval = 0L;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		memcpy(&rval,inPtr,sizeof(long));
		inPtr += sizeof(long);
	}
	if(IamLittleEndian() && NeedDataSwapped()){
		rval = (signed long)swapLong((unsigned long)rval);
	}
	return(rval);
}

unsigned long CComm::readULong(){
	unsigned long rval = 0L;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		memcpy(&rval,inPtr,sizeof(long));
		inPtr += sizeof(long);
	}
	if(IamLittleEndian() && NeedDataSwapped()){
		rval = (unsigned long)swapLong((unsigned long)rval);
	}
	return(rval);
}

long long CComm::readLongLong() {
	long long rval = 0L;

	if ((char *)inPtr <= (char *)(inputBuffer + inMaxLen - 1)) {
		memcpy(&rval, inPtr, sizeof(long long));
		inPtr += sizeof(long long);
	}
	if (IamLittleEndian() && NeedDataSwapped()) {
		rval = (signed long long)swapLongLong((unsigned long long)rval);
	}
	return(rval);
}

unsigned long long CComm::readULongLong() {
	unsigned long long rval = 0L;

	if ((char *)inPtr <= (char *)(inputBuffer + inMaxLen - 1)) {
		memcpy(&rval, inPtr, sizeof(long long));
		inPtr += sizeof(long long);
	}
	if (IamLittleEndian() && NeedDataSwapped()) {
		rval = (unsigned long long)swapLongLong((unsigned long long)rval);
	}
	return(rval);
}


char *CComm::readString(){
	char *rval = NULL;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		rval = (char *)inPtr;
		while(inPtr[0]){
			if((char *)inPtr > (char *)(inputBuffer+inMaxLen-1)){
				break;
			}
			inPtr++;
		}
		inPtr++;
	}
	return(rval);
}

void *CComm::readBuffer(int len){
	void *rval = NULL;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		rval = (char *)inPtr;
		memcpy(rval, inPtr, len);
		inPtr += len;
	}
	return(rval);
}

float CComm::readFloat(){
	float rval = (float)0.0;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		memcpy(&rval,inPtr,sizeof(float));
		inPtr += sizeof(float);
	}
	return(rval);
}

double CComm::readDouble(){
	double rval = 0.0;

	if((char *)inPtr <= (char *)(inputBuffer+inMaxLen-1)){
		memcpy(&rval,inPtr,sizeof(double));
		inPtr += sizeof(double);
	}
	return(rval);
}

int CComm::writeChar(char data){
	int rc = COMMRET_SUCCESS;

	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-1)){
		outPtr[0] = data;
		outPtr += sizeof(char);
		outLen += sizeof(char);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeUChar(unsigned char data){
	int rc = COMMRET_SUCCESS;

	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-1)){
		outPtr[0] = data;
		outPtr += sizeof(char);
		outLen += sizeof(char);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeShort(short data){
	int rc = COMMRET_SUCCESS;

	if(IamLittleEndian() && NeedDataSwapped()){
		data = (signed short)swapShort((unsigned short)data);
	}
	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-sizeof(short))){
		memcpy(outPtr,(const void *)&data,sizeof(short));
		outPtr += sizeof(short);
		outLen += sizeof(short);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeUShort(unsigned short data){
	int rc = COMMRET_SUCCESS;

	if(IamLittleEndian() && NeedDataSwapped()){
		data = (unsigned short)swapShort((unsigned short)data);
	}
	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-sizeof(short))){
		memcpy(outPtr,(const void *)&data,sizeof(short));
		outPtr += sizeof(short);
		outLen += sizeof(short);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

// Write three bytes of signed data
int CComm::writeTriByte(int data){
	int rc = COMMRET_SUCCESS;
	if(IamLittleEndian() && NeedDataSwapped()){
		data = (signed int)swapTriByte((unsigned int)data);
	}
	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-3)){
		memcpy(outPtr,(const void *)&data, 3);
		outPtr += 3;
		outLen += 3;
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

// Write three bytes of unsigned data
int CComm::writeUTriByte(unsigned int data){
	int rc = COMMRET_SUCCESS;

	if(IamLittleEndian() && NeedDataSwapped()){
		data = (unsigned int)swapTriByte((unsigned int)data);
	}
	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-3)){
		memcpy(outPtr,(const void *)&data, 3);
		outPtr += 3;
		outLen += 3;
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeLong(long data){
	int rc = COMMRET_SUCCESS;

	if(IamLittleEndian() && NeedDataSwapped()){
		data = (signed long)swapLong((unsigned long)data);
	}
	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-sizeof(long))){
		memcpy(outPtr,(const void *)&data,sizeof(long));
		outPtr += sizeof(long);
		outLen += sizeof(long);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeULong(unsigned long data){
	int rc = COMMRET_SUCCESS;

	if(IamLittleEndian() && NeedDataSwapped()){
		data = (unsigned long)swapLong((unsigned long)data);
	}
	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-sizeof(long))){
		memcpy(outPtr,(const void *)&data,sizeof(long));
		outPtr += sizeof(long);
		outLen += sizeof(long);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeLongLong(long long data) {
	int rc = COMMRET_SUCCESS;

	if (IamLittleEndian() && NeedDataSwapped()) {
		data = (signed long long)swapLongLong((unsigned long long)data);
	}
	if ((char *)outPtr <= (char *)(outputBuffer + outMaxLen - sizeof(long long))) {
		memcpy(outPtr, (const void *)&data, sizeof(long long));
		outPtr += sizeof(long long);
		outLen += sizeof(long long);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeULongLong(unsigned long long data) {
	int rc = COMMRET_SUCCESS;

	if (IamLittleEndian() && NeedDataSwapped()) {
		data = (unsigned long long)swapLongLong((unsigned long long)data);
	}
	if ((char *)outPtr <= (char *)(outputBuffer + outMaxLen - sizeof(long long))) {
		memcpy(outPtr, (const void *)&data, sizeof(long long));
		outPtr += sizeof(long long);
		outLen += sizeof(long long);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeString(char *data){
	int rc = COMMRET_SUCCESS;

	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-strlen(data))){
		strcpy((char *)outPtr,data);
		outPtr += strlen(data);
		outLen += (int)strlen(data);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeBuffer(char *data, int len){
	int rc = COMMRET_SUCCESS;

	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-len)){
		memcpy((char *)outPtr,data,len);
		outPtr += len;
		outLen += len;
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeFloat(float data){
	int rc = COMMRET_SUCCESS;

	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-sizeof(float))){
		memcpy(outPtr,(const void *)&data,sizeof(float));
		outPtr += sizeof(float);
		outLen += sizeof(float);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}

int CComm::writeDouble(double data){
	int rc = COMMRET_SUCCESS;

	if((char *)outPtr <= (char *)(outputBuffer+outMaxLen-sizeof(double))){
		memcpy(outPtr,(const void *)&data,sizeof(double));
		outPtr += sizeof(double);
		outLen += sizeof(double);
	}
	else
		rc = COMMRET_ERROR;
	return(rc);
}


// this does a SAFE short 16-bit swap
// v = (((x & 0xff00) >> 8) |
//      ((x & 0x00ff) << 8));
unsigned short CComm::swapShort(unsigned short value){
	register unsigned short v = 0;
	v = value&0xff;
	v <<= 8;
	v += ((value>>8)&0xff);
	return(v);
}

// this does a SAFE int 32-bit swap
unsigned int CComm::swapInt(unsigned int value){
	return(swapLong((unsigned long)value));
}

// this does a SAFE 24-bit swap
// v = (((x & 0xff0000) >> 16) |
//      ((x & 0x00ff00)      ) |
//      ((x & 0x0000ff) << 16));
unsigned int CComm::swapTriByte(unsigned int value){
	register unsigned int v = value;
	v = ((v & 0xff) << 16) | (v & 0xff00) | ((v & 0xff0000) >> 16);
	return(v);
}

// this does a SAFE long 32-bit swap
// v = (((x & 0xff000000) >> 24) |
//      ((x & 0x00ff0000) >> 8)  |
//      ((x & 0x0000ff00) << 8)  |
//      ((x & 0x000000ff) << 24));
unsigned long CComm::swapLong(unsigned long value){
	register unsigned long v = 0;
	v = value&0xffff;
	v = (unsigned short)swapShort((unsigned short)v);
	v <<= 16;
	value >>= 16;
	v += (unsigned short)swapShort((unsigned short)value);
	return(v);
}

// this does a SAFE long 64-bit swap
//v = (((x & 0xff00000000000000ULL) >> 56) |
//     ((x & 0x00ff000000000000ULL) >> 40) |
//     ((x & 0x0000ff0000000000ULL) >> 24) |
//     ((x & 0x000000ff00000000ULL) >> 8)  |
//     ((x & 0x00000000ff000000ULL) << 8)  |
//     ((x & 0x0000000000ff0000ULL) << 24) |
//     ((x & 0x000000000000ff00ULL) << 40) |
//     ((x & 0x00000000000000ffULL) << 56));
unsigned long long CComm::swapLongLong(unsigned long long value) {
	register unsigned long long v = 0;
	v = value & 0xffffffff;
	v = (unsigned long)swapLong((unsigned long)v);
	v <<= 32;
	value >>= 32;
	v += (unsigned long)swapLong((unsigned long)value);
	return(v);
}
