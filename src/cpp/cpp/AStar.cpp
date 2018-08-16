//// A C++ Program to implement A* Search Algorithm

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <set>
#include <algorithm>
#include <stack>
#include <vector>
#include <string>
#include "opencv2/core.hpp"
#include <list>
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include <queue>
#include <structuredquery.h>
#include <concurrent_priority_queue.h>
#include <functional>
using namespace std;

int DistanceCalc(cv::Point point1, cv::Point point2)
{
	return int(sqrt(pow(point1.x + point2.x, 2) + pow(point1.y + point2.y, 2)));
}

class Node
{
public:
	cv::Point Possition;
	int DistFromBegin, DistToDest, Total;
	Node* Parent;
	Node(cv::Point possition, cv::Point *destination, Node *parent) /*:h(h1), name(name1)*/
	{
		Possition = possition;
		if (parent==NULL)
		Parent = NULL;
		if (Parent != NULL) DistFromBegin = Parent->DistFromBegin + 1;
		else DistFromBegin = 0;
		DistToDest = DistanceCalc(Possition, *(destination));
		Total = DistFromBegin + DistToDest;
		
	}
	bool friend operator< (const Node& Node1, const Node &Node2)
	{
		return Node1.Total > Node2.Total;
	}
	friend bool operator> (const Node& Node1, const Node &Node2)
	{
		return Node1.Total < Node2.Total;
	}


};




//struct Compare
//{
//	bool operator()(const Node &t1, const Node &t2) const
//	{
//		return t1.br > t2.br;
//	}
//};

bool CheckPossitionForMoving(cv::Mat image, cv::Point possition)
{
	//255 - white(no) ; 0 - black - can
	if (cv::Scalar(image.at<uchar>(possition)).val[0] == 0)return true;
	else return false;
}

bool CheckIfCanVisit(list<cv::Point> *visited, cv::Point *PossitionToCheck)
{
	return !(std::find(visited->begin(), visited->end(), *PossitionToCheck) != visited->end());
	
}

void CheckNeighbor(cv::Mat image, Node *node, cv::Point *destination, priority_queue<Node, vector<Node>, less<vector<Node>::value_type>> *nodes, list<cv::Point> *visited)
{

	//cout << node->Possition << " " << CheckPossitionForMoving(image,node->Possition) << endl;
	cv::Point right(node->Possition.x + 1, node->Possition.y);
	cv::Point left(node->Possition.x - 1, node->Possition.y);
	cv::Point top(node->Possition.x, node->Possition.y - 1);
	cv::Point down(node->Possition.x, node->Possition.y + 1);

	if (CheckPossitionForMoving(image, left) && CheckIfCanVisit(visited, &left))
	{
		nodes->push(Node(left, destination, node));
		//visited->push_back(left);
	}
	if (CheckPossitionForMoving(image, right) && CheckIfCanVisit(visited, &right))
	{
		nodes->push(Node(right, destination, node));
		//visited->push_back(right);
	}
	if (CheckPossitionForMoving(image, top) && CheckIfCanVisit(visited, &top))
	{
		nodes->push(Node(top, destination, node));
		//visited->push_back(top);
	}
	if (CheckPossitionForMoving(image, down) && CheckIfCanVisit(visited, &down))
	{
		nodes->push(Node(down, destination, node));
		//visited->push_back(down);
	}


}



void test2(priority_queue<int> *a1)
{
	a1->push(50);
	a1->push(48);
}

void test()
{
	priority_queue<int> a1;
	//concurrency::concurrent_priority_queue<int> a1;
	a1.push(13);
	a1.push(5);
	a1.push(38);
	a1.push(34);
	test2(&a1);
	//int a2 = a1.size()
	cout << a1.top() << endl;
	//priority_queue<Node*, vector<Node*>, Compare> nodesToCheck;
	//priority_queue<Node> nodesToCheck;
	//priority_queue<Node*, vector<Node*>, less<vector<Node*>::value_type> > nodesToCheck;
	//priority_queue<Node, vector<Node>, less<vector<Node>::value_type> > nodesToCheck;

	priority_queue<Node, vector<Node>, less<vector<Node>::value_type>> nodesToCheck;
	/*nodesToCheck.push(Node(2, "ss", NULL));

	nodesToCheck.push(Node(3, "s1", new Node(nodesToCheck.top())));
	if (nodesToCheck.top().Parent == NULL)
		cout << "ZERO" << endl;
	else cout << nodesToCheck.top().Parent->name << endl;
	cin.get();*/
	/*nodesToCheck.push(Node(5, "s2", nodesToCheck.top));
	nodesToCheck.push(Node(4, "s3", nodesToCheck.top));*/

	//priority_queue<Toast, vector<Toast>, ToastCompare> queue;
	//priority_queue<Toast, vector<Toast>, /*less*/greater<vector<Toast>::value_type>> queue;

	//queue.push(Toast(100, 1));
	//queue.push(Toast(120, 2));
	//queue.push(Toast(10, 3));
	//queue.push(Toast(110, 4));
	//cout << queue.top().butter << endl;

	cin.get();
}

