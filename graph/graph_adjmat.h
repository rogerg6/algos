
#ifndef _GRAPH_ADJMAT_H
#define _GRAPH_ADJMAT_H

#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * \brief: 无向图, 邻接矩阵实现
 *
 * 图vertex个数为n, edge数为m
 *
 * 时间复杂度:
 *  判断邻接:  O(1)
 *  add edge: O(1)
 *  del edge: O(1)
 *  add vertex: O(n)
 *  del vertex: O(n^2)
 *
 * 空间复杂度: O(n^2)
 */
template<typename T>
class GraphAdjMat {
public:
    /**
     * @param vertices: 顶点的值列表. eg. {1, 2, 3, 4}
     * @param edges   : 顶点对的索引对. eg. {(0,1), (0,2)}
     */
    GraphAdjMat(const std::vector<T> &vertices, const std::vector<std::vector<int>> &edges) {
        // _vertices = vertices;
        int len = vertices.size();
        for (int i = 0; i < len; i++) {
            // _adj_mat.push_back(std::vector<int>(len, 0));
            AddVertex(vertices[i]);
        }

        for (auto &edge : edges) AddEdge(edge[0], edge[1]);
    }

    // 返回顶点数量
    int Size() const { return _vertices.size(); }

    bool IsAdjacent(int i, int j) {
        if (i < 0 || j < 0 || i >= Size() || j >= Size() || i == j)
            throw std::runtime_error("Index out of boundary.");
        return _adj_mat[i][j] == 1 && _adj_mat[j][i] == 1;
    }

    // 增加顶点
    void AddVertex(T val) {
        int n = Size();
        _vertices.push_back(val);
        _adj_mat.emplace_back(std::vector<int>(n, 0));
        for (auto &row : _adj_mat) row.emplace_back(0);
    }
    // 删除顶点
    void RemoveVertex(int index) {
        if (index < 0 || index >= Size()) throw std::runtime_error("Index out of boundary.");
        _vertices.erase(_vertices.begin() + index);
        _adj_mat.erase(_adj_mat.begin() + index);
        for (auto &row : _adj_mat) row.erase(row.begin() + index);
    }

    // 增加边
    void AddEdge(int i, int j) {
        if (i < 0 || j < 0 || i >= Size() || j >= Size() || i == j)
            throw std::runtime_error("Index out of boundary.");
        _adj_mat[i][j] = 1;
        _adj_mat[j][i] = 1;
    }

    // 删除边
    void RemoveEdge(int i, int j) {
        if (i < 0 || j < 0 || i >= Size() || j >= Size() || i == j)
            throw std::runtime_error("Index out of boundary.");
        _adj_mat[i][j] = 0;
        _adj_mat[j][i] = 0;
    }

    void Print() {
        std::cout << "      ";
        for (int i = 0; i < Size(); i++) std::cout << _vertices[i] << " ";
        std::cout << "\n      ";
        for (int i = 0; i < Size(); i++) std::cout << i << " ";
        std::cout << std::endl << std::endl;
        for (int i = 0; i < Size(); i++) {
            std::cout << _vertices[i] << " ";
            std::cout << i << "   ";
            for (int j = 0; j < Size(); j++) std::cout << _adj_mat[i][j] << " ";
            std::cout << std::endl;
        }
    }

private:
    std::vector<T>                _vertices;   // 顶点列表
    std::vector<std::vector<int>> _adj_mat;    // 邻接矩阵. 存储顶点间的边关系
};


#endif