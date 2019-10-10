typedef struct message{
    int id;
    int length;
    int data[8];
}message_t;



void can_init(void);

void can_send_message(message_t* message);

void can_receive_message(message_t* message);

void can_set_mode(int mode);

