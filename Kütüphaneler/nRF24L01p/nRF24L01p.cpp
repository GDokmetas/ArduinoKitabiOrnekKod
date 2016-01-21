#if (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif
#include <SPI.h>
#include <regMapCmds.h>
#include <nRF24L01p.h>

nRF24L01p::nRF24L01p(const byte csn,const byte ce):
_csn(csn),_ce(ce){
	pinMode(_csn,OUTPUT);
	pinMode(_ce,OUTPUT);
	csnHigh();
	ceLow();
	_txIndex=0;
	_rxIndex=0;
	_prim_rx=false;
	_prim_tx=false;
	_init=false;
}

void nRF24L01p::init(){
	flushRX();
	flushTX();
	dynamicPayload(P0|P1);
	feature(DPL|DYN_ACK);
	writeReg(SETUP_RETR,0x2F);
	writeReg(STATUS,0x70);
	powerUp();
	if(_prim_rx && _prim_tx){
		enableRX(P1|P0);
		primPRX();
		ceHigh();
	}else if(_prim_rx && !_prim_tx){
		enableRX(P1);
		primPRX();
		ceHigh();
	}else if(!_prim_rx && _prim_tx){
		enableRX(P0);
		primPTX();
	}
	_init=true;
}

void nRF24L01p::csnHigh(){
	digitalWrite(_csn,HIGH);
}
void nRF24L01p::csnLow(){
	digitalWrite(_csn,LOW);
}
void nRF24L01p::ceHigh(){
	digitalWrite(_ce,HIGH);
}
void nRF24L01p::ceLow(){
	digitalWrite(_ce,LOW);
}
void nRF24L01p::cePulse(){
	ceHigh();
	delayMicroseconds(10);
	ceLow();
}
void nRF24L01p::testLow(){
	if(_init==true && _prim_rx==true)ceLow();
}
void nRF24L01p::testHigh(){
	if(_init==true && _prim_rx==true)ceHigh();
}
byte nRF24L01p::readReg(byte _reg){
	csnLow();
	_status=SPI.transfer(_reg & REGISTERS);
	byte _byteRead=SPI.transfer(0x00);
	csnHigh();
	return _byteRead;
}
void nRF24L01p::writeReg(byte _reg, byte _data){
	csnLow();
	_status=SPI.transfer(W_REGISTER | (_reg & REGISTERS));
	SPI.transfer(_data);
	csnHigh();
}
void nRF24L01p::writeReg(byte _reg, char* _data, byte _numBytes){
	csnLow();
	_status=SPI.transfer(W_REGISTER | (_reg & REGISTERS));
	for(byte it=0; it<_numBytes; it++){
		SPI.transfer(_data[it]);
	}
	csnHigh();
}

byte nRF24L01p::getStatus(){
	return readReg(STATUS);
}
byte nRF24L01p::getFIFO(){
	_fifo=readReg(FIFO_STATUS);
	return _fifo;
}

void nRF24L01p::addrWidth(byte _addrw){
	_addrw-=2;
	if(_addrw>=1 && _addrw<=3){
		writeReg(SETUP_AW,_addrw);
	}
}
boolean nRF24L01p::address(byte _reg,char* _addr){
	byte _aw=0;
	for(char *it=_addr;*it;it++){
		_aw++;
	}
	if(_aw>=3 && _aw<=5){
		addrWidth(_aw);
		writeReg(_reg,_addr,_aw);
		return true;
	}else{
		return false;
	}
}
void nRF24L01p::TXaddress(char* _address){
	address(RX_ADDR_P0,_address);
	address(TX_ADDR, _address);
	_prim_tx=true;
}
void nRF24L01p::RXaddress(char* _address){
	testLow();
	address(RX_ADDR_P1,_address);
	testHigh();
	_prim_rx=true;
}
void nRF24L01p::enableRX(byte _pipes){
	writeReg(EN_RXADDR, _pipes);
}

void nRF24L01p::channel(byte _RFCh){
	testLow();
	if(_RFCh>127){
		_RFCh=127;
	}
	writeReg(RF_CH, _RFCh);
	testHigh();
}

void nRF24L01p::dataRate(byte _RFdr){
	testLow();
	byte buf_RF=readReg(RF_SETUP);
	switch (_RFdr){
		case 1		: _RFdr=0x00; break;
		case 2		: _RFdr=0x08; break;
		case 250	: _RFdr=0x20; break;
		default		: _RFdr=buf_RF; break;
	}
	writeReg(RF_SETUP, _RFdr | (buf_RF & 0x07));
	testHigh();
}

