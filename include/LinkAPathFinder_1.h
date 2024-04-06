#ifndef __LINKAPATHFINDER_1_H__
#define __LINKAPATHFINDER_1_H__

#include "AStar.h"

class LinkANode
{
public:
    int x;
    int y;
    int index;
    std::vector<Connection<LinkANode> *> connections;
};

class LinkAConnection : public Connection<LinkANode>
{
public:
    float cost;
    LinkANode *fromNode;
    LinkANode *toNode;

    float getCost();
    LinkANode *getFromNode();
    LinkANode *getToNode();
};

class LinkAGraph : public Graph<LinkANode>
{
private:
    const std::vector<Connection<LinkANode> *> emptyConnections;
    std::vector<LinkANode *> nodeVector;

public:
    std::vector<Connection<LinkANode> *> getConnections(LinkANode *fromNode);
    int getIndex(LinkANode *node);
    int size();
};
#endif // __LINKAPATHFINDER_1_H__