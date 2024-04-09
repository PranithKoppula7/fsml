
#include "graph.h"
#include "operation.h"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include <string>
#include <map>
#include <vector>
#include <iostream>

static int ID = 1;

void dfs(tensor* t, 
         std::map<tensor*, Agnode_t*>& graph_map, 
         GVC_t* gvc,
         Agraph_t* r);

graph::graph() {}

void graph::run(tensor t) {

    GVC_t *gvc = gvContext();
    Agraph_t *g = agopen((char*)"g", Agundirected, 0);

    std::map<tensor*, Agnode_t*> graph_map;
    dfs(&t, graph_map, gvc, g);

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
        Agnode_t* curr = agnode(r, std::to_string(ID).data(), 1);
        ID++;
        agsafeset(curr, "label", t->repr().data(), "");
        graph_map[t] = curr;
    }

    if(t->parents_.size() == 0) return;

    Agnode_t* op = agnode(r, std::to_string(ID).data(), 1);
    ID++;
    agsafeset(op, "label", t->ctx_->op_.data(), "");
    agedge(r, graph_map[t], op, 0, 1);
    for (tensor* p: t->parents_) {
        dfs(p, graph_map, gvc, r);
        agedge(r, op, graph_map[p], 0, 1);
    }
}