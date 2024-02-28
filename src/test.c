int main(void){
	
	struct node* queue_array[5];

	void reset_queues(struct node** queue_array){	
		struct node* current_queue = NULL; 
		struct node* process = NULL;
	
		// Look for all processes original niceness and place them back in their original queue 
		for (int i = 0; i < 5; i++){
			current_queue = queue_array[i];
			while (current_queue != NULL){
				if (current_queue->niceness != current_queue->original_niceness){
					process = pop(current_queue);
					queue_array[5 - original_niceness] = push(queue_array[5 - original_niceness], process->pid, process->status, 
						process->original_niceness, process->cputime, process->proctime, process->original_niceness);
					free(process);
					process = NULL; // watchpoint here
				}
			}
		}
	}
}
