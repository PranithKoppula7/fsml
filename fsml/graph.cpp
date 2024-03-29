
#include "graph.h"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

void create_graph(tensor t, GVC_t* gvc, Agraph_t* root);

graph::graph() {}

void graph::run(tensor t) {

    GVC_t *gvc = gvContext();
    Agraph_t *g = agopen((char*)"g", Agundirected, 0);

    create_graph(t, gvc, g);

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "graph.png");

    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}

void create_graph(tensor t, GVC_t* gvc, Agraph_t* root) {
    Agnode_t *curr = agnode(root, t.repr().data(), 1);
    for (tensor* p: t.parents_) {
        Agnode_t *m = agnode(root, p->repr().data(), 1);
        Agedge_t *e = agedge(root, curr, m, 0, 1);
    }
}