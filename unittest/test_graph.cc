
#include "graph_adjlist.h"
#include "graph_adjmat.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(graph_adj_mat, function_test) {
    /**
     1 --- 5 \
     |     |  4
     3 --- 2 /
    */
    std::vector<int>              vertices = {1, 2, 3, 4, 5};
    std::vector<std::vector<int>> edges    = {{0, 2}, {0, 4}, {1, 4}, {1, 2}, {1, 3}, {3, 4}};

    GraphAdjMat<int> g(vertices, edges);
    for (auto &e : edges) EXPECT_TRUE(g.IsAdjacent(e[0], e[1]));
    EXPECT_FALSE(g.IsAdjacent(0, 3));
    EXPECT_FALSE(g.IsAdjacent(0, 1));
    // g.Print();

    g.RemoveEdge(0, 2);   // delete edge(1,3)
    EXPECT_FALSE(g.IsAdjacent(0, 2));
    // g.Print();

    g.RemoveVertex(3);   // delete vertex 4
    // g.Print();
}

TEST(graph_adj_list, function_test) {
    Vertex<int> *n1 = new Vertex<int>(1);
    Vertex<int> *n2 = new Vertex<int>(2);
    Vertex<int> *n3 = new Vertex<int>(3);
    Vertex<int> *n4 = new Vertex<int>(4);
    Vertex<int> *n5 = new Vertex<int>(5);

    /**
     1 --- 5 \
     |     |  4
     3 --- 2 /
    */
    std::vector<std::vector<Vertex<int> *>> edges = {
        {n1, n3}, {n1, n5}, {n2, n3}, {n2, n5}, {n4, n2}, {n4, n5}};

    GraphAdjList<int> g(edges);
    // g.Print();
    for (auto &e : edges) EXPECT_TRUE(g.IsAdjacent(e[0], e[1]));
    EXPECT_FALSE(g.IsAdjacent(n1, n4));
    EXPECT_FALSE(g.IsAdjacent(n1, n2));

    g.RemoveEdge(n1, n3);
    // g.Print();
    EXPECT_FALSE(g.IsAdjacent(n1, n3));

    g.RemoveVertex(n4);
    // g.Print();

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
}

TEST(graph_adj_list, BFS) {
    Vertex<int>                            *n0    = new Vertex<int>(0);
    Vertex<int>                            *n1    = new Vertex<int>(1);
    Vertex<int>                            *n2    = new Vertex<int>(2);
    Vertex<int>                            *n3    = new Vertex<int>(3);
    Vertex<int>                            *n4    = new Vertex<int>(4);
    Vertex<int>                            *n5    = new Vertex<int>(5);
    Vertex<int>                            *n6    = new Vertex<int>(6);
    Vertex<int>                            *n7    = new Vertex<int>(7);
    Vertex<int>                            *n8    = new Vertex<int>(8);
    std::vector<std::vector<Vertex<int> *>> edges = {{n0, n1},
                                                     {n0, n3},
                                                     {n1, n2},
                                                     {n2, n5},
                                                     {n5, n8},
                                                     {n7, n8},
                                                     {n3, n6},
                                                     {n6, n7},
                                                     {n4, n1},
                                                     {n4, n3},
                                                     {n4, n5},
                                                     {n4, n7}};
    GraphAdjList<int>                       g(edges);

    /*
     n0 --- n1 --- n2
      |      |     |
     n3 --- n4 --- n5
      |      |     |
     n6 --- n7 --- n8
    */
    std::vector<Vertex<int> *> res = g.Bfs(n0);
    EXPECT_EQ(res, std::vector<Vertex<int> *>({n0, n1, n3, n2, n4, n6, n5, n7, n8}));

    delete n0;
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
    delete n7;
    delete n8;
}

TEST(graph_adj_list, DFS) {
    Vertex<int>                            *n0    = new Vertex<int>(0);
    Vertex<int>                            *n1    = new Vertex<int>(1);
    Vertex<int>                            *n2    = new Vertex<int>(2);
    Vertex<int>                            *n3    = new Vertex<int>(3);
    Vertex<int>                            *n4    = new Vertex<int>(4);
    Vertex<int>                            *n5    = new Vertex<int>(5);
    Vertex<int>                            *n6    = new Vertex<int>(6);
    std::vector<std::vector<Vertex<int> *>> edges = {
        {n0, n1}, {n0, n3}, {n1, n2}, {n2, n5}, {n4, n5}, {n5, n6}};
    /*
     n0 --- n1 --- n2
      |            |
     n3     n4 --- n5
                   |
                   n6
    */
    GraphAdjList<int> g(edges);

    std::vector<Vertex<int> *> res = g.Dfs(n0);
    EXPECT_EQ(res, std::vector<Vertex<int> *>({n0, n1, n2, n5, n4, n6, n3}));

    delete n0;
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
}