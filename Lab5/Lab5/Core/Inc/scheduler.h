#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#include <stdio.h>
#include <stdlib.h>
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

#define RETURN_NORMAL   1
#define RETURN_ERROR    2

//// Mã lỗi
//#define ERROR_SCH_CANNOT_DELETE_TASK (3)
//#define ERROR_SCH_TOO_MANY_TASKS     (4)
//// ... Các mã lỗi khác ...

typedef unsigned char tByte;
typedef unsigned int tWord;

void toggle();

typedef struct {
	void ( * pTask)(void) ;
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

typedef struct Node {
	sTask* data;
    struct Node* next;
} Node_t;

typedef struct List_sTask {
    Node_t* head;
} List_sTask;


void SCH_Init(void);
unsigned char SCH_Add_Task(void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD);
void addAt(void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD, int index);
unsigned char SCH_Delete_Task(const tByte TASK_INDEX);
void SCH_Dispatch_Tasks(void);
void SCH_Update(void);

void SCH_Clear_Some_Tasks();

void SCH_Go_To_Sleep();
void rearrange_ID();
void SCH_Report_Status(void);

int SCH_Get_TaskID(void (* pFunction)() );




#endif /* SOFTWARE_TIMER_H */
