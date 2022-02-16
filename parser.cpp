#include"parser.h"
#include"common.h"
int rr()
{
    int a = 0;
    return 0;
}

int tme::find_oldstate(string state, string tape_n_char)
{
    for (unsigned int it = 0; it <transition_func.size(); it++)
    {
        if (transition_func[it].oldstate == state && transition_func[it].oldchar == tape_n_char)
            return it;
    }
    return -1;
}
int stateexit(vector<string>p, string q)
{
    int flag = 0;
    for (int k = 0; k < p.size(); k++)
    {
        if (p[k] == q)
        {
            flag = 1;
            break;
        }
    }
    return flag;



}
int charexit(vector<char>p, char q)
{
    int flag = 0;
    for (int k = 0; k < p.size(); k++)
    {
        if (p[k] == q)
        {
            flag = 1;
            break;
        }
    }
    return flag;



}
int tme::splitAload(string line, char mode)
{
    int isize = 1;
    isize = line.size();
    /*if (mode != 'W'&&mode!='q')
    {
        for (int i = 0; line[i] != '}'; i++)
        {
            isize++;
        }
    }*/
    //cout << isize << endl;
    switch (mode)
    {
    case 'Q':
    {
        //vector<string> state_set;//Q
        int lb = 6;
        int rb = 0;
        int len = 0;
        for (unsigned int i = 6; i < isize; i++)
        {
            if (line[i] == ',' || line[i] == '}')
            {
                len = i - lb;
                state_set.push_back(line.substr(lb, len));
                lb = i + 1;
            }
        }
        break;
    }
    case 'S':
    {
        vector<char> illegalchar{ ' ',',',';','{','}','*' };
        int oldi = 5;
        for (int i = 6; i < isize; i++)
        {
            if (line[i] == ',' || line[i] == '}')
            {
                if (i - oldi > 2)
                {
                    string m = line.substr(oldi + 1, i - oldi - 1);
                    if (verbose)
                    {
                    
                    fprintf(stderr, "syntax error : line %d : %s ,the %s must be of typechar!\n", linenumber, line.c_str(), m.c_str());
                    exit(-1);
                     }
                    fprintf(stderr, "syntax error\n");
                    exit(-1);
                }
                /*if (i - oldi > 2 )
                {
                    string m = line.substr(oldi + 1, i - oldi);
                    fprintf(stderr, "syntax error : line %d : %s ,%s must belonged to charkind!\n", linenumber, line.c_str(), m.c_str());
                    exit(-1);
                }*/
                oldi = i;
                if (charexit(illegalchar, line[i - 1]))
                {
                    if (verbose)
                    {
                        fprintf(stderr, "syntax error : line %d : %s ,the %c illegal!\n", linenumber, line.c_str(), line[i - 1]);
                        exit(-1);
                    }
                    fprintf(stderr, "syntax error\n");
                    exit(-1);
                }
                input_char.push_back(line[i - 1]);
            }
        }
        break;
    }
    case 'G':
    {
        vector<char> illegalchar{ ' ',',',';','{','}','*' };
        int oldi = 5;
        for (int i = 6; i < isize; i++)
        {
            if (line[i] == ',' || line[i] == '}')
            {
                if (i - oldi > 2 )
                {
                    string m = line.substr(oldi + 1, i - oldi-1);
                    if (verbose)
                    {
                        fprintf(stderr, "syntax error : line %d : %s ,the %s must be of typechar!\n", linenumber, line.c_str(), m.c_str());
                        exit(-1);
                    }
                    fprintf(stderr, "syntax error\n");
                    exit(-1);
                }
                /*if (i - oldi > 2)
                {
                    string m = line.substr(oldi + 1, i - oldi);
                    fprintf(stderr, "syntax error : line %d : %s ,the %s must belonged to charkind!\n", linenumber, line.c_str(), m.c_str());
                    exit(-1);
                }*/
                oldi = i;
                if (charexit(illegalchar, line[i - 1]))
                {
                    if (verbose)
                    {
                        fprintf(stderr, "syntax error : line %d : %s ,the %c illegal!\n", linenumber, line.c_str(), line[i - 1]);
                        exit(-1);
                    }
                    fprintf(stderr, "syntax error\n");
                    exit(-1);
                }
                tape_char.push_back(line[i - 1]);
            }
        }
        break;


    }
    case 'q':
    {
        isize = line.size();
        original_state = line.substr(6, isize - 6);
        break;
    }
    case 'F':
    {

        int lb = 6;
        int rb = 0;
        int len = 0;
        for (int i = 6; i < isize; i++)
        {
            if (line[i] == ',' || line[i] == '}')
            {
                len = i - lb;
                string m = line.substr(lb, len);
                accept_state_set.push_back(m);
                lb = i + 1;
                int flag = 0;
                for (int k = 0; k < state_set.size(); k++)
                {
                    if (state_set[k] == m)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    if (verbose)
                    {
                        fprintf(stderr, "syntax error : line %d : %s , state '%s' dont exit in state set!", linenumber, line.c_str(), m.c_str());
                        exit(-1);
                    }
                    fprintf(stderr, "syntax error\n");
                    exit(-1);
                }
            }
        }
        break;
    }
    case 'W':
    {
        int ifcomment = 0;
        int loac = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ';')
            {
                ifcomment = 1;
                loac = i;
                break;
            }
        }
        string line2=line;
        if (ifcomment)
        {
            line2 = line.substr(0, loac-1);
        }
        int blank_num = 0;//cp_ab a_ aa rr cp_aba
        for (int i = 0; i < line2.size(); i++)
        {
            if (line2[i] == ' ')
                blank_num++;
        }
        if (blank_num != 4)
        {
            if (verbose)
            {
                fprintf(stderr, "syntax error : line %d : %s,transfunc format illegal,you might pay attention to blank format.", linenumber, line.c_str());
                exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        struct delta_function node;
        istringstream is(line2);
        is >> node.oldstate >> node.oldchar >> node.newchar >> node.direction >> node.newstate;
        int flag = stateexit(state_set, node.oldstate);
        int ream = stateexit(state_set, node.newstate);
        if (flag == 0)
        {
            if (verbose)
            {
                fprintf(stderr, "syntax error : line %d : %s,oldstate '%s'in this transfunc dont exit in state set!", linenumber, line.c_str(), node.oldstate.c_str());
                exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        if (ream == 0)
        {
            if(verbose)
            {
            fprintf(stderr, "syntax error : line %d : %s,newstate '%s'in this transfunc dont exit in state set!", linenumber, line.c_str(), node.newstate.c_str());
            exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        if (node.newchar.size() != ntape)
        {
            if (verbose)
            {
                fprintf(stderr, "syntax error : line %d : %s,the amount of newchar '%s' unmatched with ntape", linenumber, line.c_str(), node.newchar.c_str());
                exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        if (node.oldchar.size() != ntape)
        {
            if (verbose)
            {
                fprintf(stderr, "syntax error : line %d : %s,the amount of oldchar '%s' unmatched with ntape", linenumber, line.c_str(), node.oldchar.c_str());
                exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        if (node.direction.size() != ntape)
        {
            if (verbose)
            {
                fprintf(stderr, "syntax error : line %d : %s,the amount of direction set '%s' unmatched with ntape", linenumber, line.c_str(), node.direction.c_str());
                exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        for (int i = 0; i < ntape; i++)
        {
            int flag = charexit(tape_char, node.oldchar[i]);
            if(flag==0)
            {
                if(verbose)
                { 
                    fprintf(stderr, "syntax error : line %d : %s,oldchar '%c' dont exit in tapechar set!", linenumber, line.c_str(), node.oldchar[i]);
                   exit(-1); 
                }
                fprintf(stderr, "syntax error\n");
                exit(-1);
            }
        }
        for (int i = 0; i < ntape; i++)
        {
            int flag = charexit(tape_char, node.newchar[i]);
            if (flag == 0)
            { 
                if (verbose)
                {
                    fprintf(stderr, "syntax error : line %d : %s,newchar '%c' dont exit in tapechar set!", linenumber, line.c_str(), node.newchar[i]);
                    exit(-1);
                }
                fprintf(stderr, "syntax error\n");
                exit(-1);
            }
        }
        for (int i = 0; i < ntape; i++)
        {
            vector<char>k{'l','r','*'};
            int flag = charexit(k, node.direction[i]);
            if (flag == 0)
            {
                if (verbose)
                {
                    fprintf(stderr, "syntax error : line %d : %s,direction '%s' dont exit in direction_set!", linenumber, line.c_str(), node.newstate.c_str());
                    exit(-1);
                }
                fprintf(stderr, "syntax error\n");
                exit(-1);
            }
        }
        transition_func.push_back(node);
        break;
    }

    }
    return 0;




}
int tme::linefomula(string s,int line,int nstart)//#G = {0,1,_,T,r,u,e,F,a,l,s}
{
    int sn=0;
    if(nstart==1)
        sn = nstart;
    if (s.substr(2+sn,3) != " = ")
    {
        if (sn == 0)
        {
            if (verbose)
            {
                fprintf(stderr, "syntax error : line %d : %s,illegal format,the three characters after %c must be ' = ' \n", line, s.c_str(), s[1]);
                exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        else
        {
            if (verbose)
            {
                fprintf(stderr, "syntax error : line %d : %s,illegal format,the three characters after %c%c must be ' = ' \n", line, s.c_str(), s[1], s[2]);
                exit(-1);
            }
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
    }
    if (nstart == 2|| nstart == 1)
        return 0;
    if(s[5]!='{')
    {
        if (verbose)
        {
            fprintf(stderr, "syntax error : line %d : %s,missing left '{'\n", line, s.c_str());
            exit(-1);
        }
        fprintf(stderr, "syntax error\n");
        exit(-1);
    }
    int size = s.size();
    if (s[size-1] != '}')
    {
        if (verbose)
        {
            fprintf(stderr, "syntax error : line %d : %s,missing right '}',you may pat attention that no symbol especially ' 'after } \n", line, s.c_str());
            exit(-1);
        }
        fprintf(stderr, "syntax error\n");
        exit(-1);
    }
    return 0;
}
int tme::parse_code(string tmfile)
{
    fstream file;
    file.open(tmfile);
    string temp;
    linenumber = 0;
    while (getline(file, temp))
    {
        linenumber++;
   //     cout << linenumber<<endl;
        if (temp[0] == ';')
        {
   //         cout << "comment";
        }
        else if (temp=="")
        {
   //         cout << "blank";
        }
        else if (temp[0] == '#')
        {
            switch (temp[1]) {
            case'Q':
            {
                linefomula(temp, linenumber,0);
                splitAload(temp, temp[1]);
                break;
            }
            case 'S':
            {
                linefomula(temp, linenumber, 0);
                splitAload(temp, temp[1]);
                break;
            }
            case'G':
            {
                linefomula(temp, linenumber, 0);
                splitAload(temp, temp[1]);
                break;

            }
            case'q':
            {
                if (temp[2] != '0')
                {
                    if (verbose)
                    {
                        fprintf(stderr, "syntax error : line %d : %s , the symbol must be q0!\n", linenumber, temp.c_str());
                        exit(-1);
                    }
                    fprintf(stderr, "syntax error\n");
                    exit(-1);
                }
                linefomula(temp, linenumber, 1);
                splitAload(temp, temp[1]);
                break;

            }
            case'B':
            {
                linefomula(temp, linenumber, 2);
                blank = '_';
                break;
            }
            case'F':
            {
                linefomula(temp, linenumber, 0);
                splitAload(temp, temp[1]);
                break;
            }
            case'N':
            {
                int size = temp.size();
                string sub = temp.substr(5, size - 5);
                //const char* p = sub.data();
                ntape = atoi(sub.c_str());
                if (ntape == 0)
                {
                    if (verbose)
                    {
                        fprintf(stderr, "syntax error : line %d : %s , the ntape must be a number greater than 0 !\n", linenumber, temp.c_str());
                        exit(-1);
                    }
                    fprintf(stderr, "syntax error\n");
                    exit(-1);
                }
                break;
            }
            default:
            {
                if (verbose)
                {
                    fprintf(stderr, "syntax error: line %d : unknown symbol '%c'\n", linenumber, temp[1]);
                    exit(-1);
                }
                fprintf(stderr, "syntax error\n");
                exit(-1);
                break;
            }
            }
        }
        else
        {
            splitAload(temp, 'W');
        }


    }
    file.close();
    return 0;
}