#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>                           //I used std::numeric_limits<int>::max()
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"


typedef ics::ArrayQueue<std::string>         WordQueue;
typedef ics::ArraySet<std::string>           FollowSet;
typedef ics::pair<WordQueue,FollowSet>       CorpusEntry;
typedef ics::ArrayPriorityQueue<CorpusEntry> CorpusPQ;     //Convenient to supply gt at construction
typedef ics::ArrayMap<WordQueue,FollowSet>   Corpus;


//Return a random word in the words set (use in produce_text)
std::string random_in_set(const FollowSet& words) {
  int index = ics::rand_range(1, words.size());
  int i = 0;
  for (const std::string& s : words)
    if (++i == index)
      return s;
  return "?";
}


//Read an open file of lines of words (separated by spaces) and return a
//  Corpus (Map) of each sequence (Queue) of os (Order-Statistic) words
//  associated with the Set of all words that follow them somewhere in the
//  file.
Corpus read_corpus(int os, std::ifstream &file) {
    Corpus words;
    std::string line;
    std::vector<std::string> v;
    while(std::getline(file,line)){
        auto line_v = ics::split(line, " ");
         for(auto i : line_v){
             v.push_back(i);
         }
    }
    for(int i = 0; i < v.size() - os; ++i){
        WordQueue wq;
        for(int j = i; j < i + os; ++j){
            wq.enqueue(v[j]);
        }
        words[wq].insert(v[i+os]);
    }
    return words;
}


//Print "Corpus" and all entries in the Corpus, in lexical alphabetical order
//  (with the minimum and maximum set sizes at the end).
//Use a "can be followed by any of" to separate the key word from the Set of words
//  that can follow it.

//One queue is lexically greater than another, if its first value is smaller; or if
//  its first value is the same and its second value is smaller; or if its first
//  and second values are the same and its third value is smaller...
//If any of its values is greater than the corresponding value in the other queue,
//  the first queue is not greater.
//Note that the queues sizes are the same: each stores Order-Statistic words
//Important: Use iterators for examining the queue values: DO NOT CALL DEQUEUE.

bool queue_gt(const CorpusEntry& a, const CorpusEntry& b) {
    auto ap = a.first.begin();
    auto bp = b.first.begin();
    int i = 0;
    while(i < a.first.size()){
        ++i;
        if (*ap == *bp){
            ap++;
            bp++;
        }
        else{return *ap < *bp;}
    }
}

void print_corpus(const Corpus& corpus) {
    std::cout<<"\n"<<"Corpus contains "<<corpus.size()<<" Entry pairs"<<std::endl;
    CorpusPQ pq(corpus, queue_gt);
    int max = 0;
    int min = corpus.size();
    for(auto i : pq){
        std::cout<<"  "<<i.first<<" -> "<<i.second<<std::endl;
        if (i.second.size() > max){max = i.second.size();}
        if (i.second.size() < min){min = i.second.size();}
    }
    std::cout<<"Corpus contains "<<corpus.size()<<" Entry pairs"<<std::endl;
    std::cout<<"min-max = "<<min<<"-"<<max<<std::endl<<"\n";
}


//Return a Queue of words, starting with those in start and including count more
//  randomly selected words using corpus to decide which word comes next.
//If there is no word that follows the previous ones, put "None" into the queue
//  and return immediately this list (whose size is <= start.size() + count).
WordQueue produce_text(const Corpus& corpus, const WordQueue& start, int count) {
    WordQueue wq;
    wq.enqueue_all(start);
    WordQueue temp;
    temp.enqueue_all(start);
    for(int i = 0; i < count; ++i){
        if(!corpus.has_key(temp)){
            wq.enqueue("None");
            break;
        }
        else{
            auto next = random_in_set(corpus[temp]);
//            WordQueue temp;
//            temp.enqueue_all(start);
            temp.enqueue(next);
            temp.dequeue();
            wq.enqueue(next);
        }
    }
    return wq;
}



//Prompt the user for (a) the order statistic and (b) the file storing the text.
//Read the text as a Corpus and print it appropriately.
//Prompt the user for order statistic words from the text.
//Prompt the user for number of random words to generate
//Call the above functions to solve the problem, and print the appropriate information
int main() {
  try {
      // Didn't notice there was a prompt_int function ....... and wrote the whole thing..
      int statistic = ics::prompt_int("Enter an order statistic", 2);
      std::ifstream infile;
      std::string file_prompt="Enter a file storing text to process";
      ics::safe_open(infile, file_prompt,"wginput1.txt");
      Corpus corpus = read_corpus(statistic,infile);
      print_corpus(corpus);
      infile.close();
      std::cout<<"Enter "<<statistic<<" words for prefix to start"<<std::endl;
      WordQueue q;
      for(int i = 0; i < statistic; ++i){
          std::string input;
          std::cout<<"Enter word "<<i+1<<":";
          std::cin>>input;
          q.enqueue(input);
      }
      int num;
      std::cout<<"Enter # of words for generation: ";
      std::cin>>num;
      WordQueue wq = produce_text(corpus,q,num);
      std::cout<<"Random text = "<<wq<<std::endl;


  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
