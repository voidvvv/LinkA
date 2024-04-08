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
    return (*it)->getAllValidConnection();
}

// std::vector<Connection<N> *> getConnections(N *fromNode, N* matchNode)
std::vector<Connection<LinkANode> *> LinkAGraph::getConnections(LinkANode *fromNode, LinkANode *matchNode)
{
    return getConnections(fromNode);
}


int LinkAGraph::getIndex(LinkANode *node)
{
    return node->index;
};
int LinkAGraph::size()
{
    return this->nodeVector.size();
};

void LinkAGraph::create(){
    this->nodeVector.clear();
};