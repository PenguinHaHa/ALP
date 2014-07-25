#include<stdio.h>
#include<getopt.h>
#include<string.h>

const char* const short_options = "hc:";
const struct option long_options[] = {
  {"help", 0, NULL, 'h'},
  {"case", 1, NULL, 'c'},
  {NULL, 0, NULL, 0}
};

void print_usage(void)
{
  printf("Advanced Linux Programming\n");
  printf("  -h  --help           Display usage information.\n");
  printf("  -c  --case testcase  choose test case.\n");
}

int main(int argc, char *argv[])
{
  int option;

  do {
    option = getopt_long(argc, argv, short_options, long_options, NULL);
    switch (option)
    {
      case 'h':
        print_usage();

      case 'c':
        printf("test case %s\n", optarg);
        break;

      case -1:
        break;

      default:
        printf("Unsupported option %c\n", option);
        break;

    }
  } while (option != -1);

  return 0;
}

void choose_testcase(char *optarg)
{
  if(strcmp(optarg, "standardio"))
  {
    printf("Run Standard IO test case\n");
  }
  else
  {
    printf("Undefined test case %s\n", optarg);
  }
}
