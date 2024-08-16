#include <iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<string>

using namespace std;

struct Node{
    double x,y;
    double fx,fy;
};
struct Edge{
    int start,end;
};

struct Graph{
    vector<Node>nodes;
    vector<Edge>edges;
};

bool readGraph(const string& filename, Graph& graph) {//這也是一種檢查文件是否打開打方式，還有一種就是作業3例寫的
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }


int numNodes;
    file >> numNodes;  // Read the number of nodes
    Graph.nodes.resize(numNodes); 

int start, end;
    while (file >> start >> end) {
        graph.edges.push_back({start, end});//添加邊到vector容器中
    }

    file.close();
    return true;
}

void initializeNodePositions(Graph& graph) {
    const double PI = 3.14159265358979323846;
    int numNodes = graph.nodes.size();
    for (int i = 0; i < numNodes; ++i) {
        graph.nodes[i].x = cos(2 * PI * i / numNodes);
        graph.nodes[i].y = sin(2 * PI * i / numNodes);
        graph.nodes[i].fx = 0;  // Initialize force components to zero
        graph.nodes[i].fy = 0;
    }
}

void calculateRepulsiveForces(Graph& graph) {
    const double kRepel = 0.001;  // Repulsion constant
    for (size_t i = 0; i < graph.nodes.size(); ++i) {
        for (size_t j = i + 1; j < graph.nodes.size(); ++j) {
            double dx = graph.nodes[j].x - graph.nodes[i].x;
            double dy = graph.nodes[j].y - graph.nodes[i].y;
            double distance = sqrt(dx * dx + dy * dy);
            double forceMagnitude = kRepel / (distance * distance);
            double fx = forceMagnitude * dx / distance;
            double fy = forceMagnitude * dy / distance;
            
            graph.nodes[i].fx -= fx;
            graph.nodes[i].fy -= fy;
            graph.nodes[j].fx += fx;
            graph.nodes[j].fy += fy;
        }
    }
}

void calculateAttractiveForces(Graph& graph) {
    const double kAttract = 0.001;  // Attraction constant
    for (const auto& edge : graph.edges) {
        Node& nodeStart = graph.nodes[edge.start];
        Node& nodeEnd = graph.nodes[edge.end];
        double dx = nodeEnd.x - nodeStart.x;
        double dy = nodeEnd.y - nodeStart.y;
        double distance = sqrt(dx * dx + dy * dy);
        double forceMagnitude = kAttract * (distance * distance);
        double fx = forceMagnitude * dx / distance;
        double fy = forceMagnitude * dy / distance;
        
        nodeStart.fx += fx;
        nodeStart.fy += fy;
        nodeEnd.fx -= fx;
        nodeEnd.fy -= fy;
    }
}
void updateNodePositions(Graph& graph) {
    const double damping = 0.05;  // Damping factor to avoid overshooting
    for (auto& node : graph.nodes) {
        node.x += damping * node.fx;
        node.y += damping * node.fy;
        
        // Reset forces after moving
        node.fx = 0;
        node.fy = 0;
    }
}


int main()
{
std::cout << "Graph Layout Program Started." << std::endl;//初始化一下告知一下這個程序
Graph graph;
    string filename;
    cout << "Enter the filename of the graph: ";
    getline(cin,filename);

    if (!readGraph(filename, graph)) {
        return 1;  // Error occurred
    }

    initializeNodePositions(graph);

    for (int iter = 0; iter < 1000; ++iter) {  // For a set number of iterations
        calculateRepulsiveForces(graph);
        calculateAttractiveForces(graph);
        updateNodePositions(graph);

cout << "Final node positions:" << endl;
    for (const auto& node : graph.nodes) {
        cout << "Node position: (" << node.x << ", " << node.y << ")" << endl;
    }

    return 0;
}
}