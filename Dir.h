#pragma once
#include <memory>
#include <map>
#include <string>
#include <iostream>


class File
{
	std::string  fname;
	const char* ext;
	size_t bytes;
public:
	File(std::string  a);
	File();
	void write();
	std::string  getFname() { return fname; }


};

//TODO learn smart pointers
class Directory
{
	
	std::map<std::string ,Directory> nested;// Used for any directories present within a given directory
	std::map<std::string ,File> files;//Used for all files that are in a given directory
	std::string  name;//Dir Name
	
public:
	Directory(std::string  n);//Constructs a directory
	Directory();
	void add_file(File& f);
	void rm_file(File& f);
	int printSize();
	void add_dir(std::string n);
	//void copy();
	bool inDir(std::string& n);
	void move();//Refering to moving one directory into another directory
	void rm_dir();
	void list_dirs();
	void list_files();
	int get_size();
	std::string getDirName();
	Directory getDir(std::string s);
	

};

