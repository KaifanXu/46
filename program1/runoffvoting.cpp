//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArrayQueue<std::string>              CandidateQueue;
//typedef ics::ArraySet<std::string>                CandidateSet;
//typedef ics::ArrayMap<std::string,int>            CandidateTally;
//
//
//
//typedef ics::ArrayMap<std::string,CandidateQueue> Preferences;
//typedef ics::pair<std::string,CandidateQueue>     PreferencesEntry;
//
//bool preferences_entry_gt (const PreferencesEntry& a, const PreferencesEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<PreferencesEntry, preferences_entry_gt> PreferencesEntryPQ; //Must supply gt at construction
//
//typedef ics::pair<std::string,int>                TallyEntry;
//typedef ics::ArrayPriorityQueue<TallyEntry>       TallyEntryPQ;
//
//
//
////Read an open file stating voter preferences (each line is (a) a voter
////  followed by (b) all the candidates the voter would vote for, in
////  preference order (from most to least preferred candidate, separated
////  by semicolons), and return a Map of preferences: a Map whose keys are
////  voter names and whose values are a queue of candidate preferences.
//Preferences read_voter_preferences(std::ifstream &file) {
//    Preferences p_map;
//    std::string line;
//    while(std::getline(file,line)){
//        std::vector<std::string> v = ics::split(line, ";");
//        std::string temp_key=v[0];
//        CandidateQueue q;
//        for(auto i : v){
//            q.enqueue(i);
//        }
//        q.dequeue();
//        p_map.put(temp_key,q);
//    }
//    return p_map;
//}
//
//
////Print a label and all the entries in the preferences Map, in alphabetical
////  order according to the voter.
////Use a "->" to separate the voter name from the Queue of candidates.
//void print_voter_preferences(const Preferences& preferences) {
//    std::cout<<std::endl;
//    PreferencesEntryPQ pq;
//    for (auto item : preferences){
//        pq.enqueue(item);
//    }
//    std::cout<<"Voter name -> queue of Preferences"<<std::endl;
//    for (auto entry : pq){
//        std::cout<<"  "<<entry.first<<" -> "<<entry.second<<std::endl;
//    }
//    std::cout<<std::endl;
//}
//
//
////Print the message followed by all the entries in the CandidateTally, in
////  the order specified by has_higher_priority: i is printed before j, if
////  has_higher_priority(i,j) returns true: sometimes alphabetically by candidate,
////  other times by decreasing votes for the candidate.
////Use a "->" to separate the candidat name from the number of votes they
////  received.
//void print_tally(std::string message, const CandidateTally& tally, bool (*has_higher_priority)(const TallyEntry& i,const TallyEntry& j)) {
//    std::cout<<message<<std::endl;
//    TallyEntryPQ pq(tally, has_higher_priority);
//    for(auto i : pq){
//        std::cout<<"  "<<i.first<<" -> "<<i.second<<std::endl;
//    }
//}
//
//
////Return the CandidateTally: a Map of candidates (as keys) and the number of
////  votes they received, based on the unchanging Preferences (read from the
////  file) and the candidates who are currently still in the election (which changes).
////Every possible candidate should appear as a key in the resulting tally.
////Each voter should tally one vote: for their highest-ranked candidate who is
////  still in the the election.
//CandidateTally evaluate_ballot(const Preferences& preferences, const CandidateSet& candidates) {
//    CandidateTally ct;
//    for (auto i : candidates){
//        ct.put(i,0);
//    }
//    for (auto j : preferences){
//        CandidateQueue temp = j.second;
//        for (auto k : temp){
//            if (ct.has_key(k)){
//                ct[k]+=1;
//                break;
//            }
//        }
//    }
//    return ct;
//}
//
//
////Return the Set of candidates who are still in the election, based on the
////  tally of votes: compute the minimum number of votes and return a Set of
////  all candidates receiving more than that minimum; if all candidates
////  receive the same number of votes (that would be the minimum), the empty
////  Set is returned.
//CandidateSet remaining_candidates(const CandidateTally& tally) {
//    CandidateSet cs;
//    int min = 100;
//    for (auto i : tally){
//        if (i.second < min){
//            min = i.second;
//        }
//    }
//    for (auto j : tally){
//        if (j.second != min){
//            cs.insert(j.first);
//        }
//    }
//    return cs;
//}
//
//
////Prompt the user for a file, create a voter preference Map, and print it.
////Determine the Set of all the candidates in the election, from this Map.
////Repeatedly evaluate the ballot based on the candidates (still) in the
////  election, printing the vote count (tally) two ways: with the candidates
////  (a) shown alphabetically increasing and (b) shown with the vote count
////  decreasing (candidates with equal vote counts are shown alphabetically
////  increasing); from this tally, compute which candidates remain in the
////  election: all candidates receiving more than the minimum number of votes;
////  continue this process until there are less than 2 candidates.
////Print the final result: there may 1 candidate left (the winner) or 0 left
////   (no winner).
//
////gt for tally
//bool alphabetically_gt(const TallyEntry& a, const TallyEntry& b)
//{return a.first<b.first;}
//
//bool decreasing_gt(const TallyEntry& a, const TallyEntry& b){
//    if(a.second != b.second){ return a.second > b.second; }
//    else{ return alphabetically_gt(a,b); }
//}
//
//int main() {
//  try {
//      std::ifstream infile;
//      std::string file_prompt = "Enter a file storing voter preferences";
//      ics::safe_open(infile, file_prompt,"votepref1.txt");
//      Preferences p_map = read_voter_preferences(infile);
//      print_voter_preferences(p_map);
//      CandidateSet cs;
//      int index = 1;
//      for (auto i : p_map){
//          CandidateQueue temp = i.second;
//          cs.insert(temp.dequeue());
//      }
//      while(cs.size() > 1){
//          CandidateTally tally = evaluate_ballot(p_map, cs);
//          std::stringstream m_1;
//          m_1<<" Vote count on ballot #"<<index;
//          m_1<<": (alphabetical ordering of) remaining candidates = ";
//          m_1<<cs;
//          print_tally(m_1.str(),tally,alphabetically_gt);
//          std::cout<<std::endl;
//
//          std::stringstream m_2;
//          m_2<<"Vote count on ballot #"<<index;
//          m_2<<": (numerical ordering of) remaining candidates = ";
//          m_2<<cs;
//          print_tally(m_2.str(),tally,decreasing_gt);
//          std::cout<<std::endl;
//
//          cs = remaining_candidates(tally);
//          ++index;
//      }
//      if(cs.size() == 0){
//          std::cout<<"No identifiable unique winner: election is tie among the candidates who remain on the last ballot result"<<std::endl;
//      }
//      else{
//          std::string w;
//          for(auto item : cs){
//              w = item;
//              break;
//          }
//          std::cout<<"Winner is "<<w<<std::endl;
//      }
//
//      infile.close();
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//  return 0;
//}
