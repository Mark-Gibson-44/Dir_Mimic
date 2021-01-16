#pragma once
#include <memory>
#include <vector>
#include "Dir.h"

enum DirOp//ENUM used to Define commands
{
	CD = 1,
	LS = 2,
	RM = 3,
	CP = 4,
	MV = 5,
	NEW = 6,
	INVALID = -1,
	CDR = 7,// For testing of absolute paths
	LA = 8,
	NF = 9

};

class FileSystem
{
	Directory root;//Initial Directory
	Directory* head = &root;//Pointer to Head
	Directory* cur;//Pointer to current directory]
public:
	FileSystem() : root("Root"), cur(head/*std::make_shared<Directory>(root)*/){}
	void Browse();
	void changeDir();
	void retToHead();
	void insertDir();
	void changeAbsoluteDir(std::string path);
	//TODO implement parse Dir to allow for absolute Paths
	DirOp ParseCommand(std::string cmd);
	void REPL();
	std::vector<std::string> parseInput(std::string in);
	void changeDirWithArg(std::string arg);
	Directory* getDirLocation(std::string arg);
	void insertFile();

};