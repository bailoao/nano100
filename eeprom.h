#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int

//nano100  smartcard0½Ó¿Ú
#define EEPROM_RST		PA11
#define EEPROM_VCC		PA10
#define EEPROM_DAT		PA9
#define EEPROM_SCL		PA8

void EEPROM_Delay(u32 t);
void EEPROM_Init(void);
void EEPROM_Command(u8 c);
void EEPROM_Data(u8 c);
