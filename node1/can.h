typedef struct message{
    uint8_t id;
    uint8_t length;
    uint8_t data[8];
}message_t;



void can_init(void);

void can_send_message(message_t* message);

message_t can_receive_message();

void can_set_mode(int mode);

int can_should_send(message_t message, uint8_t position_before[8]);