void nRF24L01p::dynamicPayload(byte _dyn){
	_dyn &= 0x3F;
	writeReg(DYNPD, _dyn);
}

void nRF24L01p::feature(byte _fea1){
	_fea1 &= 0x07;
	writeReg(FEATURE, _fea1);
}

void nRF24L01p::powerUp(){
	byte buf=readReg(CONFIG);
	writeReg(CONFIG, buf | 0x02);
	delayMicroseconds(4500);
}
void nRF24L01p::powerDown(){
	byte buf=readReg(CONFIG);
	writeReg(CONFIG, buf & 0xFD);
}

void nRF24L01p::primPRX(){
	byte buf=readReg(CONFIG);
	writeReg(CONFIG,buf | 0x01);
}
void nRF24L01p::primPTX(){
	byte buf=readReg(CONFIG);
	writeReg(CONFIG,buf & 0xFE);
}

void nRF24L01p::irqFunction(byte _mask,boolean _onoff){
	byte buf=readReg(CONFIG);
	if(_onoff==true){
		buf|=0x70;
		buf&=(~_mask | 0x0F);
	}else if(_onoff==false){
		buf|=(_mask & 0x70);
	}
	writeReg(CONFIG,buf);
}

void nRF24L01p::flushRX(){
	csnLow();
	SPI.transfer(FLUSH_RX);
	csnHigh();
}
void nRF24L01p::flushTX(){
	csnLow();
	SPI.transfer(FLUSH_TX);
	csnHigh();
}
byte nRF24L01p::payLoadWidth(){
	csnLow();
	SPI.transfer(R_RX_PL_WID);
	byte _width=SPI.transfer(0x00);
	csnHigh();
	return _width;
}
boolean nRF24L01p::available(){
	if(_prim_rx==false){
		_rxIndex=32;
		return false;
	}
	getFIFO();
	if(bitRead(_fifo,0)==0){
		if(payLoadWidth()>32){
			flushRX();
			getFIFO();
			if(bitRead(_fifo,0)==0){
				writeReg(STATUS,0x40);
				return true;
			}else{
				return false;
			}
		}else{
			return true;
		}
	}else{
		return false;
	}	
}

boolean nRF24L01p::read(){
	if(_prim_rx==false){
		_rxIndex=32;
		return false;
	}
	_rxIndex=0;
	for(int it=0;it<32;it++){
		_rxPayLoad[it]=0;
	}
	byte _plw=payLoadWidth();
	csnLow();
	SPI.transfer(R_RX_PAYLOAD);
	for(int it=0;it<_plw;it++){
		_rxPayLoad[it]=SPI.transfer(0x00);
	}
	csnHigh();
	writeReg(STATUS,1<<6);
	return true;
}

boolean nRF24L01p::send(boolean _modeSend){
	if(_prim_tx==false){
		_txIndex=32;
		return false;
	}
	if(_prim_rx==true){
		ceLow();
		primPTX();
	}
	csnLow();
	if(_modeSend==false || (_prim_rx && _prim_tx)){
		SPI.transfer(W_TX_PAYLOAD);
	}else{
		SPI.transfer(W_TX_PAYLOAD_NOACK);
	}
	for(int i=0;i<_txIndex;i++){
		SPI.transfer(_txPayLoad[i]);
	}
	csnHigh();
	cePulse();
	unsigned long tmC1=micros();
	while(1){
		if(bitRead(getStatus(),5)){
			//writeReg(STATUS,_status|(1<<6));
			writeReg(STATUS,_status|(1<<5));
			writeReg(STATUS,_status|(1<<4));
			break;
		}
		if(bitRead(getStatus(),4)){
			writeReg(STATUS,_status|(1<<4));
			cePulse();
		}
		unsigned long tmC2=micros();
		if(tmC2-tmC1>2500000L){
			//Serial.println("send(SLOW) returned false");
			//Serial.println("connection lost ");
			return false;
		}
	}
	_txIndex=0;
	if(_prim_rx==true){
		primPRX();
		ceHigh();
	}
	return true;
}

