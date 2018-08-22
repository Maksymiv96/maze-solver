//// A C++ Program to implement A* Search Algorithm

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include "opencv2/core.hpp"
#include <list>
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include <map>
#include "opencv2/highgui.hpp"
#include <queue>

using namespace std;

int DistanceCalc(cv::Point point1, cv::Point point2)
{
	//evclide
	//return int(sqrt(pow(point1.x + point2.x, 2) + pow(point1.y + point2.y, 2)));
	//manhatten
	return int((abs(point1.x - point2.x) + abs(point1.y - point2.y)));
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
		if (parent == NULL)
			Parent = NULL; else Parent = parent;
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

bool CheckPossitionForMoving(cv::Mat *image, cv::Point possition)
{
	//255 - white(no) ; 0 - black - can
	if (cv::Scalar(image->at<uchar>(possition)).val[0] == 0)return true;
	else return false;
}

bool CheckIfCanVisit(vector<cv::Point> *visited, cv::Point PossitionToCheck)
{
	return !(std::find(visited->begin(), visited->end(), PossitionToCheck) != visited->end());

}

void CheckNeighbor(cv::Mat *image, Node *node, cv::Point *destination, priority_queue<Node, vector<Node>, less<vector<Node>::value_type>> *nodes, vector<cv::Point> *visited)
{

	//cout << node->Possition << " " << CheckPossitionForMoving(image,node->Possition) << endl;
	cv::Point right(node->Possition.x + 1, node->Possition.y);
	cv::Point left(node->Possition.x - 1, node->Possition.y);
	cv::Point top(node->Possition.x, node->Possition.y - 1);
	cv::Point down(node->Possition.x, node->Possition.y + 1);

	if (CheckPossitionForMoving(image, left) && CheckIfCanVisit(visited, left))
	{
		nodes->push(Node(left, destination, new Node(*node)));
		visited->push_back(left);
	}
	if (CheckPossitionForMoving(image, right) && CheckIfCanVisit(visited, right))
	{
		nodes->push(Node(right, destination, new Node(*node)));
		visited->push_back(right);
	}
	if (CheckPossitionForMoving(image, top) && CheckIfCanVisit(visited, top))
	{
		nodes->push(Node(top, destination, new Node(*node)));
		visited->push_back(top);
	}
	if (CheckPossitionForMoving(image, down) && CheckIfCanVisit(visited, down))
	{
		nodes->push(Node(down, destination, new Node(*node)));
		visited->push_back(down);
	}

	//if you wanna move on all 8 direction uncomment next code;

	//cv::Point sw(node->Possition.x - 1, node->Possition.y+1);
	//cv::Point se(node->Possition.x + 1, node->Possition.y+1);
	//cv::Point nw(node->Possition.x-1, node->Possition.y - 1);
	//cv::Point ne(node->Possition.x+1, node->Possition.y - 1);



	//if (CheckPossitionForMoving(image, ne) && CheckIfCanVisit(visited, ne))
	//{
	//	nodes->push(Node(ne, destination, new Node(*node)));
	//	visited->push_back(ne);
	//}
	//if (CheckPossitionForMoving(image, nw) && CheckIfCanVisit(visited, nw))
	//{
	//	nodes->push(Node(nw, destination, new Node(*node)));
	//	visited->push_back(nw);
	//}
	//if (CheckPossitionForMoving(image, sw) && CheckIfCanVisit(visited, sw))
	//{
	//	nodes->push(Node(sw, destination, new Node(*node)));
	//	visited->push_back(sw);
	//}
	//if (CheckPossitionForMoving(image, se) && CheckIfCanVisit(visited, se))
	//{
	//	nodes->push(Node(se, destination, new Node(*node)));
	//	visited->push_back(se);
	//}


}

void CheckNeighborSecondImpl(cv::Mat *image, Node *node, cv::Point *destination, priority_queue<Node, vector<Node>, less<vector<Node>::value_type>> *nodes, vector<cv::Point> *visited)
{

	//cout << node->Possition << " " << CheckPossitionForMoving(image,node->Possition) << endl;
	cv::Point right(node->Possition.x + 1, node->Possition.y);
	cv::Point left(node->Possition.x - 1, node->Possition.y);
	cv::Point top(node->Possition.x, node->Possition.y - 1);
	cv::Point down(node->Possition.x, node->Possition.y + 1);

	if (CheckPossitionForMoving(image, left))
	{
		nodes->push(Node(left, destination, new Node(*node)));
		cv::drawMarker(*image, left, cv::Scalar(255, 255, 255), 0, 1);
	}
	if (CheckPossitionForMoving(image, right))
	{
		nodes->push(Node(right, destination, new Node(*node)));
		cv::drawMarker(*image, right, cv::Scalar(255, 255, 255), 0, 1);
	}
	if (CheckPossitionForMoving(image, top))
	{
		nodes->push(Node(top, destination, new Node(*node)));
		cv::drawMarker(*image, top, cv::Scalar(255, 255, 255), 0, 1);
	}
	if (CheckPossitionForMoving(image, down))
	{
		nodes->push(Node(down, destination, new Node(*node)));
		cv::drawMarker(*image, down, cv::Scalar(255, 255, 255), 0, 1);
	}

	//if you wanna move on all 8 direction uncomment next code;

	//cv::Point sw(node->Possition.x - 1, node->Possition.y+1);
	//cv::Point se(node->Possition.x + 1, node->Possition.y+1);
	//cv::Point nw(node->Possition.x-1, node->Possition.y - 1);
	//cv::Point ne(node->Possition.x+1, node->Possition.y - 1);



	//if (CheckPossitionForMoving(image, ne) && CheckIfCanVisit(visited, ne))
	//{
	//	nodes->push(Node(ne, destination, new Node(*node)));
	//	cv::drawMarker(*image, ne, cv::Scalar(255, 255, 255), 0, 1);
	//}
	//if (CheckPossitionForMoving(image, nw) && CheckIfCanVisit(visited, nw))
	//{
	//	nodes->push(Node(nw, destination, new Node(*node)));
	//	cv::drawMarker(*image, nw, cv::Scalar(255, 255, 255), 0, 1);
	//}
	//if (CheckPossitionForMoving(image, sw) && CheckIfCanVisit(visited, sw))
	//{
	//	nodes->push(Node(sw, destination, new Node(*node)));
	//	cv::drawMarker(*image, sw, cv::Scalar(255, 255, 255), 0, 1);
	//}
	//if (CheckPossitionForMoving(image, se) && CheckIfCanVisit(visited, se))
	//{
	//	nodes->push(Node(se, destination, new Node(*node)));
	//	cv::drawMarker(*image, se, cv::Scalar(255, 255, 255), 0, 1);
	//}


}

//vector<cv::Point> PathFinder(cv::Mat maze, cv::Point currentPossition, cv::Point destinationPossition)
cv::Mat PathFinder(cv::Mat *maze, cv::Point currentPossition, cv::Point destinationPossition)
{
	vector<cv::Point> Path;
	
	priority_queue<Node, vector<Node>, less<vector<Node>::value_type>> nodes;
	nodes.push(Node(currentPossition, &destinationPossition, NULL));
	vector<cv::Point> visitidPoint;
	cv::Mat local;
	maze->copyTo(local);
	Nod e buf = nodes.top();
	int i = 0;
	//cv::namedWindow("Result");
	
	do {
		buf = nodes.top();
		nodes.pop();

		if (buf.Possition == destinationPossition) cout << "detect" << endl;
		//CheckNeighbor(&local, &buf, &destinationPossition, &nodes, &visitidPoint);
		CheckNeighborSecondImpl(&local, &buf, &destinationPossition, &nodes, &visitidPoint);

		//cv::drawMarker(local, buf.Possition, cv::Scalar(255, 255, 255), 0, 1);

		//if (i % 100 == 0)
		//{
		//	cv::imshow("Result", local);
		//	cv::waitKey();
		//	//i = 0;
		//}
		i++;
		
		

	} while (nodes.size() > 0 && buf.Possition != destinationPossition);
	if (buf.Possition == destinationPossition)
	{
		cout << "Visited point" << visitidPoint.size() << endl;
		cout << "Cycle" << i << endl;
		cout << "Success" << endl;
		cout << "Path built" << endl;
	}
	else cout << "Cant find path" << endl;
	cout << &buf << " " << buf.Possition << " " << buf.Parent << endl;
	
	maze->copyTo(local);
	cv::cvtColor(local, local, cv::COLOR_GRAY2BGR);
	do
	{
		cv::drawMarker(local, buf.Possition, cv::Scalar(255, 0, 255), 0, 5);
		buf = *buf.Parent;

	} while (buf.Parent != NULL);

	//cv::namedWindow("Result");
	//cv::imshow("Result", local);
	cin.get();
	
	return local;
	//return Path;
}










