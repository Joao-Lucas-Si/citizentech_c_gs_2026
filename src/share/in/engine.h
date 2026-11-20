typedef void (*Handler)(char* message);

typedef struct struc_listener {
    char* preffix;
    Handler handler;
} Listener;

void registerInput(char *preffix, Handler handler);