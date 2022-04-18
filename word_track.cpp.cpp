#include <iostream>
#include <fstream>
#include<string>
using namespace std;


int StringLenght(char* str);   //To calculate stringlenght

char** ListOfWords(int testcases, int readFromLine);   //reads the list of search words from file 

char** ReadWordSearchGrid(int rows, int cols, int readFromLine);  //reads the grid from input file

int* GridSearch(char** grid, int gridRow, int gridCol, char* word);  // takes all words  of the list turn by turn

int* SearchAllDirections(char** grid, int gridRow, int gridCol, int row, int col, char* word);  //searches the word in all eight directions

void ShowCordinates(char** list, int numberOfWords, char** grid, int rows, int cols); //function to show start and end cordinates  of a word




int StringLenght(char* str)   //function to calculate stringlenght
{
	int stringLen = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		stringLen++;
		i++;
	}

	return stringLen;
}
char** ListOfWords(int testcases, int readFromLine)
{
	ifstream file("Input.txt");
	if (file)
	{

		string dummyLine;
		for (int i = 0; i < readFromLine; i++)      //this skips all the data before words 
		{
			getline(file, dummyLine);
		}

		char** wordList = new char* [testcases];

		int i = 0;

		while (i < testcases)
		{
			char abc[80];

			file.getline(abc, 80);

			int cols = 0;
			cols = StringLenght(abc);

			wordList[i] = new char[cols + 1];

			int j = 0;
			for (j = 0; j < cols; j++) //deep copying
			{
				wordList[i][j] = abc[j];
			}
			wordList[i][j] = '\0';
			i++;
		}

		return wordList;
	}

}
char** ReadWordSearchGrid(int rows, int cols, int readFromLine)
{
	ifstream file("Input.txt");
	if (file)
	{

		string dummyLine;
		for (int i = 0; i < readFromLine; i++) //this skips all the data before grid
		{
			getline(file, dummyLine);
		}

		int i = 0;
		char** Grid = new char* [rows];
		while (i < rows)
		{
			char abc[80];

			file.getline(abc, 80);



			Grid[i] = new char[cols + 1];

			int j = 0;
			int k = 0;
			for (j = 0; j < cols && k < (cols + cols - 1); j++) //deep copying
			{

				Grid[i][j] = abc[k];
				k += 2;

			}
			Grid[i][j] = '\0';
			i++;
		}

		return Grid;
	}

}

int* SearchAllDirections(char** grid, int gridRow, int gridCol, int row, int col, char* word)
{
	int rowDirection[] = { 0, 0, 1,-1, 1, 1, -1, -1 };     // 8 directions  in the order (right to left),(left to right),(top to bottom),(bottom to top),(top left to bottom right),(top right to bottom left),(bottom left to top right),(bottom right to top left)
	int colDirection[] = { -1, 1, 0, 0, 1, -1, 1, -1 };

	int* arr = new int[3];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
							 //if word not found then the array wil will have -1 at 0 position

	if (grid[row][col] != word[0])   //checks if the cordinate have the first letter of word 
	{
		arr[0] = -1;
		arr[1] = 0;
		arr[2] = 0;
		return  arr;
	}


	int length = StringLenght(word);   //user defined


	for (int i = 0; i < 8; i++)  //for 8 directions
	{
		int j;
		int moveRow = row + rowDirection[i];
		int moveCol = col + colDirection[i];

		// First character is already checked, match remaining characters

		for (j = 1; j < length; j++)  //it starts searching after tracking first letter
		{
			// If out of bound then break 
			if (moveRow >= gridRow || moveRow < 0 || moveCol >= gridCol || moveCol < 0)
			{
				break;
			}


			// If not matched, then break 
			if (grid[moveRow][moveCol] != word[j])
			{
				break;
			}



			moveRow = moveRow + rowDirection[i];   //moves in the specuific direction 
			moveCol = moveCol + colDirection[i];
		}


		if (j == length) //if the word is found then j will be equal to length
		{
			moveRow = moveRow - rowDirection[i];
			moveCol = moveCol - colDirection[i];

			arr[0] = 1;
			arr[1] = moveRow;   //end cordinates of the word
			arr[2] = moveCol;

			return arr;
		}

	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return  arr;
}


int* GridSearch(char** grid, int gridRow, int gridCol, char* word)  //this function searches all words
{
	int* returnArray = new int[4];
	int* arr = new int[3];

	for (int row = 0; row < gridRow; row++)
	{
		for (int col = 0; col < gridCol; col++)
		{
			arr = SearchAllDirections(grid, gridRow, gridCol, row, col, word);
			if (arr[0] == 1)
			{
				returnArray[0] = row;  //start cordinates of word
				returnArray[1] = col;

				returnArray[2] = arr[1];  //end codinates of the word
				returnArray[3] = arr[2];
				return returnArray;
			}

		}

	}
	delete[]arr;
	returnArray[0] = -1;
	returnArray[1] = 0;
	returnArray[2] = 0;
	returnArray[3] = 0;
	return returnArray;

}


void ShowCordinates(char** list, int numberOfWords, char** grid, int rows, int cols)  
{
	ofstream file("Output.txt");       // this function shows coordinates
	if (file)
	{
		for (int i = 0; i < numberOfWords; i++)
		{

			int* resultArr = new int[4];

			resultArr = GridSearch(grid, rows, cols, list[i]);  //coodinates will be returned

			if (resultArr[0] == -1)
			{
				file << "Not found";
			}
			else                   //curley brackets for good track output 
			{
				file << "{" << resultArr[0] << "," << resultArr[1] << "}" << "{" << resultArr[2] << "," << resultArr[3] << "}";
			}
			file << endl;
			delete[]resultArr;


		}
	}
	file.close();


}
int main()
{
	ifstream fin("Input.txt");
	if (fin)
	{
		int rows, cols, testcases;

		fin >> rows >> cols >> testcases;


		cout << "word earcing has been started plz wait" << endl;

		int readLine;

		char** grid = nullptr;
		readLine = 2;     //frst line for rows& cols second for testcases
		grid = ReadWordSearchGrid(rows, cols, readLine);     //for grid reading


		char** list = nullptr;
		readLine = 2 + rows;  //words total list will be givn
		list = ListOfWords(testcases, readLine);         //reads the list

		ShowCordinates(list, testcases, grid, rows, cols);
		cout << endl;
		cout << "you specifid words have been searched " << endl;
		cout << "please check the output file for track" << endl;
	}

	system("pause");
	return 0;

}