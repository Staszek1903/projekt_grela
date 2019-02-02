#ifdef __linux__
    #include "include/guinode.h"
#else
    #include "guinode.h"
#endif

#include <vector>
#include <cstdio>

class GuiManager
{
    std::vector <GuiNode *> nodes;
public:
    GuiNode * addNode(GuiNode *);
    void update(GuiEvent *);
    void draw();

    GuiManager();
    ~GuiManager();
};
