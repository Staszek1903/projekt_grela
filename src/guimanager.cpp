#ifdef __linux__
    #include "include/guimanager.h"
#else
    #include "guimanager.h"
#endif


GuiNode *GuiManager::addNode(GuiNode * n)
{
    nodes.push_back(n);
    return n;
}

void GuiManager::update(GuiEvent * ev)
{
    //printf("size: %i\n", nodes.size());
    for(auto n : nodes)
        n->update(ev);
}

void GuiManager::draw()
{
    for(auto n: nodes)
        n->draw();
}

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager()
{
    for(auto n : nodes)
        delete n;
}
