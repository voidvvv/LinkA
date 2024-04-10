#ifndef __ASTAR_H__
#define __ASTAR_H__
#include <vector>

template <typename N>
class Connection
{
public:
    virtual float getCost() = 0;
    virtual N *getFromNode() = 0;
    virtual N *getToNode() = 0;
};

template <typename N>
class Graph
{
public:
    virtual std::vector<Connection<N> *> getConnections(N *fromNode) = 0;
    virtual std::vector<Connection<N> *> getConnections(N *fromNode, N *matchNode) = 0;
    virtual int getIndex(N *node) = 0;
    virtual int size() = 0;
};

template <typename N>
class Heuristic
{
public:
    virtual float estimate(N *node, N *endNode) = 0;
};

enum Node_Category
{
    UNVISITED,
    OPEN,
    CLOSE
};

template <typename N>
class NodeRecord
{
public:
    N *node;

    /** The incoming connection to the node */
    Connection<N> *connection;

    /** The actual cost from the start node. */
    float costSoFar = 0.f;

    float estimate = 0.f;

    /** The node category: {@link #UNVISITED}, {@link #OPEN} or {@link #CLOSED}. */
    Node_Category category = Node_Category::UNVISITED;

    /** ID of the current search. */
    unsigned int searchId = 0;

    float value() const{
        return estimate;
    };

    virtual bool operator==(const NodeRecord<N> &a) const 
    {
        return value() == a.value();
    };
    virtual bool operator>(const NodeRecord<N> &a) const 
    {
        return value() > a.value();
    };
    virtual bool operator>=(const NodeRecord<N> &a) const 
    {
        return value() >= a.value();
    };
    virtual bool operator<(const NodeRecord<N> &a) const 
    {
        return value() < a.value();
    };
    virtual bool operator<=(const NodeRecord<N> &a) const 
    {
        return value() <= a.value();
    };
};

template <typename N>
class PathFinder
{
public:
    virtual bool searchNodePath(N *startNode, N *endNode,
                                float (*_Heuristic)(N *, N *),
                                bool (*_shouldStop)(N *, N *),
                                std::vector<N *> &outPath) = 0;
    // virtual bool searchNodePath(N *startNode, N *endNode, Heuristic<N> &, std::vector<N *> &outPath) = 0;

    virtual void generateNodePath(N *startNode, std::vector<N *> &outPath) = 0;
};

#endif // __ASTAR_H__