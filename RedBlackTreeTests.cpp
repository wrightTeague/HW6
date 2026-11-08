
#include <iostream>
#include <cassert>
#include <random>
#include <stdexcept>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// Mirror images of the three cases above.
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(60); // Right Right
	assert(rbt->ToPrefixString() == " B45  R30  R60 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(35); // Left Right
	assert(rbt->ToPrefixString() == " B35  R30  R45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(15); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	// The fourth node always lands under a red parent with a red uncle, so the
	// fix-up only recolors and the root stays the same.
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	assert(rbt->ToPrefixString() == " B30  B15  R10  B45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(20);
	assert(rbt->ToPrefixString() == " B30  B15  R20  B45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(50);
	assert(rbt->ToPrefixString() == " B30  B15  B45  R50 ");
	delete rbt;

	// Starts from the LL case, so 15 is the root before the fourth insert.
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(5);
	assert(rbt->ToPrefixString() == " B15  B10  R5  B30 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	// Black uncle (an empty spot) this time, so it rotates instead of recoloring.
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(5);
	assert(rbt->ToPrefixString() == " B30  B10  R5  R15  B45 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());
	assert(rbt2.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");
	assert(rbt2.Size() == 6);
	assert(rbt1.Size() == 7);
	assert(rbt2.Contains(200) == false);

	// Changes to the copy must not reach the original either.
	rbt2.Insert(1);
	assert(rbt1.Contains(1) == false);

	RedBlackTree empty = RedBlackTree();
	RedBlackTree emptyCopy = RedBlackTree(empty);
	assert(emptyCopy.ToPrefixString() == "");
	assert(emptyCopy.Size() == 0);
	emptyCopy.Insert(5);
	assert(empty.Size() == 0);

	// Assignment replaces the old nodes instead of sharing them.
	RedBlackTree assigned = RedBlackTree(99);
	assigned = rbt1;
	assert(assigned.ToPrefixString() == rbt1.ToPrefixString());
	assert(assigned.Contains(99) == false);
	rbt1.Insert(300);
	assert(assigned.Contains(300) == false);
	// Going through a reference so the compiler doesn't flag the self-assignment.
	RedBlackTree& same = assigned;
	assigned = same;
	assert(assigned.Size() == 7);
	assert(assigned.Contains(200));

	cout << "PASSED!" << endl << endl;
}






void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	assert(rbt->Contains(40));
	assert(rbt->Contains(12));
	assert(rbt->Contains(29));
	assert(rbt->Contains(55));
	assert(rbt->Contains(30) == false);
	assert(rbt->Contains(0) == false);
	assert(rbt->Contains(100) == false);
	delete rbt;

	rbt = new RedBlackTree(7);
	assert(rbt->Contains(7));
	assert(rbt->Contains(8) == false);
	delete rbt;

	cout << "PASSED!" << endl << endl;
}




void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree empty = RedBlackTree();
	try {
		empty.GetMin();
		assert(false);
	} catch (const invalid_argument& e) {}
	try {
		empty.GetMax();
		assert(false);
	} catch (const invalid_argument& e) {}

	RedBlackTree single = RedBlackTree(5);
	assert(single.GetMin() == 5);
	assert(single.GetMax() == 5);

	// After balancing, 5 ends up two levels below the root, not a direct child.
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);
	assert(rbt.GetMin() == 5);
	assert(rbt.GetMax() == 15);

	RedBlackTree negatives = RedBlackTree();
	negatives.Insert(-3);
	negatives.Insert(-10);
	negatives.Insert(4);
	assert(negatives.GetMin() == -10);
	assert(negatives.GetMax() == 4);

	cout << "PASSED!" << endl << endl;
}

void TestDuplicateInsert(){
	cout << "Testing Duplicate Insert..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(10);
	rbt.Insert(5);
	rbt.Insert(15);
	string before = rbt.ToPrefixString();

	try {
		rbt.Insert(10);
		assert(false);
	} catch (const invalid_argument& e) {}
	// A duplicate deeper than the root is caught too, not just at the root.
	try {
		rbt.Insert(15);
		assert(false);
	} catch (const invalid_argument& e) {}
	assert(rbt.ToPrefixString() == before);

	try {
		RedBlackTree single = RedBlackTree(4);
		single.Insert(4);
		assert(false);
	} catch (const invalid_argument& e) {}

	cout << "PASSED!" << endl << endl;
}

void TestLargeTree(){
	cout << "Testing Large Tree..." << endl;

	// Sorted input is the worst case for a plain BST (it becomes a linked
	// list), so it's a good check that balancing keeps working.
	RedBlackTree rbt = RedBlackTree();
	for (int i = 1; i <= 5000; i++) {
		rbt.Insert(i);
	}
	assert(rbt.Size() == 5000);
	assert(rbt.GetMin() == 1);
	assert(rbt.GetMax() == 5000);
	for (int i = 1; i <= 5000; i++) {
		assert(rbt.Contains(i));
	}
	assert(rbt.Contains(0) == false);
	assert(rbt.Contains(5001) == false);

	RedBlackTree copy = RedBlackTree(rbt);
	assert(copy.ToInfixString() == rbt.ToInfixString());

	cout << "PASSED!" << endl << endl;
}

void TestPrivateMethods(){
	RedBlackTree rbt = RedBlackTree();
	rbt.PrivateTests();
}

void TestSize(){
	cout << "Testing Size..." << endl;

	RedBlackTree rbt = RedBlackTree();
	assert(rbt.Size() == 0);
	rbt.Insert(10);
	assert(rbt.Size() == 1);
	rbt.Insert(20);
	rbt.Insert(30);
	rbt.Insert(5);
	assert(rbt.Size() == 4);

	// A rejected duplicate must not be counted.
	try {
		rbt.Insert(20);
		assert(false);
	} catch (const invalid_argument& e) {}
	assert(rbt.Size() == 4);

	assert(RedBlackTree(3).Size() == 1);

	cout << "PASSED!" << endl << endl;
}





int main(){

	
	TestSimpleConstructor();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();
	TestSize();
	TestDuplicateInsert();
	TestLargeTree();
	TestPrivateMethods();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
