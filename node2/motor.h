
void motor_init(void);

void motor_enable(void);

void motor_disable(void);

void motor_set_speed(int value);

int motor_pi_regulator(int position, int speed);

void motor_toggle(void);