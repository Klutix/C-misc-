//Klutix
//allows you to select a file from a path. If no path is provided the working directory is used.
std::string FileDialogPrompt(std::string path = "",bool cls = false,std::string message = "") {
	std::vector<std::string> directory;
	int choice, i = 1;
	if (cls)	
		system("CLS");
	std::cout << message; //show any passed messages
	if (path == "")
		path = std::experimental::filesystem::current_path().u8string();
	std::cout << "\nContents of: " << path << std::endl << std::endl;
	for (const auto & entry : fs::directory_iterator(path)) {
		if (!fs::is_directory(entry.path()))
			std::cout << "\t(" << i << ") " << entry.path().filename() << std::endl;
		else {
			printf("\t(%d) \x1B[93m FOLDER \033[0m", i); //this magic formula makes yellow..
			std::cout << entry.path().filename().u8string() << std::endl;
		}
		directory.push_back(entry.path().u8string());
		i++;
	}
	std::cout << "\n\t(0) - to go back a directory\n";
	std::cout << "\t(-1) - to Exit\n";
	std::cout << "\nSelect # of file you choose: ";
	std::cin >> choice;
	if (std::cin.fail()) {
		std::cin.clear(); 
		std::cin.ignore();
		return  FileDialogPrompt(path, cls, "Invalid selection. Choose a # from directory listing\n");
	}
	//choice -= 1; //subract 1 because selection starts at 1
	if (choice== 0) { //go back a directory
		std::filesystem::path pPath = std::filesystem::path(path);
		return FileDialogPrompt(pPath.parent_path().u8string(), cls);
	}
	else if (choice < 0)
		return "";
	else if (choice >= directory.size())  //why is this returning true when -1
		return FileDialogPrompt(path, cls,  "Invalid selection. Choose a # from directory listing\n");
	else if (fs::is_directory(directory[choice - 1]))
		return FileDialogPrompt(directory[choice - 1], cls);
	else
		return directory[choice - 1];
}
