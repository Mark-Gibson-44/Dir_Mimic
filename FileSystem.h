#pragma once
#include <memory>
#include "Dir.h"

enum DirOp
{
	CD,
	LS,
	RM,
	CP,
	MV,
	NEW
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




};