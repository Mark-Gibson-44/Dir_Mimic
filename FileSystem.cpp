#include "FileSystem.h"

/*
Function to demonstrate basic uses of the filesystem
*/
void FileSystem::Browse()
{
	bool cont = true;
	while (cont)
	{
		std::cout << "In Directory " << this->cur->getDirName() << "." << std::endl;

		std::cout << "1: List Directory" << std::endl;
		std::cout << "2: Add Directory" << std::endl;
		std::cout << "3: Change Directory" << std::endl;
		std::cout << "4: Exit" << std::endl;
		std::cout << "5: Return to Root" << std::endl;
		int choice;
		std::cin >> choice;
		switch (choice)
		{
		case 1: this->cur->list_dirs(); break;
		case 2: this->insertDir(); break;
		case 3: this->changeDir(); break;
		case 4: cont = false; break;
		case 5: this->retToHead(); break;
		default: std::cout << "Invalid option" << std::endl; break;
		}
	}
}

/*
Prints out all directories present in a the current Directory
Then prompts user to select which to move to
Checks if the Dir exists
Then moves into the Dir
*/
void FileSystem::changeDir()
{
	this->cur->list_dirs();
	std::cout << "Which directory to move to?" << std::endl;
	std::string moving;
	std::cin >> moving;
	if (!this->cur->inDir(moving))
	{
		std::cout << "Not a Dir" << std::endl;
		return;
	}
	this->cur = std::make_unique<Directory> (this->cur->getDir(moving));

}



/*
Function used to Return to the root of The Dir from anywhere

*/
void FileSystem::retToHead()
{
	
	this->cur = this->head;
}

/*
Adds A directory into where the current Directory is located
*/
void FileSystem::insertDir()
{
	std::cout << "Name of Directory to Add" << std::endl;
	std::string moving;

	std::cin >> moving;
	this->cur->add_dir(moving);
}

   
void FileSystem::changeAbsoluteDir(std::string path)
{
	auto traversal = [](std::string& p) {
		std::vector<std::string> retu;
		auto start = p.begin();

		auto lastChar = p.begin();
		for (start; start != p.end(); start++)
		{
			if (*start == '/')
			{

				retu.push_back(std::string(lastChar, start));
				lastChar = start;
				lastChar++;
			}

		}

		retu.push_back(std::string(lastChar, start));
		return retu;
	};
	auto depth = traversal(path);
	for (auto a : depth)
	{
		this->cur = std::make_unique<Directory>(this->cur->getDir(a));
		//std::cout << a << std::endl;
	}
}

DirOp FileSystem::ParseCommand(std::string cmd)
{
	
	if (!strcmp(cmd.c_str(), "cd"))
		return CD;
	
	if (!strcmp(cmd.c_str(), "ls"))
		return LS;
	if (!strcmp(cmd.c_str(), "rm"))
		return RM;
	if (!strcmp(cmd.c_str(), "mv"))
		return MV;
	if (!strcmp(cmd.c_str(), "new"))
		return NEW;
	if (!strcmp(cmd.c_str(), "cdr"))
		return CDR;
	return INVALID;
}

void FileSystem::REPL()
{
	while (true)
	{
		std::cout << "In Directory " << this->cur->getDirName() << "." << std::endl;
		std::string cmd;
		std::getline(std::cin, cmd);
		std::vector<std::string> args = parseInput(cmd);
		
		
		
		switch (ParseCommand(args[0]))
		{
		case CD:
			if (args.size() == 1)
			{
				this->retToHead(); break;
			}
			this->changeDir(); break;
			//this->changeDirWithArg(args[1]); break;
			 
		case LS:
			this->cur->list_dirs(); break;
		case NEW:
			this->insertDir(); break;
		case CDR:
			if (args.size() == 1)
			{
				this->retToHead(); break;
			}
			this->changeAbsoluteDir(args[1]); break;
		}
	}
}

/*
Separates a CLI arg by spaces for example cd C:/documents
would return {"cd", "C:/documents"}
*/
std::vector<std::string> FileSystem::parseInput(std::string in)
{
	std::vector<std::string> retu;
	auto start = in.begin();

	auto lastChar = in.begin();
	for (start; start != in.end(); start++)
	{
		if (*start == ' ')
		{

			retu.push_back(std::string(lastChar, start));
			lastChar = start;
			lastChar++;
		}

	}

	retu.push_back(std::string(lastChar, start));
	return retu;
}

void FileSystem::changeDirWithArg(std::string arg)
{
	
	if (!this->cur->inDir(arg))
	{
		std::cout << "Not a Dir" << std::endl;
		return;
	}
	this->cur = std::make_unique<Directory>(this->cur->getDir(arg));
}
 