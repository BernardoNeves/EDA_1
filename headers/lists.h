/**
 * @brief
 *
 * job Struct contains jobNumber (@@jobNumber)
 * contains a pointer operationHead
 * contains a pointer to the next job
 */
typedef struct job
{
    int jobNumber;
    struct operation *operationHeadPointer;
    struct job *next;
    struct job *prev;
} job;

/**
 * @brief
 *
 * operation Struct contains operationNumber (@@operationNumber), jobNumber (@@jobNumber)
 * contains a pointer machineHead
 * contains a pointer to the next and previous operation
 */
typedef struct operation
{
    int operationNumber;
    int jobNumber;
    struct machine *machineHeadPointer;
    struct operation *next;
    struct operation *prev;
} operation;

/**
 * @brief
 *
 * machine Struct contains machineNumber (@@machineNumber), machineTime (@@machineTime)
 * contains a pointer to the next and previous machine
 */
typedef struct machine
{
    int machineNumber;
    int machineTime;
    struct machine *next;
    struct machine *prev;
} machine;

int getInt();

job *read();
void write();

int timeMin();
int timeMax();
float timeAverage();

void printJobList();
void printOperationList();
void printMachineList();

void userCreateOperation();
void userRemoveOperation();
void userAlterOperation();

job *createNewJob();
operation *createNewOperation();
machine *createNewMachine();

job insertAfterJob();
operation insertAfterOperation();
machine insertAfterMachine();

job *insertAtJobHead();
operation *insertAtOperationHead();
machine *insertAtMachineHead();

job *insertAtJobEnd();
operation *insertAtOperationEnd();
machine *insertAtMachineEnd();

void orderJob();
void orderOperation();
job *findJob();
operation *findOperation();
machine *findMachine();

void *removeJob();
void *removeOperation();
void *removeMachine();