
struct OLED{
    int line;
}OLED;

void oled_write_c(char command);

void oled_write_char(char letter);

void oled_init(void);

void oled_reset(void);

void oled_select_line(int row);

void print_string(char* content);

int oled_scroll(void);

void oled_select_indicator(int row);

void oled_remove_marker(void);