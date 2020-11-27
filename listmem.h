/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */


typedef struct memory_struct * mem_historic;
typedef struct struct_command command;


mem_historic create_memlist();
void remove_memlist(mem_historic);
void insert_in_memlist(mem_historic, void*, int ,char*,char*);
void remove_from_memlist(mem_historic, int);
command* read_from_memlist(mem_historic, int);
int n_elements_in_memlist(mem_historic);


