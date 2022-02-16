#pragma once
#include"common.h"
struct delta_function
{
    string newstate;
    string oldstate;
    string newchar;
    string oldchar;
    string direction;
};
//struct delta_function
//{
//    string newstate;
//    string oldstate;
//    string newchar;
//    string oldchar;
//    string direction;
//};
class tme//turing machine
{
public:
    vector<string> state_set;//Q
    vector<char> input_char;//S
    vector<char> tape_char;//G
    string original_state;//q0
    char blank;//B
    vector<string> accept_state_set;//F
    int ntape;//amonut of n
    vector<delta_function> transition_func;//delta func
    bool verbose;
    char invalidchar;
    int linenumber;
    /*tme(vector<string>q,vector<char> s,vector<char> g,string q0, char blank, vector<string> f,int ntape, vector<delta_function>func)
    {
        state_set=q;
        input_char=s;
        tape_char=g;
        original_state=q0;
        blank=blank;
        accept_state_set=f;
        ntape=ntape;
        transition_func=func;
    }*/
    int parse_code(string tmfile);
    int splitAload(string line, char mode);
    int tm_run(string input);
    int find(int index,vector<pair<int, char>>p);
    int find_oldstate(string state, string tape_n_char);//旧状态和n条纸带上现在的字符组成的字符串  《=》
    bool is_valid(string input);//输入的字符串是否合法
    int linefomula(string s, int line, int nstart);
};

void error_handling(int kind);