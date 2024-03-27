#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

int main() {
    GVC_t *gvc = gvContext();

    Agraph_t *g = agopen((char*)"g", Agundirected, 0);
    Agnode_t *n = agnode(g, "a", 1);
    Agnode_t *m = agnode(g, "m", 1);
    Agedge_t *e = agedge(g, n, m, 0, 1);

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "graph.png");

    gvFreeLayout(gvc, g);
    agclose(g);
    return gvFreeContext(gvc);
}