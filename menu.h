struct node{
    
    struct node *select;
    struct node *prev;
    struct node *mainMenu;
}node_t;


void menu_build(node_t * mainMenu);
