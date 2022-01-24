#include "state.h"

State* init_state(const char* data, size_t size)
{
	State* state = (State*) malloc(sizeof(State));
	
	return state;
}

void dispose_state(State* state)
{
	free(state->blocks);
	free(state);
}
