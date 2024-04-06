#include "LinkAFinder.h"
#include <algorithm>

LinkANode *LinkAConnection::getFromNode()
{
    return this->fromNode;
}

LinkANode *LinkAConnection::getToNode()
{
    return this->toNode;
}

float LinkAConnection::getCost()
{
    return 1;
}

std::vector<Connection<LinkANode> *> LinkAGraph::getConnections(LinkANode *fromNode)
{
    typename std::vector<LinkANode*>::iterator it =
        std::find(this->nodeVector.begin(), this->nodeVector.end(), fromNode);
    if (it == this->nodeVector.end()){
        return emptyConnections;
    }
    return (*it)->connections;
}

int LinkAGraph::getIndex(LinkANode *node)
{
    return node->index;
};
int LinkAGraph::size()
{
    return this->nodeVector.size();
};