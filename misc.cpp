//Klutix
//a recursive function that allows you to select a file from a path. 
//  (If no path is provided the working directory is used)
std::string FileDialogPrompt(std::string path = "") {
	int choice, i = 1;
	std::vector<std::string> directory;
	if (path == "")
		path = std::experimental::filesystem::current_path().u8string();
	std::cout << "\nShowing path.." << path << std::endl << std::endl;
	for (const auto & entry : fs::directory_iterator(path)) {
		std::cout << "\t" << i << ") " << entry.path() << std::endl;
		directory.push_back(entry.path().u8string());
		i++;
	}
	std::cout << "\t0 - to go back a directory\n";
	std::cout << "\nSelect # of file you choose: ";
	std::cin >> choice;
	choice -= 1; //subract 1 because selection starts at 1
        if (choice + 1 == 0) {
		std::filesystem::path pPath = std::filesystem::path(path);
		FileDialogPrompt(pPath.parent_path().u8string());
	}
	else if (fs::is_directory(directory[choice]))
		FileDialogPrompt(directory[choice]);
	else
		return directory[choice];
}
