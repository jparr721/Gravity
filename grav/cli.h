#ifndef CLI_H_
#define CLI_H_

struct program {
  char* name;
  int soft_limit;
  int hard_limit;
  char** flags;
};

void parse_args(int argc, char** argv, struct program* p);
void show_usage();

#endif // CLI_H_
