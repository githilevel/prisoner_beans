#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void playgame(int pn, int bn);

int main(int argc, char** argv)
{
	if (argc >= 3) {
		int pn, bn;
		pn = atoi(argv[1]);
		bn = atoi(argv[2]);

		cout << "囚犯：" << pn << "\t豆子：" << bn << endl;

		playgame(pn, bn);
	}
}

class Game
{
public:
	Game(int pn, int bn)
		:prinum(pn), beantotal(bn), beannum(bn), curmin(bn), curmax(0){}

	using Result = vector<int>;

	bool pick_beans(int bn)
	{
		if (vecpick.size() < prinum and bn <= beannum){
			vecpick.push_back(bn);
			beannum -= bn;
			curmin = min(curmin, bn);
			curmax = max(curmax, bn);

			if (vecpick.size() == prinum) {
				int idx = 0;
				for (int& bn : vecpick){
					idx++;
					if (bn == curmin or bn == curmax) {
						result.push_back(idx);
					}
				}
				return true;
			}
		}
		return false;
	}

	const Result& get_result() const
	{
		return result;
	}

	void pick_range(int& pmin, int& pmax) const
	{
		auto idx = vecpick.size() + 1;
		if (idx <= 2){
			pmin = 1;
			pmax = max(curmax, (beannum + 1) / 2) - 1;
		}else if (idx == prinum) {
			if( (curmax - curmin) > 1 and beannum > curmin){
				pmin = curmin + 1;
			}else{
				pmin = curmin;
			}
			pmax = pmin;
		}else{
			pmin = min(curmin + 1, curmax - 1);
			pmax = max(curmin + 1, curmax - 1);
		}

		pmax = min(pmax, beannum);
		pmin = min(pmin, pmax);
	}

private:
	int prinum;
	int beantotal;

	vector<int> vecpick;
	int beannum;
	int curmin;
	int curmax;
	Result result;
};

void next_round(const Game& game, int& count);

void playgame(int pn, int bn)
{
	Game game = {pn, bn};

	int all_live_count = 0;

	next_round(game, all_live_count);

	cout<<all_live_count<<endl;
}

void next_round(const Game& game, int& count)
{
	int pmin, pmax;
	game.pick_range(pmin, pmax);
	for (int k = pmin; k <= pmax; k++){
		Game g = game;
		if (g.pick_beans(k)){
			count++;
		}else{
			next_round(g, count);
		}
	}
}
