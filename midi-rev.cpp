#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
//run with
//  ./flip ascend.asc

int main(int argc, char *argv[]){
	//grab file as stream
	cout<<"--Welcome to flipmidi--"<<endl;

	string tempstr;
	int note = 0,
		time = 0, 
		total_time = 0;
	bool end = false;

	//make stream argument name
	ifstream inputfile(argv[1]);
	if(!inputfile.is_open()){
	cout<<"error: file doesn't exist in directory"<<endl;
	return 1;
	}

	//save as asc file to be converted to midi
	ofstream out("output.asc");
	//vector for input file
	vector<string> input_vector;

	//store input file in vector
	while(inputfile.eof()==0){
		inputfile>>tempstr;	//stores input string in tempstr
		input_vector.push_back(tempstr);	//pushes string to vector

		//if 'on' has been called, the only 'meta' in file left is the song length
		if(tempstr=="On")
			end = true;

		if(tempstr=="Meta" && end==true){
			input_vector.pop_back();	//goes back by one string to grab time
			stringstream total(input_vector.back());	//convert vector string to stream
			total >> total_time;	//stream to int
			cout<<"Total Time: "<<total_time<<endl;
			input_vector.pop_back();	//pops time
		}
	}
	
	//pops any excess from the end of vector
	while(input_vector.back()=="TrkEnd" || input_vector.back()=="Meta"){
		input_vector.pop_back();
	}
	
	//complete file is stored and we have total time
	//if total time not found, exit with error
	if(total_time==0){
		cout<<"error: no TrkEnd time found";
		return 2;
	}
	
	//add template header to file
	out<<"MFile 1 2 15360\nMTrk\n0 Meta SeqName \"Transport\"\n";
	out<<"0 Meta InstrName \"Hardware Interface II\"\n";
	out<<"0 Meta 0x21 00\n0 Tempo 500000\n0 TimeSig 4/4 24 8\n";
	out<<"38400 Meta TrkEnd\nTrkEnd\nMTrkr\n";
	out<<"0 Meta TrkName \"Original Ch1\"\n";
	out<<"0 Meta InstrName \"Original Ch1\"\n";
	out<<"0 Meta 0x21 03\n";
	
	
	//vector back is now at the final 'v=0'
	//it takes 5 pops to go to the next line
	//note(n) and channel(ch) will stay the same
	//so no change to 2nd or 3rd pop
	
	//test what's next
	cout<<"First Up: "<<input_vector.back()<<endl;
	
	//we will iterate through the vector backwards
	while(!input_vector.empty()){
		
		//v=0 so we want to make not change
		//put print to asc out file
		//out<<input_vector.back()<<endl;
		//input_vector.pop_back();	//pop v=0
		
		//if meta comes up, don't bother...
		//if(input_vector.at(input_vector.size()-3)=="Meta"){
		//	cout<<"-3: ";
		//	cout<<input_vector.at(input_vector.size()-3)<<endl;
		//	break;
		//}
			
		
		//finds the 1st value at the beginning of each row
		stringstream stream_time(input_vector.at(input_vector.size()-5));
		stream_time >> time;
		//cout<<"time: "<<time<<endl;
		time = total_time - time;
		out<<time<<" ";
		
		//2nd value should flip (On/Off)
		//cout<<"on/off: "<<input_vector.at(input_vector.size()-4)<<endl;
		if(input_vector.at(input_vector.size()-4)=="On")
			out<<"Off ";
		else	
			out<<"On ";
		
		//3rd value (ch) should stay the same
		out<<input_vector.at(input_vector.size()-3)<<" ";
		
		//4th value (n) should stay the same
		out<<input_vector.at(input_vector.size()-2)<<" ";
		
		//5th value (v) should flip
		if(input_vector.at(input_vector.size()-1)=="v=0")
			out<<"v=70"<<endl;
		if(input_vector.at(input_vector.size()-1)=="v=70")
			out<<"v=0"<<endl;
		
		//after entire row is complete, pop row
		input_vector.pop_back();
		input_vector.pop_back();
		input_vector.pop_back();
		input_vector.pop_back();
		input_vector.pop_back();
		//cout<<"new row: "<<input_vector.back()<<endl;
	}
	
	out<<"fuck you"<<endl;
	cout<<"fuck you"<<endl;
	out<<total_time<<" Meta TrkEnd"<<endl;
	out<<"TrkEnd"<<endl;
	
	return 0;
}
