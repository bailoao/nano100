#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int

#define LCD_DAT		PA3
#define LCD_CLK 	PA4
#define LCD_RS	 	PA5
#define LCD_RST 	PA6
#define LCD_DE 		PA7 //data enable //VREF
#define LCD_BK		PC7

void LCD_Delay(u32 t);
void LCD_Init(void);
void LCD_Command(u8 c);
void LCD_Data(u8 c);
void LCD_Fill(u8 c);
void LCD_Char(char c);
void LCD_String(char *st, u8 len);
void LCD_setPos(u8 x, u8 y);
