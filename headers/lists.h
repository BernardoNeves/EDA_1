typedef struct machine
{
    int machineNumber;
    int machineTime;
    struct machine *next;
    struct machine *prev;
} machine;

typedef struct operation
{
    int operationNumber;
    int jobNumber;
    struct machine *machineHeadPointer;
    struct operation *next;
    struct operation *prev;
} operation;

typedef struct job
{
    int jobNumber;
    struct operation *operationHeadPointer;
    struct job *next;
} job;

int GetInt();

job *read();
void write();

void PrintJobList();
void PrintOperationList();
void PrintMachineList();

void UserCreateOperation();
void UserRemoveOperation();
void UserAlterOperation();

job *create_new_job();
operation *create_new_operation();
machine *create_new_machine();

job *insert_at_jobhead();
operation *insert_at_operationhead();
machine *insert_at_machinehead();

job *insert_job_at_end();
operation *insert_operation_at_end();
machine *insert_machine_at_end();

job *select_job();
operation *select_operation();
machine *select_machine();
operation *find_operation();

operation *alter_operation();

void insert_after_job();
void insert_after_operation();
void insert_after_machine();

void *remove_machine();
void *remove_operation();
void *remove_job();