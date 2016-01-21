
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // RST Ayağını Ayarla.  Bu iki ayak herhangi bir ayak olabilir. 
#define SS_PIN          10          // SS ayağını ayarla. Bu iki ayak herhangi bir ayak olabilir.

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Nesne oluştur. 

MFRC522::MIFARE_Key key;


void setup() {
    Serial.begin(9600); // Seri port aç
    while (!Serial);    // Atmega32u4 için.
    SPI.begin();        // SPI aç
    mfrc522.PCD_Init(); // RC522 tanımla.
    // Anahtarları hazırla.
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    Serial.println(F("RFID Kart okuma ve yazma programi "));
    Serial.print(F("Kullanilan anahtar. (A'dan B'ye):"));
    dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();
    
    Serial.println(F("Dikkat! Veri 1. sektore yazilacaktir."));
}

/**
 * Main loop.
 */
void loop() {
    // yeni kartlara bak
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // bu kartlardan birini seç
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    // biraz ayrinti goster
    Serial.print(F("Kart UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    // uyumluluk denetle
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("Bu ornek MIFARE Klasik kartlara calisir"));
        return;
    }

    // Bu ornekte şu sektör kullanılmıştır. 
    //
    byte sector         = 1;
    byte blockAddr      = 4;
    byte dataBlock[]    = {
        0x01, 0x02, 0x03, 0x04, //  1,  2,   3,  4,
        0x05, 0x06, 0x07, 0x08, //  5,  6,   7,  8,
        0x08, 0x09, 0xff, 0x0b, //  9, 10, 255, 12,
        0x0c, 0x0d, 0x0e, 0x0f  // 13, 14,  15, 16
    };
    byte trailerBlock   = 7;
    MFRC522::StatusCode status;
    byte buffer[18];
    byte size = sizeof(buffer);

    // A anahtarini kullanarak tanımla
    Serial.println(F("A anahtari kullanilarak tanimlaniyor...."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Tanimlama basarisiz.: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Sektoru Goster
    Serial.println(F("Verinin oldugu sektor:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();

    // Bloktaki veriyi oku
    Serial.print(F("Bloktan veri okunuyor. ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() basarisiz: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print(F("Bloktaki veri ")); Serial.print(blockAddr); Serial.println(F(":"));
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    //B anahtarı kullanarak tanımlama
    Serial.println(F("Anahtar B kullanilarak tekrar tanimlama..."));
    status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("PCD_Authenticate() basarisiz: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Write data to the block
    Serial.print(F("Writing data into block ")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    dump_byte_array(dataBlock, 16); Serial.println();
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.println();

    // Bloktaki veriyi oku. 
    Serial.print(F("Blok verisi okuma")); Serial.print(blockAddr);
    Serial.println(F(" ..."));
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() basarisiz: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print(F("Blokdaki veri ")); Serial.print(blockAddr); Serial.println(F(":"));
    dump_byte_array(buffer, 16); Serial.println();
        
    // Ne yaziliysa denetle.
    // 
    Serial.println(F("Sonuca bakiliyor..."));
    byte count = 0;
    for (byte i = 0; i < 16; i++) {
        // Compare buffer (= what we've read) with dataBlock (= what we've written)
        if (buffer[i] == dataBlock[i])
            count++;
    }
    Serial.print(F("Eslesen Bayt sayisi = ")); Serial.println(count);
    if (count == 16) {
        Serial.println(F("Basarili :-)"));
    } else {
        Serial.println(F("Basarisiz, eslesme yok :-("));
        Serial.println(F(" Belki yazma islemi iyi olmadi"));
    }
    Serial.println();
        
    // Dump the sector data
    Serial.println(F("Sektordaki mevcut veri:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}


void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
