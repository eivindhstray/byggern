
void mcp_init(void);

int mcp_read(int address);

void mcp_reset(void);

void mcp_write(int address, int data);

int mcp_read_status(void);

void mcp_request_to_send(int buffer_number);

void mcp_bit_modify(int address, int mask, int data);

int mcp_ready_to_send(void);