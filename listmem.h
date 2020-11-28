/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */


typedef struct memory_struct * mem_list;
typedef struct struct_command command;


mem_list create_memlist();
void remove_memlist(mem_list);
void insert_in_memlist(mem_list, void*, int , char*, char*);
void remove_from_memlist(mem_list, int);
command* read_from_memlist(mem_list, int);
int n_elements_in_memlist(mem_list);


