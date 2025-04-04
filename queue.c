
#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) { 
    size_t val = remove_from_head(&q->data);
    return deserialize(val);
}

int tiles_equal(struct game_state current, struct game_state goal){
  for(int i = 0; i<4; i++){
    for(int j =0; j<4; j++){
      if(current.tiles[i][j] != goal.tiles[i][j]){
        return 0;
      }
    }
  }
  return 1;
}

int check_visited(struct queue *visited, struct game_state current){
    struct list_node *checker = visited->data.head;
    current.num_steps = 0;
    size_t ser_current = serialize(current);
    while(checker!=NULL){
      //struct game_state check = deserialize(checker->value);
      //if(tiles_equal(check, current)){
      if(checker->value == ser_current){
        return 0;
      }
      checker = checker->next;
    }
    return 1;
}


int number_of_moves(struct game_state start) {
    struct queue q = {.data.head = NULL};
    struct queue visited = {.data.head = NULL};
    struct game_state goal = {.tiles = {{1, 2, 3, 4}, 
                                         {5, 6, 7, 8},
                                         {9, 10, 11, 12}, 
                                         {13, 14, 15, 0}},
                                    .empty_row = 3, .empty_col = 3, .num_steps = 0}; // empty_row/col is empty tile's pos

    if(tiles_equal(start, goal)){ return 0; }
    enqueue(&q, start);
    int num_steps;
    while(q.data.head != NULL){ 
      struct game_state current = dequeue(&q); // takes the queue and makes it the current state
      num_steps = current.num_steps;
      current.num_steps = 0;
      enqueue(&visited, current);
      current.num_steps = num_steps;
      if(tiles_equal(current, goal)){ // if the current state equals the goal, then return the num steps it took to get there
        free_list(visited.data);
        free_list(q.data);
        return current.num_steps;
      }

      if(current.empty_row > 0){
        struct game_state down = current;
        move_down(&down);
        if(check_visited(&visited, down)){
            enqueue(&q, down);
            //enqueue(&visited, down);
        }
      }

      if(current.empty_col > 0){
        struct game_state right = current;
        move_right(&right);
        if(check_visited(&visited, right)){
            enqueue(&q, right);
            //enqueue(&visited, right);
        }
      }

      if(current.empty_row < 3){
        struct game_state up = current;
        move_up(&up);
        if(check_visited(&visited, up)){        
            enqueue(&q, up);
            //enqueue(&visited, up); // adds to visited
        }
      }

      
      if(current.empty_col < 3){
        struct game_state left = current;
        move_left(&left);
        if(check_visited(&visited, left)){
            enqueue(&q, left);
            //enqueue(&visited, left); // adds to visited
        }
      }
    }

    free_list(q.data);
    free_list(visited.data);
    return -1; }
