#include<iostream>
#include<vector>

using namespace std;
enum tokenenum
{
	token_key, token_sym, token_str_cnt, token_cnt, token_ind, token_char_cnt
};
struct token_type {
	tokenenum t_type;
	int t_pos;
};

bool Syntax(vector<token_type> t);
