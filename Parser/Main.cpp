#include <iostream>
#include "Client.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std; 

string getFieldFromJson(string json, string field);


int main() {
	Client client;
	string res = client.getResponse("google.com");
	cout << getFieldFromJson(res,"as");
	return 0;
}

string getFieldFromJson(string json, string field) {
	stringstream jsonEncoded(json);
	boost::property_tree::ptree root;
	boost::property_tree::read_json(jsonEncoded, root);

	if (root.empty())
		return "";
	return root.get <string>(field);
}