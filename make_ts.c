#include <err.h>
#include <stdlib.h>
#include "tskit.h"

#define check_tsk_error(val)                                                            \
    if (val < 0)                                                                        \
        {                                                                               \
            errx(EXIT_FAILURE, "line %d: %s", __LINE__, tsk_strerror(val));             \
        }

int
main(int argc, char **argv)
{
    tsk_table_collection_t tables;
    tsk_treeseq_t ts;
    int code;

    code = tsk_table_collection_init(&tables, 0);
    check_tsk_error(code);
    tables.sequence_length = 100.0;
    tsk_node_table_add_row(&tables.nodes, TSK_NODE_IS_SAMPLE, 0.0, -1, -1, NULL, 0);
    tsk_node_table_add_row(&tables.nodes, TSK_NODE_IS_SAMPLE, 0.0, -1, -1, NULL, 0);
    tsk_node_table_add_row(&tables.nodes, 0, 1.0, -1, -1, NULL, 0);

    tsk_edge_table_add_row(&tables.edges, 0., 100.0, 2, 0, NULL, 0);
    tsk_edge_table_add_row(&tables.edges, 0., 100.0, 2, 1, NULL, 0);

    // No anc state, no metadata
    code = tsk_site_table_add_row(&tables.sites, 50.0, NULL, 0, NULL, 0);
    check_tsk_error(code);

    // no derived state, no metadata
    code = tsk_mutation_table_add_row(&tables.mutations, 0, 1, -1, 0.01, NULL, 0, NULL,
                                      0);
    check_tsk_error(code);

    code = tsk_table_collection_sort(&tables, NULL, 0);
    check_tsk_error(code);
    code = tsk_table_collection_check_integrity(&tables, 0);
    check_tsk_error(code);
    code = tsk_table_collection_build_index(&tables, 0);
    check_tsk_error(code);
    code = tsk_treeseq_init(&ts, &tables, 0);
    check_tsk_error(code);
    tsk_treeseq_dump(&ts, "no_states.trees", 0);
}
