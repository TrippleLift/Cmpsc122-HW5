//Programmer:  Joseph Chang
//Section:     #001
//Activity:    #5
//Date:        April 1, 2018
//File name:   Main.cpp

#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

void validateXML(string xml);
void bubbleSort(vector <string> &target);

int main()
{
	cout << "Enter XML format message\n";
	string text;
	getline(cin, text);
	validateXML(text);

	system("pause");
	return 0;
}

void validateXML(string xml)
{
	bool openSwitch = false; //check > follow only by <
	string temp; //to store temp string (1.for reading the text. 2.for counting strings to print)
	stack <string> xmlCheckSta; //for the XML format checking
	vector <string> xmlStoreText; //for printing if it's valid
	for (int i = 0; i < xml.size(); i++)
	{
		if (xml[i] == '<' && openSwitch == false) //start to read
		{
			openSwitch = true;
			temp = "";
		}
		else if (xml[i] == '>' && openSwitch == true) //stop to read, and get the <CompleteText> for stage 2
		{
			openSwitch = false;
			//scan and push "temp" into "xmlCheckSta" or pop "xmlCheckSta"
			if (temp[0] != '/')
			{
				//check if very text is lower case
				for (int j = 0; j < temp.size(); j++)
				{
					if (!islower(temp[j]))
					{
						//cout << "Error, something is not lower case alphabet!!\n";
						cout << "NOT Valid\n";
						//exit(1);
						return;
					}
				}
				//push temp into stack
				xmlCheckSta.push(temp);
				xmlStoreText.push_back(temp);
			}
			else
			{
				//check if stack is empty
				if (xmlCheckSta.empty())
				{
					//cout << "Error, xml does not match!!\n";
					cout << "NOT Valid\n";
					//exit(1);
					return;
				}
				temp.erase(0, 1);
				//check top and then pop
				if (xmlCheckSta.top() == temp)
					xmlCheckSta.pop();
				else
				{
					//cout << "Error, xml text does not match!!\n";
					cout << "NOT Valid\n";
					//exit(1);
					return;
				}
			}
		}
		else if (openSwitch == true && xml[i] != '<') //reading
		{
			temp += xml[i];
		}
		else if (xml[i] == ' ' && openSwitch == false) //skip the space between > <, ex: <a>  <b>
		{ }
		else //<> format errors
		{
			//cout << "<> format errors!!\n";
			cout << "NOT Valid\n";
			exit(1);
			return;
		}
	}

	//check if stack is empty at the end
	if (xmlCheckSta.empty())
	{
		cout << "Valid\n";

		//for printing
		bubbleSort(xmlStoreText);
		temp = xmlStoreText[0];
		int i = 1;
		int count = 1;
		while (i < xmlStoreText.size())
		{
			if (temp == xmlStoreText[i])
				count++;
			else
			{
				cout << temp << " " << count << endl;
				count = 1;
				temp = xmlStoreText[i];
			}

			i++;
		}
		cout << temp << " " << count << endl;
		return;

		exit(0);
	}
	else
	{
		//cout << "Error, xml does not match!!\n";
		cout << "NOT Valid\n";
		exit(1);
		return;
	}
}

void bubbleSort(vector <string> &target)
{
	for (int i = target.size()-1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (target[j] > target[j + 1])
			{
				string temp = target[j];
				target[j] = target[j + 1];
				target[j + 1] = temp;
			}
		}
	}
}