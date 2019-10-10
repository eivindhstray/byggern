typedef struct message{
    uint8_t id;
    uint8_t length;
    uint8_t data[8];
}message_t;



void can_init(void);

void can_send_message(message_t* message);

void can_receive_message(message_t* message);

void can_set_mode(int mode);

