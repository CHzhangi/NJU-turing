#include"parser.h"
int tme::find(int index, vector<pair<int, char>>p)
{
    for (unsigned int i = 0; i < p.size(); i++)
    {
        if (p[i].first == index)
            return i;
    }
    return -22222;
    //cout << "find error" << endl;
}
bool tme::is_valid(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        int flag = 0;
        for (int k = 0; k < input_char.size(); k++)
        {
            if (input[i] == input_char[k])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            invalidchar = input[i];
            return false;
        }
    }

    return true;




}
int tme::tm_run(string input)
{
    if (!is_valid(input))
    {
        if (verbose)
        {
            fprintf(stderr, "error: '%c' was not declared in the set of input symbols\nInput: %s\n=====================END======================\n", invalidchar, input.c_str());
            exit(-1);
        }
        else
        {
            fprintf(stderr, "illegal input\n");
            exit(-1);
        }
    }
    vector < vector<pair<int, char>>>tape;
    int head[100]; ;//head ��¼��ǰʱ�̵�index�������ʱ����pair��vector�е�begin.index�Ĳ�ֵ����ո�
    for (int i = 0; i < ntape; i++)//��ֽ�����г�ʼ��
    {
        head[i] = 0;
        if (i == 0)
        {
            vector<pair<int, char>>tape_index;//<index,symbol>
            tape.push_back(tape_index);
            for (unsigned int j = 0; j < input.size(); j++)
            {
                pair<int, char> node(j, input[j]);
                tape[0].push_back(node);

            }
        }
        else
        {
            vector<pair<int, char>>tape_index;
            tape.push_back(tape_index);
            pair<int, char> node(0, '_');
            tape[i].push_back(node);
        }
    }
    string current_state = original_state;
    string current_n_char;
    int step = 0;
    if (verbose)
        fprintf(stdout, "====================RUN=====================\n");
    while (true)
    {
        if (verbose)
        {
            fprintf(stdout, "Step   : %d\n", step);
            for (int i = 0; i < ntape; i++)
            {
                int non_blank_start = 0;
                int non_blank_end = 0;
                for (int k = 0; k < tape[i].size(); k++)
                    if (tape[i][k].second != '_')
                    {
                        non_blank_start = k;
                        break;
                    }
                for (int k = tape[i].size() - 1; k > 0; k--)
                    if (tape[i][k].second != '_')
                    {
                        non_blank_end = k;
                        break;
                    }
                int start = non_blank_start, end = non_blank_end;
                int pair_id = find(head[i], tape[i]);
                if(pair_id==-22222)
                {
                    fprintf(stderr,"run error!");
                    exit(-1);
                }
                if (pair_id < non_blank_start)
                    start = pair_id;
                if (pair_id > non_blank_end)
                    end = pair_id;
                fprintf(stdout, "Index%d : ", i);
                for (int k = start; k <= end; k++)
                    fprintf(stdout, "%d ", abs(tape[i][k].first));
                fprintf(stdout, "\n");
                //cout << endl;
                fprintf(stdout, "Tape%d  : ", i);
                //cout << "Tape" << i << "  : ";
                for (int k = start; k <= end; k++)
                    fprintf(stdout, "%c ", tape[i][k].second);
                //cout << tape[i][k].second << " ";
                fprintf(stdout, "\n");
                fprintf(stdout, "Head%d  : ", i);
                //cout << "Head" << i << "  : ";
                int _len = pair_id - start;
                for (int i = 0; i < _len; i++)
                    fprintf(stdout, "  ");//cout << "  ";
                fprintf(stdout, "^\n");
                //cout << "^"<<endl;
            }
            fprintf(stdout, "State  : ");
            cout << current_state << endl;
            //cout << "State" << "  : " << current_state<<endl;
            fprintf(stdout, "---------------------------------------------\n");


        }
        step++;
        int non_blank_start=0, non_blank_end=0;
        for (int k = 0; k < tape[0].size(); k++)
            if (tape[0][k].second != '_')
            {
                non_blank_start = k;
                break;
            }
        for (int k = tape[0].size() - 1; k > 0; k--)
            if (tape[0][k].second != '_')
            {
                non_blank_end = k;
                break;
            }
        for (int i = 0; i < ntape; i++)
        {
            int pair_id = find(head[i], tape[i]);
            if(pair_id==-22222)
            {
                    fprintf(stderr,"run error!");
                    exit(-1);
            }   
            current_n_char += tape[i][pair_id].second;
        }
        
        for (int i = 0; i < accept_state_set.size(); i++)
        {
            if (accept_state_set[i] == current_state)
            {
                cout << "Result:";
                for (int k = non_blank_start; k <= non_blank_end; k++)
                    fprintf(stdout, "%c", tape[0][k].second);
                fprintf(stdout, "\n");
                return 0;
            }
        }
        int func_id = find_oldstate(current_state, current_n_char);
        string new_state;
        if(func_id!=-1)
            new_state = transition_func[func_id].newstate;
        else
        {
             
            fprintf(stderr, "error : cannot find state correct transfuncion of %s\n", current_state.c_str());
            exit(-1);
        }
        current_state = new_state;
        int key;
        string direction = transition_func[func_id].direction;
        string newchar = transition_func[func_id].newchar;
        current_n_char = "";
        for (int i = 0; i < ntape; i++)
        {
            int pair_id = find(head[i], tape[i]);//�ҵ���ǰ������Ӧ��ֽ����<index.char>��id
            tape[i][pair_id].second = newchar[i];//�޸Ķ��е��ַ�
            switch (direction[i])                 //���ž����ƶ�����Ҫ�ǶԱ߽�Ĳ�����head[i]���ƶ�
            {
            case'l':
            {
                if (head[i] == tape[i][0].first)
                {
                    pair<int, char>node(tape[i][0].first - 1, '_');
                    tape[i].insert(tape[i].begin(), node);
                    head[i] -= 1;
                    break;
                }
                head[i]--;
                break;
            }
            case'*':
            {
                break;
            }
            case'r':
            {
                if (head[i] == (*(tape[i].end() - 1)).first)
                {
                    pair<int, char>node((*(tape[i].end() - 1)).first + 1, '_');
                    tape[i].push_back(node);
                    head[i] += 1;
                    break;
                }
                head[i]++;
                break;
            }
            default:
                break;
            }
        }
    }
    return 0;
} 