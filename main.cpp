#include "common.h"
#include "parser.h"
int main(int argc, char** argv)
{
    int index = 1;
    string file;
    string input_str;
    bool if_verbose = false;
    if (argc < 2)
    {
        printf("error amount of param , usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
        return 0;
    }
    if (!strcmp(argv[index], "--help") || !strcmp(argv[index], "-h")|| !strcmp(argv[index], "--h"))
    {
        printf("usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
        return 0;
    }
    if (!strcmp(argv[index], "-v") || !strcmp(argv[index], "-verbose"))
    {
        if_verbose = true;
        index++;
    }
    if (index >= argc)
    {
        printf("no file, usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
        return 0;
    }
    file = argv[index];
    if(file.substr(file.size()-3,3)!=".tm")
        {printf("wrong file kind\n");return 0;}
    fstream fp;
    fp.open(file);
    if (!fp)
    {
        printf("wrong filepath,file cannot find\n");
        return 0;
    }
    fp.close();
    index++;
    if (index >= argc)
    {
        printf("no input , usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
        return 0;
    }
    input_str = argv[index];
    tme turing_machine;
    //fprintf(stderr, "====================ERROR=====================\n");
    turing_machine.verbose = if_verbose;
    turing_machine.parse_code(file);
    turing_machine.tm_run(input_str);
    //cout<<file;
    //cout<<input_str;
    //cout<<if_verbose;
    return 0;




}
