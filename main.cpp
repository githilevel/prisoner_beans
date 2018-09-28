#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "game.h"

void playgame(int pn, int bn, vector<int> picked);

int main(int argc, char** argv)
{
	int minargc = 3;
	if (argc >= minargc) {
		int pn, bn;
		pn = atoi(argv[1]);
		bn = atoi(argv[2]);

		cout << "囚犯：" << pn << "\t豆子：" << bn << endl;

		vector<int> picked;
		
		if (argc > minargc) {
			cout<<"前置：";
			for(int i = minargc; i < argc; i++){
				int num = atoi(argv[i]);
				picked.push_back(num);
				cout<<num<<' ';
			}
			cout<<endl;
		}

		playgame(pn, bn, picked);
	}

	return 0;
}

using Games = vector<Game>;
Games next_round(const Game& game, int& count);
void fliter(int& maxscore, int idx, Games& games, const Game& game);

void playgame(int pn, int bn, vector<int> picked)
{
	Game game = {pn, bn};

	for(auto& x : picked){
		game.pick_beans(x);
	}

	int all_count = 0;
	auto games = next_round(game, all_count);

	cout<<"遍历"<<all_count<<"种可能性，筛选出最佳方案："<<endl;
	for(auto& game:games){
		game.print_result();
		cout<<endl;
	}
	cout<<"共"<<games.size()<<"种"<<endl;
}

Games next_round(const Game& game, int& count)
{
	int pmin, pmax;
	game.pick_range(pmin, pmax);

	Games games;
	int maxscore = 0;
	int idx = game.cur_idx() + 1;

	for (int k = pmin; k <= pmax; k++){
		Game g = game;
		if (g.pick_beans(k)){
			count++;
			fliter(maxscore, idx, games, g);
		}else{
			auto subgames = next_round(g, count);
			for_each(subgames.begin(), subgames.end(), [&](const Game& sg){fliter(maxscore, idx, games, sg);});
		}
	}

	return games;
}

void fliter(int& maxscore, int idx, Games& games, const Game& game)
{
	auto score = game.result_score(idx);
	if (score > maxscore) {
		maxscore = score;
		games = {game};
	}else if(score == maxscore){
		games.push_back(move(game));
	}
}
