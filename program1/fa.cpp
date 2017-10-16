//
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
//typedef ics::ArrayQueue<std::string>                InputsQueue;
//typedef ics::ArrayMap<std::string,std::string>      InputStateMap;
//
//typedef ics::ArrayMap<std::string,InputStateMap>    FA;
//typedef ics::pair<std::string,InputStateMap>        FAEntry;
//
//bool gt_FAEntry (const FAEntry& a, const FAEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<FAEntry,gt_FAEntry> FAPQ;
//
//typedef ics::pair<std::string,std::string>          Transition;
//typedef ics::ArrayQueue<Transition>                 TransitionQueue;
//
//
////Read an open file describing the finite automaton (each line starts with
////  a state name followed by pairs of transitions from that state: (input
////  followed by new state, all separated by semicolons), and return a Map
////  whose keys are states and whose associated values are another Map with
////  each input in that state (keys) and the resulting state it leads to.
//const FA read_fa(std::ifstream &file) {
//     FA fa;
//     std::string line;
//     while(std::getline(file,line)){
//         std::vector<std::string> v = ics::split(line, ";");
//         InputStateMap temp_v;
//         temp_v.put(v[1],v[2]);
//         temp_v.put(v[3],v[4]);
//         fa.put(v[0],temp_v);
//     }
//     return fa;
//}
//
//
////Print a label and all the entries in the finite automaton Map, in
////  alphabetical order of the states: each line has a state, the text
////  "transitions:" and the Map of its transitions.
//void print_fa(const FA& fa) {
//     std::cout<<"The Description of this Finite Automaton"<<std::endl;
//     FAPQ pq;
//     for(auto i : fa){
//         pq.enqueue(i);
//     }
//     for(auto j : pq){
//         std::cout<<"  "<<j.first<<" transitions: "<<j.second<<std::endl;
//     }
//     std::cout<<std::endl;
//}
//
//
////Return a queue of the calculated transition pairs, based on the finite
////  automaton, initial state, and queue of inputs; each pair in the returned
////  queue is of the form: input, new state.
////The first pair contains "" as the input and the initial state.
////If any input i is illegal (does not lead to a state in the finite
////  automaton), then the last pair in the returned queue is i,"None".
//TransitionQueue process(const FA& fa, std::string state, const InputsQueue& inputs) {
//     TransitionQueue tq;
//     std::string temp = state;
//     for(auto i : inputs){
//         if(tq.size() == 0){
//             Transition first ("", state);
//             tq.enqueue(first);
//         }
//         if(!fa[temp].has_key(i)){
//             Transition none("x","None");
//             tq.enqueue(none);
//             break;
//         }
//         else{
//             Transition next(i,fa[temp][i]);
//             tq.enqueue(next);
//             temp = fa[temp][i];
//         }
//     }
//     return tq;
//}
//
//
////Print a TransitionQueue (the result of calling the process function above)
//// in a nice form.
////Print the Start state on the first line; then print each input and the
////  resulting new state (or "illegal input: terminated", if the state is
////  "None") indented on subsequent lines; on the last line, print the Stop
////  state (which may be "None").
//void interpret(TransitionQueue& tq) {  //or TransitionQueue or TransitionQueue&&
//     std::cout<<"Start state = "<<tq.dequeue().second<<std::endl;
//     Transition temp;
//     while (tq.size() > 0){
//         if (tq.peek().first == "x" || tq.peek().second == "None"){
//             std::cout<<"  Input = x; illegal input: simulation terminated"<<std::endl;
//             temp.second="None";
//             break;
//         }
//         else{
//             temp = tq.dequeue();
//             std::cout<<"  Input = "<<temp.first<<"; ";
//             std::cout<<"state = "<<temp.second<<std::endl;
//         }
//     }
//    std::cout<<"Stop state = "<<temp.second<<std::endl;
//}
//
//
//
////Prompt the user for a file, create a finite automaton Map, and print it.
////Prompt the user for a file containing any number of simulation descriptions
////  for the finite automaton to process, one description per line; each
////  description contains a start state followed by its inputs, all separated by
////  semicolons.
////Repeatedly read a description, print that description, put each input in a
////  Queue, process the Queue and print the results in a nice form.
//int main() {
//  try {
//      std::ifstream infile;
//      std::string file_prompt="Enter a file storing a finite automaton";
//      ics::safe_open(infile, file_prompt,"faparity.txt");
//      FA fa = read_fa(infile);
//      print_fa(fa);
//      infile.close();
//
//      file_prompt="Enter a file storing a start-state and its inputs";
//      ics::safe_open(infile, file_prompt,"fainputparity.txt");
//      std::string line;
//      while(std::getline(infile,line)){
//          std::cout<<"\n"<<"Starting up a new FA simulation of: "<<line<<std::endl;
//          InputsQueue q;
//          auto v = ics::split(line,";");
//          for(auto i : v){
//              q.enqueue(i);
//          }
//          std::string start_state = q.dequeue();
//          TransitionQueue tq = process(fa,start_state,q);
//          interpret(tq);
//      }
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
