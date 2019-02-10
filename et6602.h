#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int

#define ET6602_MISO		PA1
#define ET6602_MOSI		PA1
#define ET6602_SCK		PA1
#define ET6602_TXON		PA1
#define ET6602_RXON		PA1
#define ET6602_WK_OUT	PA1

void ET6602_Delay(u32 t);
void ET6602_Init(void);

