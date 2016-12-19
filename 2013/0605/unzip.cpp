OmnString unzip(OmnString &zipPath)
{
	aos_assert_r(zipPath != "", false);

	unsigned found = zipPath.data().find_last_of("/\\");
	string path = zipPath,data().substr(0, found);
	string file = zipPath.data().substr(found+1);

	unsigned tmpf = file.find_last_of(".");
	string dirname = file.substr(0, tmpf);
	
	string dirPath = path + "/" + dirname;
	system("mkdir " + dirPath);
	system("unzip -o "+ zipPath.data() +" -d " + dirPath);
	
	OmnString newdirPath;
	newdirPath << dirPath;
	return newdirPath;
}

