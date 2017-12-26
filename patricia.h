#ifndef PATRICIATREE
#define PATRICIATREE

#include <bits/stdc++.h>

class PatriciaTree{
	struct Node{
		const std::string label;
		Node * parent;
		std::vector<Node*> Nodes;
		Node(const std::string &, Node *);
		void GetLabels(std::vector<std::string> &);
		void PrintNode(int);
		inline bool operator<(const Node & other){
			return label < other.label;
		}
		~Node();
	}root;
public:
	PatriciaTree();
	void Insert(const std::string &);
	void PrintTree();
	void PrintSearch(const std::string &);
	std::vector<std::string> Search (const std::string &);
};

PatriciaTree::Node::Node(const std::string & name, Node * p):label(name), parent(p){}
PatriciaTree::Node::~Node(){
	for(auto i : Nodes)
		delete i;
}

PatriciaTree::PatriciaTree():root("", nullptr){
}

int compare(const std::string & first, const std::string & second){
	int amount = 0;
	while(first[amount] == second[amount] && amount < std::min(first.length(), second.length())) ++amount;
	return amount;
}

void PatriciaTree::Insert(const std::string & word){
	Node * CurrentNode = &root;

	while(true){
		bool found = false;
		const int OriginalComparison = compare(CurrentNode->label, word);
		int NewComparison = 0;
		for(auto i : CurrentNode->Nodes){
			NewComparison = compare(i->label, word);
			if(NewComparison > OriginalComparison){
				found = true;
				CurrentNode = i;
				break;
			}
		}
		if(!found){
			auto itr = CurrentNode->Nodes.begin();
			for(; itr != CurrentNode->Nodes.end(); itr++)
				if((*itr)->label > word) break;
			CurrentNode->Nodes.emplace(itr, new Node(word, CurrentNode));
			return;
		}
		else if(CurrentNode->Nodes.empty() || NewComparison != CurrentNode->label.length()){
			if(CurrentNode->Nodes.empty() && CurrentNode->label.length() == word.length() && word.length() == NewComparison)
				return;
			auto NewNode = new Node(word.substr(0, NewComparison), CurrentNode->parent);

			if(CurrentNode->label < word){
				NewNode->Nodes.emplace_back(CurrentNode);
				NewNode->Nodes.emplace_back(new Node(word, NewNode));
			}
			else{
				NewNode->Nodes.emplace_back(new Node(word, NewNode));
				NewNode->Nodes.emplace_back(CurrentNode);
			}
			CurrentNode->parent->Nodes.erase(std::find(CurrentNode->parent->Nodes.begin(), CurrentNode->parent->Nodes.end(), CurrentNode));
			auto itr = CurrentNode->parent->Nodes.begin();
			for(; itr != CurrentNode->parent->Nodes.end(); itr++)
				if((*itr)->label > NewNode->label) break;
			CurrentNode->parent->Nodes.emplace(itr, NewNode);
			CurrentNode->parent = NewNode;
			return;
		}
	}
}

std::vector<std::string> PatriciaTree::Search(const std::string & word){
	Node * CurrentNode = &root;
	while(true){
		bool found = false;
		const int originalComparison = compare(CurrentNode->label, word);
		for(auto i : CurrentNode->Nodes){
			if(compare(i->label, word) > originalComparison){
				found = true;
				CurrentNode = i;
				break;
			}
		}
		if(!found){
			std::vector<std::string> val;
			if(CurrentNode == &root) return val;
			CurrentNode->GetLabels(val);
			if(CurrentNode->Nodes.empty()) val.emplace_back(CurrentNode->label);
			return val;
		}
	}
}

void PatriciaTree::Node::GetLabels(std::vector<std::string> & vec){
	for(auto i : Nodes){
		if(i->Nodes.empty())
			vec.emplace_back(i->label);
		else
			i->GetLabels(vec);
	}
}

void PatriciaTree::Node::PrintNode(int level){
	if(Nodes.empty())
		std::cout << std::string(level, '-') << label << std::endl;
	else
		std::cout << std::string(level, '*') << label << std::endl;
	for(auto &i : Nodes)
		i->PrintNode(level + 1);
}

void PatriciaTree::PrintSearch(const std::string & word){
	auto list = Search(word);
	std::cout << "Buscar  " << word <<"\n";
	for(auto & i : list){
		std::cout << i.c_str() << ' ';
	}
	std::cout << std::endl;
}

#endif //PATRICIATREE
