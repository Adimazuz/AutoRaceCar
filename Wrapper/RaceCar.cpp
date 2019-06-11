#include "RaceCar.h"
#include <vector>

RaceCar::RaceCar()
{
	_arduino = std::make_shared<Arduino>();
	_tcp_client->create();
	//TODO add _camera later
}

RaceCar &RaceCar::connect(const string& ip, const unsigned short& port)
{
	_tcp_client->connect(ip, port);
	//TODO see if constructor changes
	_camera.connectCamera();
    _arduino->connect();
    return *this;

}

RaceCar &RaceCar::run()
{
	while (true)
	{
        std::vector<char> cmd = _tcp_client->receive(1);
		
	}
    return *this;
}

RaceCar &RaceCar::parseCmdString(const std::vector<char>& cmd)
{
    if (cmd.size() < 1)
	{
        return *this;
	}


	switch (cmd[0]) {
	case 's': {
		_arduino->stop();
		break;
	}
	case 'u': {
		_arduino->changeSpeedBy(1);
		break;
	}
	case 'd': {
		_arduino->changeSpeedBy(-1);
		break;
	}
	case 'l': {
		_arduino->changeAngleBy(-5);
		break;
	}
	case 'r': {
		_arduino->changeAngleBy(5);
		break;
	}
	default: _arduino->driveCurrentState();
	}

/*	std::vector<string> cmd_vec;
	splitString(cmd, cmd_vec)*/;

	//if (cmd_vec[0] == "i")
	//{
	//	if (cmd_vec.size == 3) {
	//		_arduino->drive(std::stoi(cmd_vec[1]), std::stoi(cmd_vec[2]));
	//	}
	//}
	//else if (cmd_vec[0] == "stop")
	//{ 
	//	
	//	_arduino->stop();
	//}
	//else if (cmd_vec[0] == "changeAngle")
	//{
	//	if (cmd_vec.size == 2) {
	//		_arduino->changeAngle(std::stoi(cmd_vec[1]));
	//	}
	//}
	//else if (cmd_vec[0] == "changeSpeed")
	//{
	//	if (cmd_vec.size == 2) {
	//		_arduino->changeSpeed(std::stoi(cmd_vec[1]));
	//	}
	//}
	//else if (cmd_vec[0] == "changeAngleBy")
	//{
	//	if (cmd_vec.size == 2) {
	//		_arduino->changeAngleBy(std::stoi(cmd_vec[1]));
	//	}
	//}
	//else if (cmd_vec[0] == "changeSpeedBy")
	//{
	//	if (cmd_vec.size == 2) {
	//		_arduino->changeSpeedBy(std::stoi(cmd_vec[1]));
	//	}
	//}
    return *this;
}

static void splitString(const string &str, std::vector<string> &output)
{
	string::size_type start = 0; // Where to start
	string::size_type last = str.find_first_of(" "); // Finds the first space

	// npos means that the find_first_of wasn't able to find what it was looking for
	// in this case it means it couldn't find another space so we are at the end of the
	// words in the string.
	while (last != string::npos)
	{
		// If last is greater then start we have a word ready
		if (last > start)
		{
			output.push_back(str.substr(start, last - start)); // Puts the word into a vector look into how the method substr() works
		}

		start = ++last; // Reset start to the first character of the next word
		last = str.find_first_of(" ", last); // This means find the first space and we start searching at the first character of the next word
	}

	// This will pickup the last word in the file since it won't be added to the vector inside our loop
	output.push_back(str.substr(start));
}


