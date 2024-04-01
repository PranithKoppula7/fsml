
#include "graph.h"
#include "operation.h"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include <string>
#include <map>
#include <vector>

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

void dfs(tensor* t, 
         std::map<tensor*, Agnode_t*>& graph_map, 
         GVC_t* gvc,
         Agraph_t* r) {

    if (t == NULL) return;
    if (graph_map.find(t) == graph_map.end()) {
        Agnode_t* curr = agnode(r, t->repr().data(), 1);
        graph_map[t] = curr;
    }

    if(t->parents_.size() == 0) return;

    std::string op_name = t->ctx_->op_ + t->repr();
    // Agnode_t* op = agnode(r, t->ctx_->op_.data(), 1);
    Agnode_t* op = agnode(r, op_name.data(), 1);
    agedge(r, graph_map[t], op, 0, 1);
    for (tensor* p: t->parents_) {
        dfs(p, graph_map, gvc, r);
        agedge(r, op, graph_map[p], 0, 1);
        // agedge(r, graph_map[t], graph_map[p], 0, 1);
    }
}

void create_graph(tensor t, GVC_t* gvc, Agraph_t* root) {
    std::map<tensor*, Agnode_t*> graph_map;
    dfs(&t, graph_map, gvc, root);
}