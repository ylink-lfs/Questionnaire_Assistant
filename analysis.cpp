#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;
using std::isspace;

class problem
{
private:
	vector<int> option_count;
	vector<double> option_rate;
public:
	problem(const int n = 0) : option_count(n)
	{
		for (auto it = option_count.begin(); it < option_count.end(); it++)
			*it = 0;
	}
	void add_option(const char ch) 
	{ 
		option_count[toupper(ch) - 'A']++; 
	}
	int return_current_count(const char ch) const
	{
		return option_count[toupper(ch) - 'A'];
	}
	void resize_option(const int n)
	{
		option_count.resize(n);
		option_rate.resize(n);
	}
	void count_rate()
	{
		int tot_member = 0;
		for (auto it = option_count.begin(); it < option_count.end(); it++)
		{
			tot_member += *it;
		}
		for (auto it = option_rate.begin(); it < option_rate.end(); it++)
		{
			*it = double(option_count[it - option_rate.begin()]) / tot_member;
		}
	}
	int how_many_option() const { return option_count.size(); }
	const double operator[](int i) { return option_rate[i]; }
};

int main(void)
{
	ifstream ist("in.txt", std::ios_base::in);

	string analyst_name;
	getline(ist, analyst_name);

	int member_count;
	ist >> member_count;
	ist.get();

	problem count_board[11];
	count_board[0].resize_option(2);
	count_board[1].resize_option(4);
	count_board[2].resize_option(4);
	count_board[3].resize_option(3);
	count_board[4].resize_option(2);
	count_board[5].resize_option(4);
	count_board[6].resize_option(4);
	count_board[7].resize_option(2);
	count_board[8].resize_option(2);
	count_board[9].resize_option(6);
	count_board[10].resize_option(5);

	for (int i = 0; i < member_count; i++)
	{
		string option_tmp_store;
		getline(ist, option_tmp_store);
		for (auto it = option_tmp_store.begin(); it < option_tmp_store.end() && !isspace(*it); it++)
		{
			count_board[it - option_tmp_store.begin()].add_option(*it);
		}
	}
	for (int i = 0; i < 11; i++)
		count_board[i].count_rate();

	ofstream os(analyst_name + "_result.txt");
	os.setf(std::ios_base::fixed);
	os.precision(5);
	os << "Total member: " << member_count << endl;
	for (int i = 0; i < 11; i++)
	{
		os << "Problem " << i + 1 << ":\n";
		for (int j = 0; j < count_board[i].how_many_option(); j++)
		{
			char cur_opt = 'A' + j;
			
			os << cur_opt << ": " << count_board[i][j] << '\t';
		}
		os << endl;
	}
	ist.close();
	os.close();
	return 0;
}