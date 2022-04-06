#include <iostream> // the required libraries for file handling and vectors
#include <fstream>
#include <vector>

using namespace std; 

void newSet(const vector<char> & v, fstream & output); // prints n and relations of the set to the output file

void reflexive(const vector<char> & v, const vector<char> & in, fstream & output); // decides if the relations are reflexive and prints to the output file with the reason

void symmetric(const vector<char> & v, fstream & output); // decides if the relations are symmetric and prints to the output file with the reason

void antisymmetric(const vector<char> & v, fstream & output);// decides if the relations are anitsymmetric and prints to the output file with the reason

void transitive(const vector<char> & v, fstream & output);// decides if the relations are transitive and prints to the output file with the reason

int main(void){
	
	int count=0; // count is the number before each set in the input file
	char temp=' '; // temp is the character read from the input file
	std::vector<char> str, strtemp; //str holds the elements of the set and strtemp holds the relations
	
	str.reserve(50); // They both have a capacity of 50 at the start but they will grow if needed
	
	strtemp.reserve(50);
	
	fstream input; // inout and output files are opened for reading and writing
	input.open("input.txt");
	fstream output;
	output.open("output.txt", ios::out);
	
	input >> temp; //the first character is read from the input file
	
	while(temp != EOF){ // program will keep running until the file ends

		count = temp - 48; // number is read as character and since count is an integer, 48 is subtracted from temp's value
		
		temp = ','; // temp will mostly be ',' so it's initialized to ','
		
		while(temp == ','){ // the elements of the set are like a,b,c in the file and when the line is over, temp will have the a of an (a,b) relation so temp won't be ',' anymore
			
			input >> temp; //the element is read
			str.push_back(temp);//element is added at the end of str
			input >> temp;//',' is read
		
		}
		
		count *= 2; //count is doubled. count is the line number to be read from the file but every line has 2 elements so count holds the element number now
		
		while(count != 0){ // relations will be read element by element until the given line number is 0
			
			strtemp.push_back(temp);//adds the a of (a,b) at the end of the vector that the relations are kept in
			
			--count;//count is decremented by one, one element is read from the relations
			
			input >> temp; // ',' is read
			
			input >> temp; // b of (a,b) is read

			strtemp.push_back(temp);//adds the b of (a,b) at the end of the vector that the relations are kept in
		
			--count;//count is decremented by two at total, one relation of (a,b) is read
			
			input >> temp; // a of (a,b) is read
		
		}
		
		newSet(strtemp,output); // set is printed to the output file
		
		reflexive(strtemp,str,output); //reflexivity is printed to the output file
		symmetric(strtemp,output);//symmetric is printed to the output file
		antisymmetric(strtemp,output);// antisymmetric is printed to the output file
		transitive(strtemp,output);//transitivity is printed to the output file
		
		str.clear(); // both vectors are cleared to read the new set
		strtemp.clear(); 
		
		count=0; // count is 0 to get the new count
		
		if(temp == EOF)	output.close();//checks if the file is over
	
	}
	
	output.close();//closes the files
	input.close();

}

void newSet(const vector<char> & v, fstream & output){//vector is const since it won't be changed

	output << 'n' << endl; //first, n is printed to separate the sets
	
	int i=0;// i will go through the whole set to print the elements
	
	while(i != v.size()){
	
		output << '(' << v[i] << ',';//ex: i is 0, first element is printed
		
		++i;//ex: i is now 1
		
		output << v[i] << ')';// ex: second element is printed
		
		++i;//ex: i is now 2
	
	}
	
	output << endl; //new line

}

void reflexive(const vector<char> & v, const vector<char> & in, fstream & output){//vectors are const since they won't be changed
	
	output << "Reflexive: ";

	int i=0, j, flag;
	char a=' ';
	
	while(i != in.size()){// iterates over all elements of the set
	
		a = in[i]; // takes the element of the set
		
		flag=0;
		j=0;
	
		while(j != v.size()){// iterates over all the relations
		
			if(v[j] == a && v[j+1] == a)	++flag;//When it finds the (a,a) relation, increments the flag
		
			j += 2; // j is incremented twice to check the a and b in (a,b) relation simultaneously
			
		}
	
		++i; // i is incremented by one to get to the next element of the set
		
		if(flag == 0){ // If flag is zero, that means there are no (a,a) among the relations so it's not reflexive
		
			output << "No, (" << a << ',' << a << ") is not found." << endl; // prints that the relations are not reflexive and gets out of the function
			break;	
			
		}
	
	}
	
	if(flag != 0)	output << "Yes, all elements are present. (" << a << ',' << a << ") is found." << endl; // If flag is incremented at the end of the loop, there are (a,a) for every a, so the
	 															//relations are reflexive
	
}