void nRF24L01p::rxPL(String &_sen){
	byte _pos=_rxIndex;
	for(int it=0;(it<32) && (_rxIndex<32);it++){		
		if(_rxPayLoad[it+_pos]=='\0'){
			_rxIndex++;
			break;
		}else{
			_sen+=char(_rxPayLoad[it+_pos]);
			_rxIndex++;
		}
	}
}

int nRF24L01p::txPL(String _payLoad){
	int _sizeS=_payLoad.length();
	int _qty=0;
	int i;
	byte _pos=_txIndex;
	for(i=0;(i<_sizeS) && (_txIndex<32);i++){
		_txPayLoad[_pos + i]=_payLoad[i];
		_txIndex++;
		_qty++;
	}
	if(_txIndex<32 && (_sizeS==i)){
		_txPayLoad[_pos + _sizeS]='\0';
		_txIndex++;
	}
	return _qty;
}
///////////////////////////////////////////////
void nRF24L01p::rxPL(byte &_dataB){
	iterRX(&_dataB,1);
}
void nRF24L01p::rxPL(char &_dataC){
	iterRX((byte *)&_dataC,1);
}
void nRF24L01p::rxPL(int &_datai){
		iterRX((byte *)&_datai,2);
}
void nRF24L01p::rxPL(unsigned int &_dataui){
		iterRX((byte *)&_dataui,2);
}
void nRF24L01p::rxPL(long &_datal){
		iterRX((byte *)&_datal,4);
}
void nRF24L01p::rxPL(unsigned long &_dataul){
		iterRX((byte *)&_dataul,4);
}
void nRF24L01p::rxPL(float &_dataf){
		iterRX((byte *)&_dataf,4);
}
void nRF24L01p::txPL(byte &_payLoad){
	iterTX(&_payLoad,1);
}
void nRF24L01p::txPL(char &_payLoad){
	iterTX((byte *)&_payLoad,1);
}
void nRF24L01p::txPL(int &_payLoad){
		iterTX((byte *)&_payLoad,2);
}
void nRF24L01p::txPL(unsigned int &_payLoad){
		iterTX((byte *)&_payLoad,2);
}
void nRF24L01p::txPL(long &_payLoad){
		iterTX((byte *)&_payLoad,4);
}
void nRF24L01p::txPL(unsigned long &_payLoad){
		iterTX((byte *)&_payLoad,4);
}
void nRF24L01p::txPL(float &_payLoad){
		iterTX((byte *)&_payLoad,4);
}
void nRF24L01p::iterRX(byte *_adr,byte _num){
	if((32-_txIndex)/_num>0){
		byte _pos=_rxIndex;
		for(int pt=0;pt<_num;pt++,_adr++){
			*_adr=_rxPayLoad[pt + _pos];
			_rxIndex++;
		}
	}
}
void nRF24L01p::iterTX(byte *_adr,byte _num){
	if((32-_txIndex)/_num>0){
		byte _pos=_txIndex;
		for(int pt=0;pt<_num;pt++,_adr++){
			_txPayLoad[pt + _pos]=*_adr;
			_txIndex++;
		}
	}
}
////////////////////////////////////////////////
void nRF24L01p::rxPL(byte *y,byte _s){
	iterARX((byte*)y,_s,1);
}
void nRF24L01p::rxPL(char *y,byte _s){
	iterARX((byte*)y,_s,1);
}
void nRF24L01p::rxPL(int *y,byte _s){
	iterARX((byte*)y,_s,2);
}
void nRF24L01p::rxPL(unsigned int *y,byte _s){
	iterARX((byte*)y,_s,2);
}
void nRF24L01p::rxPL(long *y,byte _s){
	iterARX((byte*)y,_s,4);
}
void nRF24L01p::rxPL(unsigned long *y,byte _s){
	iterARX((byte*)y,_s,4);
}
void nRF24L01p::rxPL(float *y,byte _s){
	iterARX((byte*)y,_s,4);
}
void nRF24L01p::txPL(byte *x,byte _s){
	iterATX((byte*)x,_s,1);
}
void nRF24L01p::txPL(char *x,byte _s){
	iterATX((byte*)x,_s,1);
}
void nRF24L01p::txPL(int *x,byte _s){
	iterATX((byte*)x,_s,2);
}
void nRF24L01p::txPL(unsigned int *x,byte _s){
	iterATX((byte*)x,_s,2);
}
void nRF24L01p::txPL(long *x,byte _s){
	iterATX((byte*)x,_s,4);
}
void nRF24L01p::txPL(unsigned long *x,byte _s){
	iterATX((byte*)x,_s,4);
}
void nRF24L01p::txPL(float *x,byte _s){
	iterATX((byte*)x,_s,4);
}
void nRF24L01p::iterATX(byte *_ptA,byte _s2,byte _factor){
	if((32-_txIndex)/(_s2*_factor)>0 && _s2!=0){
		byte _pos=_txIndex;
		byte *ptArray=_ptA;
		for(int it=0;it<(_s2*_factor);it++, ptArray++){
			_txPayLoad[it+_pos]=*ptArray;
			_txIndex++;
		}
	}
}
void nRF24L01p::iterARX(byte *_ptA,byte _s2,byte _factor){
	if((32-_rxIndex)/(_s2*_factor)>0 && _s2!=0){
		byte _pos=_rxIndex;
		byte *ptArray=_ptA;
		for(int it=0;it<(_s2*_factor);it++, ptArray++){
			*ptArray=_rxPayLoad[it+_pos];
			_rxIndex++;
		}
	}
}
//////////////////////////////////////////////////////////////
void nRF24L01p::rxPL(byte *y,byte _s,byte _e){
	iterAARX((byte *)(y+_s),_s,_e,1);
}
void nRF24L01p::rxPL(char *y,byte _s,byte _e){
	iterAARX((byte *)(y+_s),_s,_e,1);
}
void nRF24L01p::rxPL(int *y,byte _s,byte _e){
	iterAARX((byte *)(y+_s),_s,_e,2);
}
void nRF24L01p::rxPL(unsigned int *y,byte _s,byte _e){
	iterAARX((byte *)(y+_s),_s,_e,2);
}
void nRF24L01p::rxPL(long *y,byte _s,byte _e){
	iterAARX((byte *)(y+_s),_s,_e,4);
}
void nRF24L01p::rxPL(unsigned long *y,byte _s,byte _e){
	iterAARX((byte *)(y+_s),_s,_e,4);
}
void nRF24L01p::rxPL(float *y,byte _s,byte _e){
	iterAARX((byte *)(y+_s),_s,_e,4);
}
void nRF24L01p::txPL(byte *x,byte _s,byte _e){
	iterAATX((byte *)(x+_s),_s,_e,1);
}
void nRF24L01p::txPL(char *x,byte _s,byte _e){
	iterAATX((byte *)(x+_s),_s,_e,1);
}
void nRF24L01p::txPL(int *x,byte _s,byte _e){
	iterAATX((byte *)(x+_s),_s,_e,2);
}
void nRF24L01p::txPL(unsigned int *x,byte _s,byte _e){
	iterAATX((byte *)(x+_s),_s,_e,2);
}
void nRF24L01p::txPL(long *x,byte _s,byte _e){
	iterAATX((byte *)(x+_s),_s,_e,4);
}
void nRF24L01p::txPL(unsigned long *x,byte _s,byte _e){
	iterAATX((byte *)(x+_s),_s,_e,4);
}
void nRF24L01p::txPL(float *x,byte _s,byte _e){
	iterAATX((byte *)(x+_s),_s,_e,4);
}
void nRF24L01p::iterAATX(byte *_ptAA,byte _s3,byte _e2,byte _factor2){
	if(_s3 != _e2){
		iterATX(_ptAA,_e2-_s3+1,_factor2);
	}
}
void nRF24L01p::iterAARX(byte *_ptAA,byte _s3,byte _e2,byte _factor2){
	if(_s3 != _e2){
		iterARX(_ptAA,_e2-_s3+1,_factor2);
	}
}
////************Especial Char Array functions
void nRF24L01p::txPL(char *_payLoad){
	byte count=qtyChars(_payLoad,32);
	if(1<count && count<=32){
		iterATX((byte *)_payLoad,count,1);
	}
}
void nRF24L01p::rxPL(char *&_refPt){
	byte count=qtyChars((char *)_rxPayLoad,32);
	if(1<count && count<=32){
		free((void *)_refPt);
		_refPt=(char *)realloc(_refPt,count);
		if(_refPt != NULL){
			iterARX((byte *)_refPt,count,1);
		}
	}
}
byte nRF24L01p::qtyChars(char *ptC,byte _hval){
	byte _count=0;
	do{
		_count++;
		if(_count>_hval){
			return _count;
		}
	}while(*ptC++);
	return _count;
}