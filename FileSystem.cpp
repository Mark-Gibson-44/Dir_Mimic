#include "FileSystem.h"




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

void FileSystem::changeDir()
{
	this->cur->list_dirs();
	std::cout << "Which directory to move to?" << std::endl;
	std::string moving;
	//std::getline(std::cin, moving);
	std::cin >> moving;
	if (!this->cur->inDir(moving))
	{
		std::cout << "Not a Dir" << std::endl;
		return;
	}
	this->cur = std::make_unique<Directory> (this->cur->getDir(moving));

}

void FileSystem::retToHead()
{
	//this->cur = this->head;
	this->cur = this->head;
}

void FileSystem::insertDir()
{
	std::cout << "Name of Directory to Add" << std::endl;
	std::string moving;

	std::cin >> moving;
	this->cur->add_dir(moving);
}