void symmetric(const vector<char> & v, fstream & output){//vector is const since it won't be changed

	output << "Symmetric: ";
	
	int i=0, j, flag=0;
	char a,b;

	while(i != v.size()){ //iterating over all the relations two by two
	
		a = v[i]; // a and b are taken for (a,b)
		++i;
		b = v[i];
		++i;
		
		j=0;
		
		while(j != v.size()){ // all relations will be searched for (b,a)
		
			if(v[j] == b && v[j+1] == a){//if (b,a) is found, flag is incremented
			
				flag += 2;
			
			}
			
			j += 2;
		
		}
		
		if(flag != i){ // if every relation has a symmetric, flag should be equal to i since it's incremented by two every time for a symmetry is found, if it's not, flag won't be equal to i
		
			output << "No, (" << b << ',' << a << ") is not found whereas (" << a << ',' << b << ") is found." << endl; 
			
			break;
			
		}
	
	}
	
	if(flag == i)	output << "Yes, (" <<  b << ',' << a << ") is found whereas (" << a << ',' << b << ") is found." << endl; //flag will be equal to i if every relation has a symmetry
	
}

void antisymmetric(const vector<char> & v, fstream & output){//vector is const since it won't be changed

	output << "Antisymmetric: ";

	int i=0, j,flag=0;
	char a,b;

	while(i != v.size()){ // iterating over all the elements two by two
	
		a = v[i];
		++i;
		b = v[i];
		++i;
		
		j=0;
		
		while(j != v.size()){//iterating over every relation to see if the relation has a symmetry
		
			if(v[j] == b && v[j+1] == a && a != b){ //if (a,b) has a (b,a) and a and be are not the same, this relation cannot be antisymmetric, the flag is incremented
			
				++flag;
			
			}
			
			j += 2;
		
		}
		
		if(flag != 0){ // flag is incremented if a symmetry is found thus making the relation antisymmetric
		
			output << "No, (" << b << ',' << a << ") is found whereas (" << a << ',' << b << ") is found." << endl;
			break;
		}
	}
	
	if(flag == 0)	output << "Yes, (" <<  b << ',' << a << ") is not found whereas (" << a << ',' << b << ") is found." << endl; // if no symmetries are found, relations are antisymmetric

}

void transitive(const vector<char> & v, fstream & output){//vector is const since it won't be changed

	output << "Transitive: ";

	char a, b, c;
	int i=0, j, k, flag;
		
	while(i != v.size()){//iterating over all the elements two by two
		
		a = v[i];//a and be are taken
		++i;
		b = v[i];
		++i;
		
		j=0;
	
		while(j != v.size()){//iterating over the relations again to see if any of the relations start with b
		
			if(v[j] == b){ // if a relation starts with b, the element after b will be set as c
			
				c = v[j+1];
				
				k=0;
				
				flag=0;
				
				while(k != v.size()){//the relations will be checked for a relation (a,c)
			
					if(v[k] == a && v[k+1] == c)	++flag;//if found, flag will be incremented
					
					k += 2;
			
				}
			
			}
			
			if(flag == 0){ // if flag is not incremented, there isn't a (a,c) for (a,b) and (b,c), making the relation non-transitive
				
				output << "No, (" << a << ',' << c << ") is not found whereas (" << a << ',' << b << ") and (" << b << ',' << c << ") is found." << endl;
					
				break;
					
			}
			
			j += 2;
		
		}
		
		if(flag == 0){// if flag is 0, the relation is already proved to be non-transitive, this if statement will get the program out of the second while loop
					
			break;
					
		}	
	
	}
	
	if(flag != 0)	output << "Yes, (" << a << ',' << c << ") is found since (" << a << ',' << b << ") and (" << b << ',' << c << ") is found." << endl;//if flag is incremented, relations are transitive

}
