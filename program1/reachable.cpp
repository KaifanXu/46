//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArraySet<std::string>          NodeSet;
//typedef ics::pair<std::string,NodeSet>      GraphEntry;
//
//bool graph_entry_gt (const GraphEntry& a, const GraphEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<GraphEntry,graph_entry_gt> GraphPQ;
//typedef ics::ArrayMap<std::string,NodeSet>  Graph;
//
//bool gt_alphabetic (const std::string& a, const std::string& b)
//{return a < b;}
//
////Read an open file of edges (node names separated by semicolons, with an
////  edge going from the first node name to the second node name) and return a
////  Graph (Map) of each node name associated with the Set of all node names to
////  which there is an edge from the key node name.
//Graph read_graph(std::ifstream &file) {
//	Graph graph;
//    Graph result;
//    ics::ArrayPriorityQueue<GraphEntry, graph_entry_gt> pq;
//    std::string line;
//    while(std::getline(file,line)){
//        std::vector<std::string> v = ics::split(line, ";");
//        if(!graph.has_key(v[0])){
//            ics::ArraySet<std::string> as;
//            //std::cout<<v[1]<<std::endl;
//            as.insert(v[1]);
//            graph.put(v[0],as);
//        }
//        else{
//            std::string temp = v[0];
//            graph[temp].insert(v[1]);
//        }
//    }
//    for (auto item : graph){
//        pq.enqueue(item);
//    }
//    for(auto entry : pq){
//        result.put(entry.first,entry.second);
//    }
//    return result;
//}
//
//
////Print a label and all the entries in the Graph in alphabetical order
////  (by source node).
////Use a "->" to separate the source node name from the Set of destination
////  node names to which it has an edge.
//void print_graph(const Graph& graph) {
//    std::cout<<"\n"<<"Graph: source node -> set of all destination nodes"<<std::endl;
//    for (auto item : graph){
//        std::cout<<"  "<<item.first<<" -> "<<item.second<<std::endl;
//    }
//    std::cout<<std::endl;
//}
//
//
////Return the Set of node names reaching in the Graph starting at the
////  specified (start) node.
////Use a local Set and a Queue to respectively store the reachable nodes and
////  the nodes that are being explored.
//NodeSet reachable(const Graph& graph, std::string start) {
//    ics::ArraySet<std::string> as;
//    if(graph.has_key(start)){
//        ics::ArrayQueue<std::string> nodes;
//        nodes.enqueue(start);
//        while(nodes.size() > 0){
//            std::string temp = nodes.dequeue();
//            as.insert(temp);
//            if (graph.has_key(temp)){
//                for (auto e : graph[temp]){
//                    nodes.enqueue(e);
//                }
//            }
//        }
//    }
//    return as;
//}
//
//
////Prompt the user for a file, create a graph from its edges, print the graph,
////  and then repeatedly (until the user enters "quit") prompt the user for a
////  starting node name and then either print an error (if that the node name
////  is not a source node in the graph) or print the Set of node names
////  reachable from it by using the edges in the Graph.
//int main() {
//  try {
//      std::string file_prompt="Enter a file storing a graph";
//      std::ifstream infile;
//      ics::safe_open(infile, file_prompt,"graph1.txt");
//      Graph map = read_graph(infile);
//      print_graph(map);
//      std::string answer;
//      std::cout<<"Enter a starting node name (or else quit):";
//      std::cin>>answer;
//      while(answer != "quit"){
//          ics::ArraySet<std::string> temp = reachable(map,answer);
//          if (temp.size() != 0){
//              std::cout<<"From "<<answer<<" the nodes reachable are in "<<temp<<"\n"<<std::endl;
//          }
//          else{
//              std::cout<<"  "<<answer<<" is not a source node name in the graph"<<"\n"<<std::endl;
//          }
//          std::cout<<"Enter a starting node name (or else quit):";
//          std::cin>>answer;
//      }
//      infile.close();
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
