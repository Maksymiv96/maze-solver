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
#include "opencv2/highgui.hpp"
#include <queue>

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
		/*if (parent == NULL)
			Parent = NULL; else Parent = parent;
		if (Parent != NULL) DistFromBegin = Parent->DistFromBegin + 1;
		else*/ DistFromBegin = 0;
		DistToDest = DistanceCalc(Possition, *(destination));
		Total = DistFromBegin + DistToDest;

	}
	bool friend operator< (const Node& Node1, const Node &Node2)
	{
		return Node1.Total >= Node2.Total;
	}
	friend bool operator> (const Node& Node1, const Node &Node2)
	{
		return Node1.Total <= Node2.Total;
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



	cin.get();
}

//vector<cv::Point> PathFinder(cv::Mat maze, cv::Point currentPossition, cv::Point destinationPossition)
cv::Mat PathFinder(cv::Mat maze, cv::Point currentPossition, cv::Point destinationPossition)
{
	vector<cv::Point> Path;
	
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

		//cout << buf.DistFromBegin << " " << buf.DistToDest << " " << buf.Total << endl;
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
		cv::drawMarker(local, buf.Possition, cv::Scalar(255, 255, 255), 0, 3);

	} while (nodes.size() > 0 && buf.Possition != destinationPossition);
	if (buf.Possition == destinationPossition)
	{
		cout << "Visited point" << visitidPoint.size() << endl;
		cout << "Cycle" << nodes.size() << endl;
		cout << "Success" << endl;
	}
	cout << &buf << " " << buf.Possition << " " << buf.Parent << endl;
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










