typedef struct machine
{
    int MachineNumber;
    int MachineTime;
    struct machine *next;
    struct machine *prev;
} machine;

typedef struct operation
{
    int OperationNumber;
    int JobNumber;
    struct machine *MachineHeadPointer;
    struct operation *next;
} operation;

typedef struct job
{
    int JobNumber;
    struct operation *OperationHeadPointer;
    struct job *next;
} job;

job *read(FILE *JobsFile, job *jobhead);
void write(FILE *JobsFile, job *jobhead);

void PrintJobList(job *jobhead);
void PrintOperationList(operation *head, job *jobhead, int l);
void PrintMachineList(machine *head);

job *create_new_job(int JobNumber, operation **head);
operation *create_new_operation(int OperationNumber, int JobNumber, machine **head);
machine *create_new_machine(int MachineNumber);

job *insert_at_jobhead(job **jobhead, job *job_to_insert);
operation *insert_at_operationhead(operation **operationhead, operation *operation_to_insert);
machine *insert_at_machinehead(machine **machinehead, machine *machine_to_insert);

job *insert_job_at_end(job **jobhead, job *job_to_insert);
operation *insert_operation_at_end(operation **operationhead, operation *operation_to_insert);
machine *insert_machine_at_end(machine **machinehead, machine *machine_to_insert);

job *find_job(job *head, int JobNumber);
operation *find_operation(operation *head, int OperationNumber, int JobNumber);
machine *find_machine(machine *head, int MachineNumber);

void insert_after_job(job *job_to_insert_after, job *newjob);
void insert_after_operation(operation *operation_to_insert_after, operation *newoperation);
void insert_after_machine(machine *machine_to_insert_after, machine *newmachine);

void *remove_operation(operation **head, int OperationNumber);