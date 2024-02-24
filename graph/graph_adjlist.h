
#ifndef _GRAPH_ADJLIST_H
#define _GRAPH_ADJLIST_H

#include "linked_list_queue.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
/**
 * \brief: 节点类
 */
template<typename T>
struct Vertex {
    T val;
    Vertex(T v)
        : val(v) {}
};

/**
 * \brief: 无向图, 邻接表链表实现
 *
 * 图vertex个数为n, edge数为m
 *
 * 时间复杂度:
 *  判断邻接:  O(m)
 *  add edge: O(1)
 *  del edge: O(m)
 *  add vertex: O(1)
 *  del vertex: O(n + m)
 *
 * 空间复杂度: O(n + m)
 */
template<typename T>
class GraphAdjList {
public:
    GraphAdjList(const std::vector<std::vector<Vertex<T> *>> &edges) {
        for (const std::vector<Vertex<T> *> &edge : edges) {
            AddVertex(edge[0]);
            AddVertex(edge[1]);
            AddEdge(edge[0], edge[1]);
        }
    }
    int Size() const { return _adj_list.size(); }

    bool IsAdjacent(Vertex<T> *v1, Vertex<T> *v2) {
        if (_adj_list.count(v1) <= 0 || _adj_list.count(v2) <= 0)
            throw std::runtime_error("Vertex is not exist.");
        std::vector<Vertex<T> *> &v1v = _adj_list[v1];
        std::vector<Vertex<T> *> &v2v = _adj_list[v2];
        return std::find(v1v.cbegin(), v1v.cend(), v2) != v1v.end() &&
               std::find(v2v.cbegin(), v2v.cend(), v1) != v2v.end();
    }

    void AddVertex(Vertex<T> *vet) {
        if (_adj_list.count(vet) > 0) return;
        _adj_list[vet] = std::vector<Vertex<T> *>();
    }

    void RemoveVertex(Vertex<T> *vet) {
        if (_adj_list.count(vet) <= 0) throw std::runtime_error("Vertex is not exist.");

        auto &vet_val = _adj_list[vet];   // vet 's adj list
        for (auto &v : vet_val) {
            auto &vs = _adj_list[v];   // v's adj list
            remove(vs, vet);
        }
        _adj_list.erase(vet);
    }

    void AddEdge(Vertex<T> *v1, Vertex<T> *v2) {
        if (_adj_list.count(v1) < 0 || _adj_list.count(v2) < 0 || v1 == v2)
            throw std::runtime_error("Vertex is not exist or v1==v2.");

        // FIXME: 如果用户重复调用AddEdge, 则v1的邻接表中会有重复的v2
        _adj_list[v1].push_back(v2);
        _adj_list[v2].push_back(v1);
    }

    void RemoveEdge(Vertex<T> *v1, Vertex<T> *v2) {
        if (_adj_list.count(v1) < 0 || _adj_list.count(v2) < 0 || v1 == v2)
            throw std::runtime_error("Vertex is not exist or v1==v2.");
        remove(_adj_list[v1], v2);
        remove(_adj_list[v2], v1);
    }

    void Print() {
        for (auto &kv : _adj_list) {
            const auto &k = kv.first;
            const auto &v = kv.second;
            std::cout << k->val << ": ";
            for (auto i : v) std::cout << i->val << ", ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // 广度优先搜索. start开始遍历的顶点
    std::vector<Vertex<T> *> Bfs(Vertex<T> *start) {
        if (_adj_list.count(start) <= 0) throw std::runtime_error("Vertex is not exist.");

        std::vector<Vertex<T> *>        res;       // 存放bfs遍历结果
        std::unordered_set<Vertex<T> *> visited;   // 已访问过的顶点
        LinkedListQueue<Vertex<T> *>    queue;

        queue.Push(start);
        visited.emplace(start);
        while (!queue.Empty()) {
            Vertex<T> *vet = queue.Pop();
            res.push_back(vet);

            for (auto v : _adj_list[vet]) {
                if (visited.count(v) <= 0) {
                    queue.Push(v);
                    visited.emplace(v);
                }
            }
        }
        return res;
    }

    // 深度优先搜索. start开始遍历的顶点
    std::vector<Vertex<T> *> Dfs(Vertex<T> *start) {
        if (_adj_list.count(start) <= 0) throw std::runtime_error("Vertex is not exist.");

        std::vector<Vertex<T> *> res;   // 存放bfs遍历结果
        dfs(res, start);
        return res;
    }

private:
    void dfs(std::vector<Vertex<T> *> &res, Vertex<T> *vet) {
        static std::unordered_set<Vertex<T> *> visited;   // 已访问过的顶点

        res.push_back(vet);
        visited.emplace(vet);
        for (auto v : _adj_list[vet]) {
            if (visited.count(v) <= 0) dfs(res, v);
        }
    }
    /**
     * 从vets中删除vet
     */
    void remove(std::vector<Vertex<T> *> &vets, const Vertex<T> *vet) {
        for (int i = 0; i < vets.size(); i++) {
            if (vets[i] == vet) {
                vets.erase(vets.begin() + i);
                break;
            }
        }
    }
    // key是顶点, value是顶点所有的邻接顶点
    std::unordered_map<Vertex<T> *, std::vector<Vertex<T> *>> _adj_list;
};


#endif