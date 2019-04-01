#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sys/stat.h>

using namespace std;

const string traceFolder = "../Test/trace/";
const string defaultCompression = "../Compression/Compression";
#ifdef __x86_64__
const string demoCompression = "../Demo/Compression-Demo-64bit";
#elif __i386__
const string demoCompression = "../Demo/Compression-Demo-32bit";
#endif

const int traceCount = 10;
const string traces[traceCount] = {
  "trace00.txt", "trace01.txt", "trace02.txt", "trace03.txt", "trace04.txt",
  "trace05.txt", "trace06.txt", "trace07.bin", "trace08.bmp", "trace09.mid"
};
int total = 0;
string testCompression = "";
string traceFile = "";
int runTraces = traceCount, currentTrace = 0;
bool firstFail = false, hideError = false, useColor = false;

void useage(const char* progname) {
  cout
    << progname << " [-h] [-e <your_exec>] [-s <stander_exec>] [-t <trace_file>] [-f] [-m] [-q] [-c]" << endl
    << "    -h  Show this message and quit" << endl
    << "    -e  Specify your executable file, default value: " << defaultCompression << endl
    << "    -t  Run specified trace file" << endl
    << "    -f  Stop at first failed test" << endl
    << "    -m  Hide error message" << endl
  ;
  exit(1);
}

void parseArguments(int argc, char** argv) {
  int c;
  opterr = 0;
  while ((c = getopt (argc, argv, "e:s:t:fmqch")) != -1) {
    switch (c)
    {
      case 'e': if (testCompression.size()) useage(argv[0]);testCompression = optarg; break;
      case 't': if (traceFile.size()) useage(argv[0]); traceFile = optarg; break;
      case 'f': if (firstFail) useage(argv[0]); firstFail = true; break;
      case 'm': if (hideError) useage(argv[0]); hideError = true; break;
      case 'c': if (useColor) useage(argv[0]); useColor = true; break;
      case 'h': useage(argv[0]); break;
      default: useage(argv[0]); break;
    }
  }
  if (testCompression.size() == 0) testCompression = defaultCompression;
}

void clearTempFiles(string temp1, string temp2) {
  int r;
  if (temp1 != "") r = system((string() + "rm " + temp1 + " -f").c_str());
  if (temp2 != "") r = system((string() + "rm " + temp2 + " -f").c_str());
  (void)r;
}

bool fileExist(string filename) {
  ifstream ifs(filename.c_str());
  return static_cast<bool>(ifs);
}

string randomFilename() {
  const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  string filename;
  int i;
  while (true) {
    filename = "";
    for (i = 0; i < 8; i++) filename += charset[rand() % charset.length()];
    filename += ".tmp";
    if (!fileExist(filename)) break;
  };
  return filename;
}

size_t getFileSize(string filename)
{
  struct stat st;
  stat(filename.c_str(), &st);
  return st.st_size;
}

int testTrace(const char* trace) {
  string temp1, temp2;
  string demo_temp1, demo_temp2;
  int ret = 0;
  try {
    if (system((string() + "timeout 20 " + testCompression + " " + trace + " " + (temp1 = randomFilename()) + " > /dev/null 2> /dev/null").c_str()) != 0) throw 2;
    if (system((string() + "timeout 20 " + testCompression + " -d " + temp1 + " " + (temp2 = randomFilename()) + " > /dev/null 2> /dev/null").c_str()) != 0) throw 2;
    if (system((string() + "timeout 20 " + demoCompression + " " + trace + " " + (demo_temp1 = randomFilename()) + " > /dev/null 2> /dev/null").c_str()) != 0) throw 5;
    if (system((string() + "timeout 20 " + demoCompression + " -d " + demo_temp1 + " " + (demo_temp2 = randomFilename()) + " > /dev/null 2> /dev/null").c_str()) != 0) throw 5;
    
    if (system((string() + "diff " + trace + " " + temp2 + " > /dev/null 2> /dev/null").c_str()) != 0) throw 4;
    size_t origSize = getFileSize(trace);
    size_t compSize = getFileSize(temp1);
    size_t demo_compSize = getFileSize(demo_temp1);
    cout << "\t  Original file size: " << origSize << "Byte(s)" << endl;
    cout << "\tCompressed file size: " << compSize << "Byte(s)" << endl;
    if (origSize) {
        double comp_ratio = 100.0 * compSize / origSize;
	double demo_ratio = 100.0 * demo_compSize / origSize;
        double fullScore_ratio = demo_ratio + 10;
        int traceScore = 0;
        cout << "\t   Your compression ratio: " << comp_ratio  << "%" << endl;
        cout << "\t   Demo compression ratio: " << demo_ratio  << "%" << endl;
        if (comp_ratio < fullScore_ratio) traceScore = 10;
        else if (comp_ratio > 99.99999) traceScore = 0;
        else traceScore = int((1000 - 10 * comp_ratio) / (100 - fullScore_ratio) + 0.5);
        cout << "\t   score: " << traceScore << endl;
        total += traceScore;
    }
    else {
        cout << "\t   Compression ratio: ------" << endl;
        cout << "\t   score: 10" << endl;
        total += 10;
    }
  } catch (int e) {
    ret = e;
  }
  clearTempFiles(temp1, temp2);
  clearTempFiles(demo_temp1, demo_temp2);
  return ret;
}

void runTest(const string currentTrace) {
  cout << "Trace \"" << currentTrace << "\": " << endl; cout.flush();
  int error = testTrace(currentTrace.c_str());
  if (error == 2) cout << "Error occurred while running your program." << endl;
  if (error == 4) cout << "File is modified after compression and decompression." << endl;
  if (error == 5) cout << "Error occurred while running demo program." << endl;
}

int main(int argc, char** argv) {
  parseArguments(argc, argv);
  try {
    if (traceFile.size()) runTest(traceFile);
    else {
      int i = 0;
      for (; i < traceCount; i++) runTest(traceFolder + traces[i]);
    }
    printf("\033[31mTotal Score: %d\n\033[0m", total);
  } catch (...) {}
  return 0;
}
