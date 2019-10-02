//Klutix
//allows you to select a file from a path. If no path is provided the working directory is used.
std::string FileDialogPrompt(std::string path = "",bool cls = false) {
	std::vector<std::string> directory;
	int choice, i = 1;
	if (cls)	
		system("CLS");
	if (path == "")
		path = std::experimental::filesystem::current_path().u8string();
	std::cout << "\nContents of: " << path << std::endl << std::endl;
	for (const auto & entry : fs::directory_iterator(path)) {
		if (!fs::is_directory(entry.path()))
			std::cout << "\t" << i << ") " << entry.path().filename() << std::endl;
		else {
			printf("\t%d) \x1B[93mFOLDER \033[0m", i); //this magic formula makes yellow..
			std::cout << entry.path().filename().u8string() << std::endl;
		}
		directory.push_back(entry.path().u8string());
		i++;
	}
	std::cout << "\t0 - to go back a directory\n";
	std::cout << "\nSelect # of file you choose: ";
	std::cin >> choice;
	choice -= 1; //subract 1 because selection starts at 1
        if (choice + 1 == 0) {
		std::filesystem::path pPath = std::filesystem::path(path);
		FileDialogPrompt(pPath.parent_path().u8string(), cls);
	}
	else if (fs::is_directory(directory[choice]))
		FileDialogPrompt(directory[choice], cls);
	else
		return directory[choice];
}
