#ifndef __LINKAPATHFINDER_1_H__
#define __LINKAPATHFINDER_1_H__

#include "AStar.h"
#include "GameObject.h"
#include <memory>

enum LinkANodeType
{
    CARD,
    OBSTACLE
};

enum LinkANodeValid
{
    NODE_VALID,
    NODE_INVALID
};
class LinkANode
{
public:
    int x;
    int y;
    int index;
    LinkANodeType nodeType;
    LinkANodeValid nodeStatus;
    std::shared_ptr<GameObject> obj;
    virtual std::vector<Connection<LinkANode> *> getAllValidConnection() = 0;
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

public:
    std::vector<LinkANode *> nodeVector;
    void create();
    std::vector<Connection<LinkANode> *> getConnections(LinkANode *fromNode);
    std::vector<Connection<LinkANode> *> getConnections(LinkANode *fromNode, LinkANode *matchNode);
    int getIndex(LinkANode *node);
    int size();
};
#endif // __LINKAPATHFINDER_1_H__