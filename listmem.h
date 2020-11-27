/**
 * @author Jorge Teixeira Crespo (jorge.teixeira)
 * @author Miguel Juncal Paz (miguel.juncalp)
 *
 */


typedef struct memory_struct * mem_historic;

mem_historic create_memlist();
void remove_memlist(mem_historic);
void insert_in_memlist(mem_historic, void*, int ,char*,char*,char*);
void remove_from_memlist(mem_historic, int);
char* read_from_memlist(mem_historic, int);
int n_elements_in_memlist(mem_historic);


