typedef struct PrinterContext PrinterContext;

typedef enum {
    PRT_STATUS_OK,
    PRT_STATUS_ERROR
} PrinterStatus;

PrinterContext* initContext();

void closeContext(PrinterContext* context);

void sayHello(PrinterContext* context, const char* name);

void sayGoodbye(PrinterContext* context);
