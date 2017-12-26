#include "patricia.h"

int main(){
	std::vector<std::string> words{"roma", "romano", "romance", "romantico", "rombo", };
	PatriciaTree t;
	for(auto & i : words){
		t.Insert(i);
	}
	t.PrintSearch("ro");
	t.PrintSearch("rom");
	t.PrintSearch("roma");
	int n{};
	std::cin >> n;
	return 0;
}
