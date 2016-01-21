#ifndef nRF24L01p_h
	#define nRF24L01p_h
	#if (ARDUINO >= 100)
		#include <Arduino.h>
	#else
		#include <WProgram.h>
	#endif
	#include <SPI.h>
	#include <regMapCmds.h>

class nRF24L01p{
	boolean _prim_rx;
	boolean _prim_tx;
	boolean _init;
	byte _status;
	byte _fifo;
	byte _csn,_ce;
	byte _rxIndex;
	byte _txIndex;
	byte _rxPayLoad[32];
	byte _txPayLoad[32];
	void csnHigh();
	void csnLow();
	void ceHigh();
	void ceLow();
	void cePulse();
	void testLow();
	void testHigh();
	void enableRX(byte);
	
	void iterRX(byte *, byte);
	void iterTX(byte *, byte);
	void iterARX(byte *, byte, byte);
	void iterATX(byte *, byte, byte);
	void iterAARX(byte *, byte,byte,byte);
	void iterAATX(byte *, byte,byte,byte);
	byte qtyChars(char *,byte);
	byte getStatus();
	byte getFIFO();
	void dynamicPayload(byte);
	void feature(byte);
	void powerUp();
	void powerDown();
	void writeReg(byte, byte);
	void writeReg(byte, char*, byte);
	byte readReg(byte);
	boolean address(byte, char*);
	void addrWidth(byte);
	void irqFunction(byte, boolean);
	void primPRX();
	void primPTX();
	byte payLoadWidth();
	void flushRX();
	void flushTX();
	
public:
	nRF24L01p(const byte, const byte);
	void init();
	void TXaddress(char*);
	void RXaddress(char*);
	void channel(byte);
	void dataRate(byte);
	
	boolean available();
	boolean read();
	
	void rxPL(byte &);
	void rxPL(char &);
	void rxPL(int &);
	void rxPL(unsigned int &);
	void rxPL(long &);
	void rxPL(unsigned long &);
	void rxPL(float &);
	void rxPL(String &);
	void rxPL(byte *, byte);
	void rxPL(char *&);
	void rxPL(char *, byte);
	void rxPL(int *, byte);
	void rxPL(unsigned int *, byte);
	void rxPL(long *, byte);
	void rxPL(unsigned long *, byte);
	void rxPL(float *, byte);
	void rxPL(byte *, byte, byte);
	void rxPL(char *, byte, byte);
	void rxPL(int *, byte, byte);
	void rxPL(unsigned int *, byte, byte);
	void rxPL(long *, byte, byte);
	void rxPL(unsigned long *, byte, byte);
	void rxPL(float *, byte, byte);
	
	void txPL(byte &);
	void txPL(char &);
	void txPL(int &);
	void txPL(unsigned int &);
	void txPL(long &);
	void txPL(unsigned long &);
	void txPL(float &);
	int txPL(String);
	void txPL(byte *, byte);
	void txPL(char *);
	void txPL(char *, byte);
	void txPL(int *, byte);
	void txPL(unsigned int *, byte);
	void txPL(long *, byte);
	void txPL(unsigned long *, byte);
	void txPL(float *, byte);
	void txPL(byte *, byte, byte);
	void txPL(char *, byte, byte);
	void txPL(int *, byte, byte);
	void txPL(unsigned int *, byte, byte);
	void txPL(long *, byte, byte);
	void txPL(unsigned long *, byte, byte);
	void txPL(float *, byte, byte);
	
	boolean send(boolean =SLOW);
};
#endif