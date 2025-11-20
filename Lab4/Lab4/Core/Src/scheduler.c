#include <scheduler.h>
#include "main.h"
#include "fsm_manual.h"
#include "fsm_automatic.h"
#include "fsm_config.h"
#include "input_processing.h"
#include "input_reading.h"

#define TIMER_INTERRUPT_DURATION_MS 10
#define SCH_MAX_TASKS 40
static List_sTask* SCH_tasks_G = NULL;


int num_task = 0;

void SCH_Init(void) {
	SCH_tasks_G = (List_sTask*) malloc(sizeof(List_sTask));
    SCH_tasks_G->head = NULL;
}

unsigned char SCH_Add_Task(void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD){
	if(num_task == SCH_MAX_TASKS) return RETURN_ERROR;
	else ++num_task;

	unsigned int NEW_DELAY = DELAY;
    unsigned char idx = 0;
    Node_t* curr = SCH_tasks_G->head;
    int sum = 0;
    int pre_sum = 0;

    while (curr != NULL) {
        sum += curr->data->Delay;
        if (sum > DELAY) break;

        ++idx;
        curr = curr->next;
    }

    if(curr){
    	pre_sum = sum - curr->data->Delay;
		NEW_DELAY = DELAY - pre_sum;
		curr->data->Delay -= NEW_DELAY;
    }else{
    	NEW_DELAY = DELAY - sum;
    }

    addAt(pFunction, NEW_DELAY, PERIOD, idx);
    return idx;
}

void addAt(void (* pFunction) () , unsigned int DELAY, unsigned int PERIOD, int index) {
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if (newNode == NULL) return;

    newNode->data = (sTask*)malloc(sizeof(sTask));
    if (newNode->data == NULL){
    	free(newNode);
    	return;
    }
    
    newNode->data->pTask = pFunction;
    newNode->data->Delay = DELAY;
    newNode->data->Period = PERIOD;
    newNode->data->RunMe = 0;
    newNode->data->TaskID = index;

    newNode->next = NULL;
    
    if (index == 0) {
        newNode->next = SCH_tasks_G->head;
        SCH_tasks_G->head = newNode;
    } else {
        Node_t* prev = SCH_tasks_G->head;
        for (int i = 0; i < index - 1 && prev != NULL; i++) {
            prev = prev->next;
        }
        if (prev != NULL) {
            newNode->next = prev->next;
            prev->next = newNode;
        } else {
            free(newNode);
        }
    }
    rearrange_ID();
}

unsigned char SCH_Delete_Task(const tByte TASK_INDEX){

    Node_t *curr = SCH_tasks_G->head;
    Node_t *delete_node = NULL;

    if (SCH_tasks_G == NULL || SCH_tasks_G->head == NULL)
        return RETURN_ERROR;

    if (TASK_INDEX == 0) {
        delete_node = SCH_tasks_G->head;
        SCH_tasks_G->head = delete_node->next;

        if (delete_node->data) {
            free(delete_node->data);
            delete_node->data = NULL;
        }

        free(delete_node);
        rearrange_ID();
    	--num_task;
        return RETURN_NORMAL;
    }

    //Viết cho đủ thôi chứ đoạn dưới đây hong dùng đâu
    for (int i = 0; curr != NULL && i < TASK_INDEX - 1; i++)
        curr = curr->next;


    if (curr == NULL || curr->next == NULL)
        return RETURN_ERROR;

    delete_node = curr->next;

    if (delete_node->data == NULL)
        return RETURN_ERROR;

    free(delete_node->data);
    delete_node->data = NULL;

    curr->next = delete_node->next;
    free(delete_node);

    rearrange_ID();
    return RETURN_NORMAL;
}

void SCH_Dispatch_Tasks(void){
    if(SCH_tasks_G->head != NULL && SCH_tasks_G->head->data->RunMe > 0){
        SCH_tasks_G->head->data->RunMe -= 1;

        while(SCH_tasks_G->head != NULL && SCH_tasks_G->head->data->Delay == 0){
            Node_t* head_node = SCH_tasks_G->head;
            (*head_node->data->pTask) ();
            if(head_node->data->Period){
                void (*temp_pTask)() = head_node->data->pTask;
                unsigned int temp_Period = head_node->data->Period;

                SCH_Delete_Task(0);

                SCH_Add_Task(temp_pTask, temp_Period, temp_Period);
            } else{
                SCH_Delete_Task(0);
            }

        }
    }
}

void SCH_Update(void) {
	if (SCH_tasks_G->head == NULL || SCH_tasks_G->head->data == NULL)
	        return;
	if(SCH_tasks_G->head->data->Delay <= 0)
		SCH_tasks_G->head->data->RunMe += 1;
	else
		SCH_tasks_G->head->data->Delay -= TIMER_INTERRUPT_DURATION_MS;
}

void rearrange_ID(){
	int idx = 0;
	Node_t* curr = SCH_tasks_G->head;
	while(curr){
		curr->data->TaskID = idx++;

		curr = curr->next;
	}
}



