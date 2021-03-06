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
	this->cur = /*std::move(*/this->getDirLocation(moving);//);

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
		this->cur = this->cur->getDir(a);
		
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
	if (!strcmp(cmd.c_str(), "la"))
		return LA;
	if (!strcmp(cmd.c_str(), "nf"))
		return NF;
	if (!strcmp(cmd.c_str(), "del"))
		return DEL;
	if (!strcmp(cmd.c_str(), "mv"))
		return MV;
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
			
			this->changeDirWithArg(args[1]); break;
			 
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
		case LA:
			this->cur->list_files(); break;
		case NF:
			this->insertFile(); break;
		case DEL:
			this->deleteDir(); break;
		case MV:
			this->moveDir(); break;
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
	this->cur = this->getDirLocation(arg);
}

Directory* FileSystem::getDirLocation(std::string arg)
{
	return this->cur->getDir(arg);
}

Directory* FileSystem::getAbsoluteLocation(std::string arg)
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
	Directory* temp = this->cur;
	auto depth = traversal(arg);
	for (auto a : depth)
	{
		temp = temp->getDir(a);

	}
	return temp;
}

void FileSystem::moveDir()
{
	std::cout << "Where to move" << std::endl;
	std::string moving;

	std::cin >> moving;
	std::string Dir;
	std::cout << "Which Dir to move" << std::endl;
	std::cin >> Dir;
	assert(this->getAbsoluteLocation(moving) != nullptr);
	this->cur->move(Dir,this->getAbsoluteLocation(moving));
}

void FileSystem::deleteDir()
{
	this->cur->list_dirs();
	std::cout << "Which Dir to delete?" << std::endl;
	std::string deleting;

	std::cin >> deleting;
	this->cur->deleteDir(deleting);
}

void FileSystem::insertFile()
{
	std::cout << "Name of File to Add" << std::endl;
	std::string moving;

	std::cin >> moving;
	this->cur->add_file(moving);
}


 