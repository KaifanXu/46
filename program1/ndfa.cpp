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
//typedef ics::ArraySet<std::string>                     States;
//typedef ics::ArrayQueue<std::string>                   InputsQueue;
//typedef ics::ArrayMap<std::string,States>              InputStatesMap;
//
//typedef ics::ArrayMap<std::string,InputStatesMap>       NDFA;
//typedef ics::pair<std::string,InputStatesMap>           NDFAEntry;
//
//bool gt_NDFAEntry (const NDFAEntry& a, const NDFAEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<NDFAEntry,gt_NDFAEntry> NDFAPQ;
//
//typedef ics::pair<std::string,States>                   Transitions;
//typedef ics::ArrayQueue<Transitions>                    TransitionsQueue;
//
//
////Read an open file describing the non-deterministic finite automaton (each
////  line starts with a state name followed by pairs of transitions from that
////  state: (input followed by a new state, all separated by semicolons), and
////  return a Map whose keys are states and whose associated values are another
////  Map with each input in that state (keys) and the resulting set of states it
////  can lead to.
//const NDFA read_ndfa(std::ifstream &file) {
//    NDFA ndfa;
//    std::string line;
//    while(std::getline(file,line)){
//        InputsQueue q;
//        auto v = ics::split(line,";");
//        q.enqueue_all(v);
//        InputStatesMap input;
//        std::string temp_key = q.dequeue();
////        for(auto i : q){
////            input[i]
////        }
//        while(q.size() > 0){
//            input[q.dequeue()].insert(q.dequeue());
//        }
//        ndfa.put(temp_key,input);
//    }
//
//    return ndfa;
//}
//
//
////Print a label and all the entries in the finite automaton Map, in
////  alphabetical order of the states: each line has a state, the text
////  "transitions:" and the Map of its transitions.
//void print_ndfa(const NDFA& ndfa) {
//    std::cout<<"The Description of this Non-Deterministic Finite Automaton"<<std::endl;
//
//    NDFAPQ pq;
//    for(auto i : ndfa){
//        pq.enqueue(i);
//    }
//    for(auto j : pq){
//        std::cout<<"  "<<j.first<<" transitions: "<<j.second<<std::endl;
//    }
//}
//
//
////Return a queue of the calculated transition pairs, based on the non-deterministic
////  finite automaton, initial state, and queue of inputs; each pair in the returned
////  queue is of the form: input, set of new states.
////The first pair contains "" as the input and the initial state.
////If any input i is illegal (does not lead to any state in the non-deterministic finite
////  automaton), ignore it.
//TransitionsQueue process(const NDFA& ndfa, std::string state, const InputsQueue& inputs) {
//    TransitionsQueue tq;
//    States first_state;
//    first_state.insert(state);
//    Transitions first("", first_state);
//    tq.enqueue(first);
//    for(auto i : inputs){
//        States temp;
//        for(auto s : first_state){
//            if(ndfa[s].has_key(i)){
//                for(auto k : ndfa[s][i]){
//                    temp.insert(k);
//                }
//            }
//        }
//        Transitions trans(i,temp);
//        tq.enqueue(trans);
//        first_state = temp;
//    }
//    return tq;
//}
//
//
////Print a TransitionsQueue (the result of calling process) in a nice form.
////Print the Start state on the first line; then print each input and the
////  resulting new states indented on subsequent lines; on the last line, print
////  the Stop state.
//void interpret(TransitionsQueue& tq) {  //or TransitionsQueue or TransitionsQueue&&
//    std::cout<<"Start state = "<<tq.dequeue().second<<std::endl;
//    Transitions trans;
//    while(tq.size() > 0){
//        //Transitions trans = tq.dequeue();
//        trans = tq.dequeue();
//        std::cout<<"  Input = "<<trans.first<<"; new states possible = ";
//        std::cout<<trans.second<<std::endl;
//    }
//    std::cout<<"Stop state(s) = "<<trans.second<<std::endl;
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
//      std::string file_prompt="Enter a file storing a non-deterministic finite automaton";
//      ics::safe_open(infile, file_prompt,"ndfaendin01.txt");
//      NDFA ndfa = read_ndfa(infile);
//      print_ndfa(ndfa);
//      infile.close();
//      std::cout<<std::endl;
//      file_prompt="Enter a file storing a start-state and its inputs";
//      ics::safe_open(infile, file_prompt,"ndfainputendin01.txt");
//
//      std::string line;
//      while(std::getline(infile,line)){
//          std::cout<<"\n"<<"Starting up new NDFA simulation of: "<<line<<std::endl;
//          InputsQueue q;
//          auto v = ics::split(line,";");
//          for(auto i : v){
//              q.enqueue(i);
//          }
//          std::string start_state = q.dequeue();
//          TransitionsQueue tq = process(ndfa,start_state,q);
//          interpret(tq);
//      }
//      infile.close();
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