//vector<cv::Point> PathFinder(cv::Mat maze, cv::Point currentPossition, cv::Point destinationPossition)
cv::Mat PathFinder(cv::Mat maze, cv::Point currentPossition, cv::Point destinationPossition)
{
	vector<cv::Point> Path;
	//cout << DistanceCalc(currentPossition, destinationPossition);
	priority_queue<Node, vector<Node>, less<vector<Node>::value_type>> nodes;
	nodes.push(Node(currentPossition, &destinationPossition, NULL));
	list<cv::Point> visitidPoint;
	cv::Mat local;
	maze.copyTo(local);
	Node buf = nodes.top();
	int i = 0;
	do {
		buf = nodes.top();
		nodes.pop();

		visitidPoint.push_front(buf.Possition);


		//visitidPoint.push_back(buf.Possition);

		//if (std::find(visitidPoint.begin(), visitidPoint.end(), buf.Possition) != visitidPoint.end())cout << "youcant";
		//else
		//{
		//	cout << "canandpushing" << endl;
		//	visitidPoint.push_back(buf.Possition);
		//}
		//if (CheckIfCanVisit(&visitidPoint, &buf.Possition)) cout << "youcan" << endl;

		//cout << visitidPoint.size() << endl;
		//cout << nodes.size() << endl;
		//std::cout.flush(100);
		CheckNeighbor(maze, &buf, &destinationPossition, &nodes, &visitidPoint);
		//cout << nodes.size() << endl;
		cv::drawMarker(local, buf.Possition, cv::Scalar(255, 255, 255),0,3);
		
	} while (nodes.size() > 0 && buf.Possition != destinationPossition);
	if (buf.Possition == destinationPossition)
	{
		cout << "Visited point" << visitidPoint.size() << endl;
		cout << "Cycle" << nodes.size() << endl;
		cout << "Success" << endl;
	}
	cout <<&buf<<" "<< buf.Possition << " " << buf.Parent  << endl;
	//while (buf.Parent != NULL)
	//{
	//	Path.push_back(buf.Possition);
	//	buf = *buf.Parent;
	//}
	//cout << nodes.top().Possition<<" "<<nodes.top().DistFromBegin<<" "<<nodes.top().DistToDest<<" "<<nodes.top().Total<<" "<<nodes.top().Parent << endl;
	cout << "Path built" << endl;
	//cv::namedWindow("Result");
	//cv::imshow("Result", local);
	cin.get();
	return local;
	//return Path;
}










