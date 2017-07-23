#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
	
char inputChar()
{
	//chars will hold all values for which we want to randomize (in ascii)
	/* uncomment this block for more randomness AKA a-z lower case and some extras.. don't forget to comment out the chars array below.
	int chars[] = {0, 32, 40, 41, 91, 93, 97, 98, 99,100,  
					101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
					111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 
					121, 122, 123, 124, 125};
	*/		
	//this list will randomly generate only the values under test in testme()
	int chars[] = {0, 32, 40, 41, 91, 93, 97, 101, 114, 115, 116, 120, 122, 123,  125};			
	int size =  sizeof(chars) / sizeof(int);  //get the number of elements in chars
	int rando =  rand() % size;  //generate a random number not to exceed the size chars
	char r = chars[rando];  //reference random number to our chars array
    return r;
}

//Referenced https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
char *inputString()
{
	int i;
    char r = rand() % 10 + 5; // r is the size of the string. I chose 5 as the floor because that is the average english word length
	char *word = malloc(sizeof(char) * (r+1));
	for (i= 0; i< r; i++)
	{
		char input =  inputChar();
		word[i] = input;
	}
    return word;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
