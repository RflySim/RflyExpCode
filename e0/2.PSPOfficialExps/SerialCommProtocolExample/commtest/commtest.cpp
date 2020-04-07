// commtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "commobj.h"
#include "commobjserial.h"

using namespace std;

CComm *g_comm;

float gVersion = 1.0;
bool  gbInit = false;

static int membyte = 0;

bool StartTx() {
	bool rc = false;
	bool done = false;
	int numch, currNum;
	char hdrkey = 'A';
	int count = 0, frame = 0, interval = 100;
	char kp = 'a';
	float ch[30] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
 					 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
 					 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	cout << "Enter in configuration to send : " << endl;
	cout << "  Number Max Channels : ";
	cin >> numch;
	numch = min(numch, 30);
	cout << "  Transmit interval in millisec : ";
	cin >> interval;
	cout << "Sending " << numch << " channels per packet every " << interval << " milliseconds" << endl;
	cout << "Press any key to start transmitting...Press 'q' to quit." << endl;
	_getch();
	// start transmiting. Channel number value is channel
	currNum = 1;
	while (!done) {
		//--------------------------------------------------------
		//  THIS IS THE CODE THAT CREATES THE DATA PACKET AND SEND
		g_comm->resetOutBuffer();
		g_comm->SetHeaderInfo(CMD_TELEM_DATA, FLAGS_MSG_TYPE_CMD);
		g_comm->writeBuffer("PX4HD", 5);
		g_comm->writeChar(hdrkey);
		g_comm->writeUShort((unsigned short)currNum);
		for (int idx = 0; idx < currNum; idx++) {
			float v = ch[idx] + (float)(count*frame);
			g_comm->writeFloat(v);
		}
		TRACE("SENDING: PX4HD%c NumCh:%d\n", hdrkey, currNum);
		g_comm->Send(5); // 5 retries!
		//--------------------------------------------------------
		// EXAMPLE: SEND PING CMD
		//g_comm->resetOutBuffer();
		//g_comm->SetHeaderInfo(CMD_PING, FLAGS_MSG_TYPE_CMD);
		//g_comm->writeBuffer("PING", 4);
		//g_comm->writeULong(counter++);
		//g_comm->Send(); 
		//--------------------------------------------------------
		if(currNum++ == numch)
			currNum = 1;		
		if (hdrkey == 'Z') {
			hdrkey = 'A';
		}
		else {
			hdrkey++;
		}
		if (_kbhit()) {
			kp = _getch();
			if (kp == 'q')
				done = true;
			else
				cout << "KeyPress " << kp << ". Press 'q' to quit." << endl;
		}
		count++;
		if (count == 10) {
			cout << "Tx+" << count << "[" << frame << "]" << endl;
			count = 0;
			frame++;
		}
		Sleep(interval);
	}
	return rc;
}

bool StartRx() {
	int rc = COMMRET_NO_DATA;
	bool done = false;
	int numch;
	unsigned short val[10];
	double ts;
	unsigned char *hdr;
	int count = 0, frame = 0, interval = 100;
	char kp = 'a';
	cout << "Press any key to start receiving. Press 'q' to quit." << endl;
	g_comm->swapDataIs(false);
	_getch();
	// start recv
	while (!done) {
		//--------------------------------------------------------
		//  THIS IS THE CODE THAT ACCEPTS THE DATA PACKETS
		rc = g_comm->Receive();
		TRACE("Receive rc = %d\n", rc);
		if(rc == COMMRET_SUCCESS) {
			hdr = (unsigned char *)g_comm->readBuffer(6);
			numch = g_comm->readUShort();
			TRACE("RECV: %6.6s NumCh:%d\n", hdr, numch);
			ts = g_comm->readDouble();
			numch = min(numch, 10);
			for (int currNum = 0; currNum < numch; currNum++) {
				val[currNum] = g_comm->readShort();
			}
			TRACE("   ch[0-3]:%d %d %d %d\n", val[0], val[1], val[2], val[3]);
		}
		//--------------------------------------------------------
		if (_kbhit()) {
			kp = _getch();
			if (kp == 'q')
				done = true;
			else
				cout << "KeyPress " << kp << ". Press 'q' to quit." << endl;
		}
		count++;
		if (count == 10) {
			cout << "Tx+" << count << "[" << frame << "]" << endl;
			count = 0;
			frame++;
		}
		Sleep(interval);
	}
	return (rc==COMMRET_SUCCESS);
}


bool InitComm(){
	bool rb = true;
	char commch;
	char baudstr[20];

	if(g_comm != NULL)
	{
		delete g_comm;
		g_comm = NULL;
	}

	g_comm = new CCommSerial();
	g_comm->AllocateBuffers();

	char initStr[200];
	cout << "Enter in COM PORT Number 1, 2, ... : ";
	cin >> commch;
	cin.getline(&baudstr[0], 20);
	cout << endl << "Enter in Baud Rate (e.g. 57600) : ";
	cin.getline(&baudstr[0], 20);
	cout << endl;
	if (commch == 0) {
		commch = '1';
	}
	if (strlen(baudstr) == 0) {
		strcpy_s(baudstr, "57600");
	}
	sprintf_s(initStr, "COM%c: baud=%s parity=N data=8 stop=1", commch, baudstr); 
	if(g_comm->Init(initStr) == -1)
	{
		cout << "ERROR initializing COM Port with " << initStr << ". Try something else..." << endl;
		gbInit = false;
	}
	cout << initStr << endl << endl;
	if(g_comm->Open() == 0)
	{
		gbInit = true;
	}

	return rb;
}

bool WriteString(char *str){
	bool rb = true;

	g_comm->resetOutBuffer();
	g_comm->writeString(str);
	g_comm->Send();

	return rb;
}

void DisplayMenuLoop(){
	char inch = 'Z';

	while(inch != 'x'){
		cout << "     ** Menu (FW Version = " << gVersion << ") **" << endl;
		cout << "  i = initialize COM port " << endl;
		cout << "  s = start sending serial data" << endl;
		cout << "  r = start receiving serial data" << endl;
		cout << "  x = exit " << endl;
		cout << "Choose Menu Option: ";
		cin >> inch;
		cout << endl;

		switch(inch){
			case 'i':
				InitComm();
				break;
			case 's':
				StartTx();
				break;
			case 'r':
				StartRx();
				break;
			case 'x':
				cout << "thanks.  good-bye." << endl;
				break;
			default:
				cout << "unknown command" << endl;
				break;
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	DisplayMenuLoop();
	if(g_comm != NULL){
		g_comm->Close();
		delete g_comm;
	}
	return 0;
}

