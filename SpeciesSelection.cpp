/*
 * Species Selection
 * An object, niche-based approach to species selection
 * proposed by Simon Butler etc in 'Methods in Ecology and Evolution' 2012
 * 
 * The main method for command-line interface
 */

#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include "SpecRTGraph.h"
#include "SpeciesSelection.h"
#include "MinSpecSetFamily.h"
using namespace std;
using namespace chrono;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

SpeciesSelection::SpeciesSelection() {
}

SpeciesSelection::~SpeciesSelection() {
}

/**
 * @param args the command line arguments
 * The first argument is the name for the input file
 * The second argument is the name for the output file
 * The third argument is for the number of species sets for each size
 * The fourth argument for the minimal size of species in a species set
 * The fifth argument for the maximal size of species in a species set
 * @throws java.io.FileNotFoundException
 */
void SpeciesSelection::main(vector<string> args) {

	auto start = high_resolution_clock::now();

   // TODO code application logic here
	cout << "The Indicator Species Selection Project." << endl;
	cout << "By Taoyang Wu" << endl;
	cout << "Converted to C++ by S Whiddett, Version 2.0, Jan 2018" << endl;

   //construct the bipartite graph between species and indicators.
   SpecRTGraph *sig = new SpecRTGraph();

   //the list to record the indicators that have been processed.
   vector<int> indicatorCreated;

   // store number of args
   int numArgs = args.size();

   // get input filename
   string fileName;
   int numWordsInName;
   if (numArgs > 0) {
      fileName = args[0];
	  numWordsInName = 1;
   }
   else
   {
	   fileName = "Forest_D_ALL.txt"; //default input data
	   numWordsInName = 1; //the number of words contains in the species name
   }

   // get output filename
   string outFileName;
   if (numArgs > 1) {
      outFileName = args[1];
   }
   else
   {
	   outFileName = fileName + "_result.txt"; //default file for output
   }

   cout << "The dataset is taken from file " << fileName << endl;

	// Read and process each line of input file
   readFile(fileName, sig, numWordsInName);

   //Output the results to a file
   ofstream outPut;
   outPut.open(outFileName);
   outPut << "The dataset:" << fileName << endl;
   outPut << "The dataset contains " << sig->numSpecies() << " species and " << sig->numResourceTypes() << " resource types" << endl;

   int startSize = 2;
   int endSize = sig->numSpecies() - 1;

   int numOfSpeciesSet = 11; //the number of species sets for 
   //each size, 11 is the default size;

   if (numArgs > 2) {
      numOfSpeciesSet = stoi(args[2]) + 1;
   }

   if (numArgs > 3) {
      startSize = stoi(args[3]);
      endSize = startSize;
   }

   if (numArgs > 4) {
      endSize = stoi(args[4]);
   }

   auto finish = high_resolution_clock::now();
   cout << "Initial Setup time: " << duration_cast<nanoseconds>((finish - start) / 1000000.0).count() << "ms" << endl;


   start = high_resolution_clock::now();

   MinSpecSetFamily *mssf = sig->getMinDomSpecSets();
   cout << "MSSF: " << mssf->size() << endl;

   finish = high_resolution_clock::now();
   cout << "MinSpecSetFamily time: " << duration_cast<nanoseconds>((finish - start) / 1000000.0).count() << "ms" << endl;

   start = high_resolution_clock::now();
   cout << "Start size: " << startSize << ", End size: " << endSize << endl;
   for (int i = startSize; i <= endSize; i++) {
      SpecSetFamily *consFamily = sig->getDomSpecSets(i, numOfSpeciesSet, mssf);
      outPut << "For " << i << "  species" << endl;
      outPut << consFamily->toString() << endl;
   }
   finish = high_resolution_clock::now();
   cout << "consFamily For loop time: " << duration_cast<nanoseconds>((finish - start) / 1000000.0).count() << "ms" << endl;


   outPut.close();
   cout << "The output is stored in " << outFileName << endl;
} //main 


void SpeciesSelection::readFile(string fileName, SpecRTGraph *sig, int numWordsInName) {
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile) {
		cerr << "Unable to open file " << fileName << endl;
		exit(1); // call system to stop
	}

	string line;
	getlineSafe(inFile, line);
	istringstream iss(line);
	string titleInformation = iss.str();
	cout << titleInformation << endl;

	while (getlineSafe(inFile, line)) {
		istringstream iss(line);
		string text = iss.str();
		if (text.length() > 0) {
			processLine(text, sig, numWordsInName);
		}
	}
	inFile.close();
}




vector<int> SpeciesSelection::stringToVector(string text) {
   stringstream stream(text);
   vector<int> values(
     (istream_iterator<int>(stream)),
     (istream_iterator<int>()));
   return values;
}

string SpeciesSelection::intToString(int num) {
   ostringstream oss;
   oss << num;
   return oss.str();
}

//process the given String for a line of the data file
void SpeciesSelection::processLine(string text, SpecRTGraph* sig, int numWordsInName) {
	//cout << "process line starting" << endl;
   // convert text to vector of ints
   vector<int> data = stringToVector(text);

   int position = 1;
   //create a new species
   string spName = intToString(data[0]);
   if (numWordsInName == 2) {
      spName.append(" ").append(intToString(data[1]));
      position++;
   }
   Species *inSpec = new Species(spName);


   int spReliance = data[position];
   position++;
   int spResources = data[position];
   position++;
   int spSensitivity = data[position];
   position++;
   inSpec->setReliance(spReliance);


   //the indication information
   int index = 0;

   //test variable
   for(position; position < data.size(); position++)
   {
      index++;
      int indValue = data[position];
      if (indValue == 1) {
         //first to check whether an indicator with the given id exists
         //System.out.println("The index is "+index+".");
         ResourceType *tmpInd = sig->getResourceTypeByID(index);


         if (tmpInd != nullptr) {
            sig->addEdge(inSpec, tmpInd);
         } else {
            //System.out.println("no such indicator "+index);
            ResourceType *newInd = new ResourceType(index);
            sig->addEdge(inSpec, newInd);
         }
      }
   }
   //cout << "process line done" << endl;
} //process a line


istream& getlineSafe(istream& is, string& t) {
	t.clear();
	// Method taken From: https://gist.github.com/josephwb/df09e3a71679461fc104
	// Deals with unix and windows line endings unlike standard getline()

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	istream::sentry se(is, true);
	streambuf* sb = is.rdbuf();

	for (;;) {
		int c = sb->sbumpc();
		switch (c) {
		case '\n':
			return is;
		case '\r':
			if (sb->sgetc() == '\n') {
				sb->sbumpc();
			}
			return is;
		case EOF:
			// Also handle the case when the last line has no line ending
			if (t.empty()) {
				is.setstate(ios::eofbit);
			}
			return is;
		default:
			t += (char)c;
		}
	}
}

