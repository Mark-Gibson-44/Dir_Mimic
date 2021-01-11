#include "Dir.h"

Directory::Directory()
{
	this->name = "untitled";
}

Directory::Directory(std::string  n)
{
	this->name = n;
}

void Directory::add_file(File& f)
{
	this->files[f.getFname()] = f;
}

void Directory::rm_file(File& f)
{
	files.erase(f.getFname());
}

int Directory::printSize()
{
	return sizeof(this);
}

void Directory::add_dir(std::string  n)
{
	if (inDir(n))
	{
		std::cout << "Directory of that name exists" << std::endl;
		n += ' (1)';


	}
	Directory ne(n);
	this->nested[n] = ne;
}

bool Directory::inDir(std::string& n)
{
	auto r = nested.find(n);
	return r != nested.end();
	
}


void Directory::list_dirs()
{
	for (auto it = nested.cbegin(); it != nested.cend(); ++it)
	{
		std::cout << it->first << "\n";
	}
}

std::string Directory::getDirName()
{
	return this->name;
}

Directory Directory::getDir(std::string s)
{
	return this->nested[s];
}

File::File()
{
	this->fname = "untitled.txt";

	//this->ext = Read on from '.' in a given string
}


File::File(std::string  a)
{
	this->fname = a;
	//this->ext = Read on from '.' in a given string
}




