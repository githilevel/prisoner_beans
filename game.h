#pragma once

class Game
{
public:
	Game(int pn, int bn)
		:prinum(pn), beantotal(bn), beannum(bn), curmin(bn), curmax(0){}

	using Result = vector<int>;

	bool pick_beans(int bn)
	{
		if (cur_idx() < prinum and bn <= beannum){
			vecpick.push_back(bn);
			beannum -= bn;
			curmin = min(curmin, bn);
			curmax = max(curmax, bn);

			if (cur_idx() == prinum) {
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

	int cur_idx() const
	{
		return vecpick.size();
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

	int result_score(int idx) const
	{
		int bn = vecpick[idx - 1];
		if (bn == curmin or bn == curmax) {
			return result.size() - 1;
		}else{
			return result.size() + prinum;
		}
	}

	void print_result() const
	{
		cout<<"豆子"<<beantotal - beannum<<"个：";
		for(int x:vecpick){
			cout<<x<<"\t";
		}

		cout<<endl<<"死亡"<<result.size()<<"人：";
		for(int x:result){
			cout<<x<<"\t";
		}
		cout<<endl;
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