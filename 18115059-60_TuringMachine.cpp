//Below is the code for Turing Machine that accepts
// the language L = {0(1^n)0 n>=1 , {0,1}*}

#include <bits/stdc++.h>
using namespace std;

int tapehead = 1;
string state = "A";
vector<char> tape;

void info(){
	cout<<"This is a Turing Machine Simulator.\n\nThe language used for the simulator is 01n0 for n>=0 .\n\n";
	cout<<"This turing machine has 5 states. ";
	cout<<"Each state is described below-\n\n";
	cout<<"q0 0(q1 X R) 1(q3 1 R) B(q3 B R)\n";
	cout<<"q1 0(q2 X R) 1(q1 Y R) B(q3 B R)\n";
	cout<<"q2 0(q3 0 R) 1(q3 1 R) B(q4 B R)\n";
	cout<<"q3 REJECT\nq4 ACCEPT\n\n";	
}

void transitionTable(){
	cout<<"The Transition Table for the Turing Machine for the given grammar is given below-\n\n";
	vector<vector<string> > table(6,vector<string> (6,"- , - , -"));
	table[0][0]="Input-->";table[0][1]="    0    ";table[0][2]="    1   ";table[0][3]="     X    ";
	table[0][4]="    Y    ";table[0][5]="    B    ";
	table[1][0]="q0----->";table[2][0]="q1----->";table[3][0]="q2----->";
	table[4][0]="q3----->";table[5][0]="q4----->";
	table[1][1]="q1, X , R";table[1][2]="q3, 1 , R";table[1][5]="q3, B , R";
	table[2][1]="q2, X , R";table[2][2]="q1, Y , R";table[2][5]="q3, B , R";
	table[3][1]="q3, 0 , R";table[3][2]="q3, 1 , R";table[3][5]="q4, B , R";
	
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			cout<<table[i][j]<<"      ";
		}
		if(i==0) cout<<"\n";
		cout<<"\n";
	}
}

//The function for each transition
bool action(char input_char, char replace_with, char move, string new_state)
{
    if (tape[tapehead] == input_char)
    {
        tape[tapehead] = replace_with;
        state = new_state;
            if (move == 'L')
            {
                tapehead -= 1;
            }
            else
            {
                tapehead += 1;
            }

            return true;

    }
    return false;
}

int main()
{
	info();
	transitionTable();
    int t; //number of testcases
    cout<<"\nEnter total number of strings to be checked ";
    cin>>t;

    while(t--)
    {
        string str; //input string
        cout<<"\nEnter String ";
        cin>>str;

        int length = str.length() + 2; //for tape length
        tape.resize(length,'_');

        //writing input string on tape
        for(int i=1; i<=str.length(); i++)
        {
            tape[i] = str[i-1];
        }

        //assigning variables for requisite characters
        char zero = '0', one = '1', X='X', Y='Y', blank='_', R='R', L='L';

        int oldtapehead = -1;
        bool accept = false;

        //Running the turing machine
        while(oldtapehead != tapehead)
        {
            oldtapehead = tapehead;

            //Printing current state
            cout<<"The tape looks like ";
            for(int c=0; c<tape.size(); c++)
            {
                cout<<tape[c]<<" , ";
            }
            cout<<"with tapehead at index "<<tapehead<<" on state "<<state<<endl;

            //Transitioning to ubsequent state according to the language
            if(state=="A")
            {
                if (action(zero, X, R, "B"))    //acceptable transition to next state
                    continue;
                else if (action(one,one,R,"REJECT") || action(blank, blank,R,"REJECT")) //transition to reject state
                    break;
            }
            else if (state == "B")
            {
                if (action(one, Y, R, "B") || action(zero, X, R, "C")) //acceptable transition to next state
                    continue;
                else if (action(blank, blank,R,"REJECT")) //transition to reject state
                    break;
            }
            else if (state == "C")
            {
                if (action(blank, blank, R, "ACCEPT")) //acceptable transition to next state
                    continue;
                else if (action(one,one,R,"REJECT") || action(zero,zero,R,"REJECT")) //transition to reject state
                    break;
            }
            else
                accept = true; //when in ACCEPT state
        }


        if (accept)
            cout<<endl<<"String accepted by the language L = {0(1^n)0 n>=1 , {0,1}*}"<<endl;
        else
            cout<<endl<<"String not accepted by the language L = {0(1^n)0 n>=1 , {0,1}*}"<<endl;

        //Resetting the variables for the next string
        tapehead = 1;
        state = "A";
        tape.clear();

    }
    
   	

    return 0;
}
