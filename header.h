extern void delay_ms(unsigned int ms);
extern void lcd_init(void);
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void delay_sec(unsigned int sec);
extern void lcd_string(char *p);
extern void uart0_tx(unsigned char data);
extern void uart0_init(unsigned int baud);
extern unsigned char uart0_rx(void);
void uart0_string(char *p);
void uart0_int( int num);
void uart0_float( float num);
void adc_init(void);
int adc_read(int chnum);

