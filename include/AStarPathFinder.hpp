#ifndef __ASTARPATHFINDER_H__
#define __ASTARPATHFINDER_H__

#include "AStar.h"
#include <memory>
#include <algorithm>

template <typename N>
class AStarPathFinder : public PathFinder<N>
{
private:
    unsigned int searchId = 0;
    std::vector<NodeRecord<N> *> records;
    Graph<N>* graph;
    NodeRecord<N> *current;

public:
    NodeRecord<N> *getNodeRecord(N *node)
    {
        Graph<N> *gp = graph;
        int index = gp->getIndex(node);
        NodeRecord<N> *nodeRecord = records[index];
        if (nodeRecord == NULL)
        {
            nodeRecord = new NodeRecord<N>();
            nodeRecord->category = Node_Category::UNVISITED;
            nodeRecord->searchId = this->searchId;
            nodeRecord->connection = NULL;
            records[index] = nodeRecord;
        }
        if (nodeRecord->searchId != this->searchId)
        {
            nodeRecord->searchId = this->searchId;
            nodeRecord->connection = NULL;
            nodeRecord->category = Node_Category::UNVISITED;
        }
        nodeRecord->node = node;
        return nodeRecord;
    }

    void init(Graph<N> *_graph)
    {
        current = NULL;
        records = std::vector<NodeRecord<N> *>(_graph->size());
        this->graph = _graph;
        // this->graph = std::shared_ptr<Graph<N>>(_graph);
    }
    void generateNodePath(N *startNode, std::vector<N *> &outPath) override
    {
        // todo
        while (current && current->connection)
        {
            outPath.push_back(current->node);
            // current->connection->getFromNode
            Graph<N> *gp = graph;
            current = records[gp->getIndex(current->connection->getFromNode())];
        }
        outPath.push_back(startNode);
    }

    void visitChild(N *end, float (*_Heuristic)(N *, N *), std::vector<NodeRecord<N> *> &openList)
    {
        Graph<N> *graphPtr = this->graph;

        std::vector<Connection<N> *> connections = graphPtr->getConnections(current->node, end);

        for (int x = 0; x < connections.size(); x++)
        {
            Connection<N> *con = connections[x];
            N *toNode = con->getToNode();
            float nodeCost = current->costSoFar + con->getCost();

            NodeRecord<N> *nrNode = getNodeRecord(toNode);

            if (toNode == end)
            {
                nrNode->costSoFar = nodeCost;
                nrNode->connection = con;

                nrNode->category = Node_Category::OPEN;
                openList.push_back(nrNode);
                return;
            }
            float nodeHeuristic;

            if (nrNode->category == Node_Category::CLOSE)
            {
                if (nrNode->costSoFar <= nodeCost)
                    continue;
                nodeHeuristic = nrNode->estimate - nrNode->costSoFar;
            }
            else if (nrNode->category == Node_Category::OPEN)
            {
                if (nrNode->costSoFar <= nodeCost)
                {
                    continue;
                }
                openList.erase(std::find(openList.begin(), openList.end(), nrNode));
                nodeHeuristic = nrNode->estimate - nrNode->costSoFar;
            }
            else
            {
                nodeHeuristic = _Heuristic(toNode, end);
            }

            nrNode->costSoFar = nodeCost;
            nrNode->connection = con;
            nrNode->estimate = nodeHeuristic + nodeCost;
            nrNode->category = Node_Category::OPEN;
            // openList.push_back(nrNode);
            putNodeRecord(nrNode, openList);
        }
    }

    void putNodeRecord(NodeRecord<N> *nrNode, std::vector<NodeRecord<N> *> &openList)
    {
        // 默认按照从大到小排序,这样pop back获取到的就是当前最小的元素
        int left = 0;
        int right = openList.size() - 1;
        int mid = left + (right - left) / 2;
        while (left <= right)
        {
            mid = left + (right - left) / 2; // 防止溢出
            if ((*openList[mid]) == *nrNode)
            {
                openList.insert(openList.begin() + mid, nrNode);
                return; // 目标值在数组中的索引
            }
            else if ((*openList[mid]) > *nrNode)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        openList.insert(openList.begin()+mid, nrNode);
    }

    bool searchNodePath(N *startNode, N *endNode,
                        float (*_Heuristic)(N *, N *),
                        bool (*_shouldStop)(N *, N *),
                        std::vector<N *> &outPath) override
    {
        this->current = NULL;
        std::vector<NodeRecord<N> *> openList;
        this->searchId++;
        NodeRecord<N> *nr = getNodeRecord(startNode);
        nr->category = Node_Category::OPEN;
        nr->connection = NULL;
        openList.push_back(nr);

        while (openList.size() > 0)
        {
            this->current = openList.back();
            openList.pop_back();
            this->current->category = Node_Category::CLOSE;

            if (_shouldStop(this->current->node, endNode))
            {
                generateNodePath(startNode, outPath);
                return true;
            }
            visitChild(endNode, _Heuristic, openList);
        }
        return false;
    }
};
#endif // __ASTARPATHFINDER_H__