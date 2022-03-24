#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <time.h>
using namespace std;

class LFSR_7{
    public:

    int* taps;
    int numTaps=0;
    int last;
    int numShifts;
    bool selfShrinking = false;
    bitset<7> fill;
    
    // Constructors
    LFSR_7(int n){
        numShifts = n;
    }

    LFSR_7(int n, string t){
        numShifts = n;
        if(n>2) selfShrinking = true;
        setTaps(t);
    }

    // Setter Methods 

    void setTaps(string input){

        // Set Global Vars
        last = input.length()-1;
        numTaps = 0;

        // Next, find out how many taps we are using
        for(int i = 0; i<=last; i++) if(input[i]=='1') numTaps++;

        // Next, dynamically create array of tap locations
        taps = new int[numTaps];

        // Next, put the value of the tap locations in the array
        int spot = 0;
        for(int i = 0; i<=last; i++)  { 
            if(input[i]=='1') {
                taps[spot] = last-i; 
                spot++;
            }
        }

    }

    void setFill(int num){
        fill = bitset<7>(num);
    }

    bool shiftAndApplyTaps(){

        bool val;

        for(int t =0; t<numShifts; t++){
            val = fill.test(taps[0]) ^ fill.test(taps[1]);  // XOR the first 2 taps
            for(int i =2; i<numTaps; i++) val ^= fill.test(taps[i]); // then XOR every tap
            fill = fill << 1;   // shift by 1
            fill.set(0,val);    // insert TAP val at the end
        }

        return fill[last];

    }


};

class LFSR_12{
    public:

    int* taps;
    int numTaps=0;
    int last;
    int numShifts;
    bool selfShrinking = false;
    bitset<12> fill;
    
    // Constructors
    LFSR_12(int n){
        numShifts = n;
    }

    LFSR_12(int n, string t){
        numShifts = n;
        if(n>2) selfShrinking = true;
        setTaps(t);
    }

    // Setter Methods 

    void setTaps(string input){

        // Set Global Vars
        last = input.length()-1;
        numTaps = 0;

        // Next, find out how many taps we are using
        for(int i = 0; i<=last; i++) if(input[i]=='1') numTaps++;

        // Next, dynamically create array of tap locations
        taps = new int[numTaps];

        // Next, put the value of the tap locations in the array
        int spot = 0;
        for(int i = 0; i<=last; i++)  { 
            if(input[i]=='1') {
                taps[spot] = last-i; 
                spot++;
            }
        }

    }

    void setFill(int num){
        fill = bitset<12>(num);
    }

    bool shiftAndApplyTaps(){

        bool val;

        for(int t =0; t<numShifts; t++){
            val = fill.test(taps[0]) ^ fill.test(taps[1]);  // XOR the first 2 taps
            for(int i =2; i<numTaps; i++) val ^= fill.test(taps[i]); // then XOR every tap
            fill = fill << 1;   // shift by 1
            fill.set(0,val);    // insert TAP val at the end
        }

        return fill[last];

    }


};

class LFSR_23{
    public:

    int* taps;
    int numTaps=0;
    int last;
    int numShifts;
    bool selfShrinking = false;
    bitset<23> fill;
    
    // Constructors
    LFSR_23(int n){
        numShifts = n;
    }

    LFSR_23(int n, string t){
        numShifts = n;
        if(n>2) selfShrinking = true;
        setTaps(t);
    }

    // Setter Methods 

    void setTaps(string input){

        // Set Global Vars
        last = input.length()-1;
        numTaps = 0;

        // Next, find out how many taps we are using
        for(int i = 0; i<=last; i++) if(input[i]=='1') numTaps++;

        // Next, dynamically create array of tap locations
        taps = new int[numTaps];

        // Next, put the value of the tap locations in the array
        int spot = 0;
        for(int i = 0; i<=last; i++)  { 
            if(input[i]=='1') {
                taps[spot] = last-i; 
                spot++;
            }
        }

    }

    void setFill(int num){
        fill = bitset<23>(num);
    }

    bool shiftAndApplyTaps(){

        bool val;

        for(int t =0; t<numShifts; t++){
            val = fill.test(taps[0]) ^ fill.test(taps[1]);  // XOR the first 2 taps
            for(int i =2; i<numTaps; i++) val ^= fill.test(taps[i]); // then XOR every tap
            fill = fill << 1;   // shift by 1
            fill.set(0,val);    // insert TAP val at the end
        }

        return fill[last];

    }


};

void q2(int n){

        // set up LFSRs
    LFSR_7* l1 = new LFSR_7(1, "1101010"); 
    LFSR_12* l2 = new LFSR_12(2,"101100100011");  
    LFSR_23* l3 = new LFSR_23(2,"10100000000000001010000");  

        // set up fills
    l1->setFill(21);
    l2->setFill(2021);
    l3->setFill(143431890);

        // output file
    ofstream out;
    out.open("../sts-2.1.2/sts-2.1.2/sample.txt");
    int numOutput =0;
    int outputsRequested = n*1000000;
    bool a,b,c;
    while(numOutput < outputsRequested){

            // if ready to output
        a = l1->shiftAndApplyTaps();
        b = l2->shiftAndApplyTaps();
        c = l3->shiftAndApplyTaps();

            // C XOR B  (high bits)
        if(  (c^b) ){   
                // output B XOR C (2nd high bits)
            out << (l2->fill.test(10)^l3->fill.test(20));
            numOutput++;
        }
        else{
                // output C XOR A( 2nd highit on C, highbit on A)
            out << (l3->fill.test(20)^l1->fill.test(6));
            numOutput++;
        }


    }// end million bits loop

    out.close();

}


int main(){
    time_t start;
    time(&start);
    q2(20);
    time_t end;
    time(&end);
    cout << "\n\nMillion Outputs in " << difftime(end,  start)/20.0 << " seconds." << endl;
}
