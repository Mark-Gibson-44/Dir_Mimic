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
	INVALID = -1

};

class FileSystem
{
	Directory root;//Initial Directory
	const std::shared_ptr<Directory> head = std::make_unique<Directory>(root);//Pointer to Head
	std::shared_ptr<Directory> cur;//Pointer to current directory
public:
	FileSystem() : root("Root"), cur(std::make_shared<Directory>(root)){}
	void Browse();
	void changeDir();
	void retToHead();
	void insertDir();
	void changeAbsoluteDir(std::string path);
	//TODO implement parse Dir to allow for absolute Paths
	DirOp ParseCommand(std::string cmd);
	void REPL();
	std::vector<std::string> parseInput(std::string in);


};