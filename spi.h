
void set_CS(int value);

void spi_master_init(void);

void spi_master_transmit(char cData);

void spi_slave_init(void);

char spi_slave_receive(void);

char mcp_read(char content);