//
//#define ROW 9
//#define COL 10
//
//// Creating a shortcut for int, int pair type
//typedef pair<int, int> Pair;
//
//// Creating a shortcut for pair<int, pair<int, int>> type
//typedef pair<double, pair<int, int>> pPair;
//
//// A structure to hold the neccesary parameters
//struct cell
//{
//	// Row and Column index of its parent
//	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
//	int parent_i, parent_j;
//	// f = g + h
//	double f, g, h;
//};
//
//// A Utility Function to check whether given cell (row, col)
//// is a valid cell or not.
//bool isValid(int row, int col)
//{
//	// Returns true if row number and column number
//	// is in range
//	return (row >= 0) && (row < ROW) &&
//		(col >= 0) && (col < COL);
//}
//
//// A Utility Function to check whether the given cell is
//// blocked or not
//bool isUnBlocked(int grid[][COL], int row, int col)
//{
//	// Returns true if the cell is not blocked else false
//	if (grid[row][col] == 1)
//		return (true);
//	else
//		return (false);
//}
//
//// A Utility Function to check whether destination cell has
//// been reached or not
//bool isDestination(int row, int col, Pair dest)
//{
//	if (row == dest.first && col == dest.second)
//		return (true);
//	else
//		return (false);
//}
//
//// A Utility Function to calculate the 'h' heuristics.
//double calculateHValue(int row, int col, Pair dest)
//{
//	// Return using the distance formula
//	return ((double)sqrt((row - dest.first)*(row - dest.first)
//		+ (col - dest.second)*(col - dest.second)));
//}
//
//// A Utility Function to trace the path from the source
//// to destination
//void tracePath(cell cellDetails[][COL], Pair dest)
//{
//	printf("\nThe Path is ");
//	int row = dest.first;
//	int col = dest.second;
//
//	stack<Pair> Path;
//
//	while (!(cellDetails[row][col].parent_i == row
//		&& cellDetails[row][col].parent_j == col))
//	{
//		Path.push(make_pair(row, col));
//		int temp_row = cellDetails[row][col].parent_i;
//		int temp_col = cellDetails[row][col].parent_j;
//		row = temp_row;
//		col = temp_col;
//	}
//
//	Path.push(make_pair(row, col));
//	while (!Path.empty())
//	{
//		pair<int, int> p = Path.top();
//		Path.pop();
//		printf("-> (%d,%d) ", p.first, p.second);
//	}
//
//	return;
//}
//
//// A Function to find the shortest path between
//// a given source cell to a destination cell according
//// to A* Search Algorithm
//void aStarSearch(int grid[][COL], Pair src, Pair dest)
//{
//	// If the source is out of range
//	if (isValid(src.first, src.second) == false)
//	{
//		printf("Source is invalid\n");
//		return;
//	}
//
//	// If the destination is out of range
//	if (isValid(dest.first, dest.second) == false)
//	{
//		printf("Destination is invalid\n");
//		return;
//	}
//
//	// Either the source or the destination is blocked
//	if (isUnBlocked(grid, src.first, src.second) == false ||
//		isUnBlocked(grid, dest.first, dest.second) == false)
//	{
//		printf("Source or the destination is blocked\n");
//		return;
//	}
//
//	// If the destination cell is the same as source cell
//	if (isDestination(src.first, src.second, dest) == true)
//	{
//		printf("We are already at the destination\n");
//		return;
//	}
//
//	// Create a closed list and initialise it to false which means
//	// that no cell has been included yet
//	// This closed list is implemented as a boolean 2D array
//	bool closedList[ROW][COL];
//	memset(closedList, false, sizeof(closedList));
//
//	// Declare a 2D array of structure to hold the details
//	//of that cell
//	cell cellDetails[ROW][COL];
//
//	int i, j;
//
//	for (i = 0; i<ROW; i++)
//	{
//		for (j = 0; j<COL; j++)
//		{
//			cellDetails[i][j].f = FLT_MAX;
//			cellDetails[i][j].g = FLT_MAX;
//			cellDetails[i][j].h = FLT_MAX;
//			cellDetails[i][j].parent_i = -1;
//			cellDetails[i][j].parent_j = -1;
//		}
//	}
//
//	// Initialising the parameters of the starting node
//	i = src.first, j = src.second;
//	cellDetails[i][j].f = 0.0;
//	cellDetails[i][j].g = 0.0;
//	cellDetails[i][j].h = 0.0;
//	cellDetails[i][j].parent_i = i;
//	cellDetails[i][j].parent_j = j;
//
//	/*
//	Create an open list having information as-
//	<f, <i, j>>
//	where f = g + h,
//	and i, j are the row and column index of that cell
//	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
//	This open list is implenented as a set of pair of pair.*/
//	set<pPair> openList;
//
//	// Put the starting cell on the open list and set its
//	// 'f' as 0
//	openList.insert(make_pair(0.0, make_pair(i, j)));
//
//	// We set this boolean value as false as initially
//	// the destination is not reached.
//	bool foundDest = false;
//
//	while (!openList.empty())
//	{
//		pPair p = *openList.begin();
//
//		// Remove this vertex from the open list
//		openList.erase(openList.begin());
//
//		// Add this vertex to the closed list
//		i = p.second.first;
//		j = p.second.second;
//		closedList[i][j] = true;
//
//		/*
//		Generating all the 8 successor of this cell
//
//		N.W   N   N.E
//		\   |   /
//		\  |  /
//		W----Cell----E
//		/ | \
//		/   |  \
//		S.W    S   S.E
//
//		Cell-->Popped Cell (i, j)
//		N -->  North       (i-1, j)
//		S -->  South       (i+1, j)
//		E -->  East        (i, j+1)
//		W -->  West           (i, j-1)
//		N.E--> North-East  (i-1, j+1)
//		N.W--> North-West  (i-1, j-1)
//		S.E--> South-East  (i+1, j+1)
//		S.W--> South-West  (i+1, j-1)*/
//
//		// To store the 'g', 'h' and 'f' of the 8 successors
//		double gNew, hNew, fNew;
//
//		//----------- 1st Successor (North) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i - 1, j) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i - 1, j, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i - 1][j].parent_i = i;
//				cellDetails[i - 1][j].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i - 1][j] == false &&
//				isUnBlocked(grid, i - 1, j) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.0;
//				hNew = calculateHValue(i - 1, j, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i - 1][j].f == FLT_MAX ||
//					cellDetails[i - 1][j].f > fNew)
//				{
//					openList.insert(make_pair(fNew,
//						make_pair(i - 1, j)));
//
//					// Update the details of this cell
//					cellDetails[i - 1][j].f = fNew;
//					cellDetails[i - 1][j].g = gNew;
//					cellDetails[i - 1][j].h = hNew;
//					cellDetails[i - 1][j].parent_i = i;
//					cellDetails[i - 1][j].parent_j = j;
//				}
//			}
//		}
//
//		//----------- 2nd Successor (South) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i + 1, j) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i + 1, j, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i + 1][j].parent_i = i;
//				cellDetails[i + 1][j].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i + 1][j] == false &&
//				isUnBlocked(grid, i + 1, j) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.0;
//				hNew = calculateHValue(i + 1, j, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i + 1][j].f == FLT_MAX ||
//					cellDetails[i + 1][j].f > fNew)
//				{
//					openList.insert(make_pair(fNew, make_pair(i + 1, j)));
//					// Update the details of this cell
//					cellDetails[i + 1][j].f = fNew;
//					cellDetails[i + 1][j].g = gNew;
//					cellDetails[i + 1][j].h = hNew;
//					cellDetails[i + 1][j].parent_i = i;
//					cellDetails[i + 1][j].parent_j = j;
//				}
//			}
//		}
//
//		//----------- 3rd Successor (East) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i, j + 1) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i, j + 1, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i][j + 1].parent_i = i;
//				cellDetails[i][j + 1].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i][j + 1] == false &&
//				isUnBlocked(grid, i, j + 1) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.0;
//				hNew = calculateHValue(i, j + 1, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i][j + 1].f == FLT_MAX ||
//					cellDetails[i][j + 1].f > fNew)
//				{
//					openList.insert(make_pair(fNew,
//						make_pair(i, j + 1)));
//
//					// Update the details of this cell
//					cellDetails[i][j + 1].f = fNew;
//					cellDetails[i][j + 1].g = gNew;
//					cellDetails[i][j + 1].h = hNew;
//					cellDetails[i][j + 1].parent_i = i;
//					cellDetails[i][j + 1].parent_j = j;
//				}
//			}
//		}
//
//		//----------- 4th Successor (West) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i, j - 1) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i, j - 1, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i][j - 1].parent_i = i;
//				cellDetails[i][j - 1].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i][j - 1] == false &&
//				isUnBlocked(grid, i, j - 1) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.0;
//				hNew = calculateHValue(i, j - 1, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i][j - 1].f == FLT_MAX ||
//					cellDetails[i][j - 1].f > fNew)
//				{
//					openList.insert(make_pair(fNew,
//						make_pair(i, j - 1)));
//
//					// Update the details of this cell
//					cellDetails[i][j - 1].f = fNew;
//					cellDetails[i][j - 1].g = gNew;
//					cellDetails[i][j - 1].h = hNew;
//					cellDetails[i][j - 1].parent_i = i;
//					cellDetails[i][j - 1].parent_j = j;
//				}
//			}
//		}
//
//		//----------- 5th Successor (North-East) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i - 1, j + 1) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i - 1, j + 1, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i - 1][j + 1].parent_i = i;
//				cellDetails[i - 1][j + 1].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i - 1][j + 1] == false &&
//				isUnBlocked(grid, i - 1, j + 1) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.414;
//				hNew = calculateHValue(i - 1, j + 1, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
//					cellDetails[i - 1][j + 1].f > fNew)
//				{
//					openList.insert(make_pair(fNew,
//						make_pair(i - 1, j + 1)));
//
//					// Update the details of this cell
//					cellDetails[i - 1][j + 1].f = fNew;
//					cellDetails[i - 1][j + 1].g = gNew;
//					cellDetails[i - 1][j + 1].h = hNew;
//					cellDetails[i - 1][j + 1].parent_i = i;
//					cellDetails[i - 1][j + 1].parent_j = j;
//				}
//			}
//		}
//
//		//----------- 6th Successor (North-West) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i - 1, j - 1) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i - 1, j - 1, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i - 1][j - 1].parent_i = i;
//				cellDetails[i - 1][j - 1].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i - 1][j - 1] == false &&
//				isUnBlocked(grid, i - 1, j - 1) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.414;
//				hNew = calculateHValue(i - 1, j - 1, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
//					cellDetails[i - 1][j - 1].f > fNew)
//				{
//					openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
//					// Update the details of this cell
//					cellDetails[i - 1][j - 1].f = fNew;
//					cellDetails[i - 1][j - 1].g = gNew;
//					cellDetails[i - 1][j - 1].h = hNew;
//					cellDetails[i - 1][j - 1].parent_i = i;
//					cellDetails[i - 1][j - 1].parent_j = j;
//				}
//			}
//		}
//
//		//----------- 7th Successor (South-East) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i + 1, j + 1) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i + 1, j + 1, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i + 1][j + 1].parent_i = i;
//				cellDetails[i + 1][j + 1].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i + 1][j + 1] == false &&
//				isUnBlocked(grid, i + 1, j + 1) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.414;
//				hNew = calculateHValue(i + 1, j + 1, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
//					cellDetails[i + 1][j + 1].f > fNew)
//				{
//					openList.insert(make_pair(fNew,
//						make_pair(i + 1, j + 1)));
//
//					// Update the details of this cell
//					cellDetails[i + 1][j + 1].f = fNew;
//					cellDetails[i + 1][j + 1].g = gNew;
//					cellDetails[i + 1][j + 1].h = hNew;
//					cellDetails[i + 1][j + 1].parent_i = i;
//					cellDetails[i + 1][j + 1].parent_j = j;
//				}
//			}
//		}
//
//		//----------- 8th Successor (South-West) ------------
//
//		// Only process this cell if this is a valid one
//		if (isValid(i + 1, j - 1) == true)
//		{
//			// If the destination cell is the same as the
//			// current successor
//			if (isDestination(i + 1, j - 1, dest) == true)
//			{
//				// Set the Parent of the destination cell
//				cellDetails[i + 1][j - 1].parent_i = i;
//				cellDetails[i + 1][j - 1].parent_j = j;
//				printf("The destination cell is found\n");
//				tracePath(cellDetails, dest);
//				foundDest = true;
//				return;
//			}
//
//			// If the successor is already on the closed
//			// list or if it is blocked, then ignore it.
//			// Else do the following
//			else if (closedList[i + 1][j - 1] == false &&
//				isUnBlocked(grid, i + 1, j - 1) == true)
//			{
//				gNew = cellDetails[i][j].g + 1.414;
//				hNew = calculateHValue(i + 1, j - 1, dest);
//				fNew = gNew + hNew;
//
//				// If it isn’t on the open list, add it to
//				// the open list. Make the current square
//				// the parent of this square. Record the
//				// f, g, and h costs of the square cell
//				//                OR
//				// If it is on the open list already, check
//				// to see if this path to that square is better,
//				// using 'f' cost as the measure.
//				if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
//					cellDetails[i + 1][j - 1].f > fNew)
//				{
//					openList.insert(make_pair(fNew,
//						make_pair(i + 1, j - 1)));
//
//					// Update the details of this cell
//					cellDetails[i + 1][j - 1].f = fNew;
//					cellDetails[i + 1][j - 1].g = gNew;
//					cellDetails[i + 1][j - 1].h = hNew;
//					cellDetails[i + 1][j - 1].parent_i = i;
//					cellDetails[i + 1][j - 1].parent_j = j;
//				}
//			}
//		}
//	}
//
//	// When the destination cell is not found and the open
//	// list is empty, then we conclude that we failed to
//	// reach the destiantion cell. This may happen when the
//	// there is no way to destination cell (due to blockages)
//	if (foundDest == false)
//		printf("Failed to find the Destination Cell\n");
//
//	return;
//}
//
//
//// Driver program to test above function
//int main()
//{
//	/* Description of the Grid-
//	1--> The cell is not blocked
//	0--> The cell is blocked    */
//	int grid[ROW][COL] =
//	{
//		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
//	{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
//	{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
//	{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
//	{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
//	{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
//	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
//	{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
//	{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
//	};
//
//	// Source is the left-most bottom-most corner
//	Pair src = make_pair(8, 0);
//
//	// Destination is the left-most top-most corner
//	Pair dest = make_pair(0, 0);
//
//	aStarSearch(grid, src, dest);
//	cin.get();
//	return(0);
//}