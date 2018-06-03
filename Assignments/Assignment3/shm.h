enum StatusEnum{INVALID, VALID, CONSUMED};

typedef struct{
	enum StatusEnum status;
	int data;
} ShmData;