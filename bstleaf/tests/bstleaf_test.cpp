//#include "Map.h"
#include "BSTLEAF.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//comparison_for_int_keys==========================
bool compare_int(const int& a, const int& b){
	if(a < b) return true;
	else return false;	
}
//=================================================

//equality_for_int_keys============================
bool equality_int(const int& a, const int& b){
	if(a == b) return true;
	else return false;	
}
//=================================================

TEST_CASE("copy constructor", "[copycons]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> cc;
	cc.insert(26, 'Z');
	cc.insert(3, 'C');
	cc.insert(8, 'H');
	cc.insert(1, 'A');
	cc.insert(5, 'E');
	cc.insert(2, 'B');
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> ccnew(cc);
	REQUIRE(ccnew.inorder_print() == cc.inorder_print());
	const cop3530::BSTLEAF<int,char,*compare_int,*equality_int> constcc(cc); 
	//constcc.remove(1);/*uncomment to throw compiler error cannot modify const tree*/
}

TEST_CASE("copy assignment", "[copyasgmt]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> ca;
	ca.insert(26, 'Z');
	ca.insert(3, 'C');
	ca.insert(8, 'H');
	ca.insert(1, 'A');
	ca.insert(5, 'E');
	ca.insert(2, 'B');
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> ca1;
	ca1.insert(13, 'M');
	ca1.insert(15, 'O');
	ca1.insert(14, 'N');
	REQUIRE(ca.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
	REQUIRE(ca1.inorder_print() == "13M 14N 15O ");
	ca1=ca;
	REQUIRE(ca.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
	REQUIRE(ca1.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
}

TEST_CASE("move constructor", "[moveconst]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> mc;
	mc.insert(19, 'S');
	mc.insert(17, 'Q');
	mc.insert(15, 'O');
	mc.insert(10, 'J');
	mc.insert(2, 'B');
	mc.insert(22, 'V');
	mc.insert(18, 'R');
	mc.insert(20, 'T');
	REQUIRE(mc.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> movedmc(std::move(mc));
	REQUIRE(movedmc.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	REQUIRE(mc.inorder_print() == "<empty tree>");
}

TEST_CASE("move assignment", "[moveasmgt]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> ma;
	ma.insert(19, 'S');
	ma.insert(17, 'Q');
	ma.insert(15, 'O');
	ma.insert(10, 'J');
	ma.insert(2, 'B');
	ma.insert(22, 'V');
	ma.insert(18, 'R');
	ma.insert(20, 'T');
	REQUIRE(ma.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> ma1;
	ma1.insert(26, 'Z');
	ma1.insert(3, 'C');
	ma1.insert(8, 'H');
	ma1.insert(1, 'A');
	ma1.insert(5, 'E');
	ma1.insert(2, 'B');
	REQUIRE(ma1.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
	ma = std::move(ma1);
	REQUIRE(ma.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
	REQUIRE(ma1.inorder_print() == "<empty tree>");
}

TEST_CASE("testing insert by checking if it matches to desired inorder_print", "[insert_to_iop]"){
	//std::cout << "==========TEST1==========" << std::endl;	
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1;
	test1.insert(5, 'E');
	test1.insert(2, 'B');
	REQUIRE(test1.inorder_print() == "2B 5E ");
	test1.insert(26, 'Z');
	test1.insert(3, 'C');
	test1.insert(8, 'H');
	test1.insert(1, 'A');
	REQUIRE(test1.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
	//testing remove(5)
	test1.remove(5);
	REQUIRE(test1.inorder_print() == "1A 2B 3C 8H 26Z ");
	//testing remove(26)
	test1.remove(26);
	REQUIRE(test1.inorder_print() == "1A 2B 3C 8H ");
	//updating a value by inserting a same key with different value
	test1.insert(1, 'Z');
	REQUIRE(test1.inorder_print() == "1Z 2B 3C 8H ");
}

TEST_CASE("testing remove on various trees", "[remove]"){
	//std::cout << "==========TEST2==========" << std::endl;
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test2a;
	test2a.insert(20, 'T');test2a.insert(26, 'Z');test2a.insert(25, 'Y');test2a.insert(23, 'W');test2a.insert(24, 'X');
	test2a.insert(22, 'V');test2a.insert(21, 'U');test2a.insert(2, 'B');
	REQUIRE(test2a.inorder_print() == "2B 20T 21U 22V 23W 24X 25Y 26Z ");
	//testing remove(23)
	test2a.remove(23);
	REQUIRE(test2a.inorder_print() == "2B 20T 21U 22V 24X 25Y 26Z ");
	test2a.remove(24);
	REQUIRE(test2a.inorder_print() == "2B 20T 21U 22V 25Y 26Z ");
	test2a.remove(26);
	REQUIRE(test2a.inorder_print() == "2B 20T 21U 22V 25Y ");
	
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test2b;
	test2b.insert(10, 'J');test2b.insert(7, 'G');test2b.insert(15, 'O');test2b.insert(3, 'C');test2b.insert(6, 'F');
	test2b.insert(5, 'E');test2b.insert(2, 'B');test2b.insert(4, 'D');test2b.insert(1, 'A');
	REQUIRE(test2b.inorder_print() == "1A 2B 3C 4D 5E 6F 7G 10J 15O ");
	test2b.remove(7);
	REQUIRE(test2b.inorder_print() == "1A 2B 3C 4D 5E 6F 10J 15O ");
	test2b.remove(5);
	REQUIRE(test2b.inorder_print() == "1A 2B 3C 4D 6F 10J 15O ");
	test2b.remove(2);
	REQUIRE(test2b.inorder_print() == "1A 3C 4D 6F 10J 15O ");
	test2b.insert(8, 'H');test2b.insert(12, 'L');test2b.insert(5, 'E');
	REQUIRE(test2b.inorder_print() == "1A 3C 4D 5E 6F 8H 10J 12L 15O ");
	test2b.remove(6);
	REQUIRE(test2b.inorder_print() == "1A 3C 4D 5E 8H 10J 12L 15O ");
	test2b.remove(10);
	REQUIRE(test2b.inorder_print() == "1A 3C 4D 5E 8H 12L 15O ");
	REQUIRE_THROWS(test2b.remove(11));
	REQUIRE_THROWS(test2b.remove(10));
	REQUIRE_THROWS(test2b.remove(-7));
}

TEST_CASE("testing lookup", "[lookup]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test3a;
	test3a.insert(10, 'J');test3a.insert(7, 'G');test3a.insert(15, 'O');test3a.insert(3, 'C');test3a.insert(6, 'F');
	test3a.insert(5, 'E');test3a.insert(2, 'B');test3a.insert(4, 'D');test3a.insert(1, 'A');
	test3a.remove(7);
	test3a.remove(5);
	test3a.remove(2);
	test3a.insert(8, 'H');test3a.insert(12, 'L');test3a.insert(5, 'E');
	test3a.remove(6);
	test3a.remove(10);
	REQUIRE(test3a.lookup(1) == 'A');
	REQUIRE(test3a.lookup(3) == 'C');
	REQUIRE(test3a.lookup(4) == 'D');
	REQUIRE(test3a.lookup(5) == 'E');
	REQUIRE(test3a.lookup(8) == 'H');
	REQUIRE(test3a.lookup(12) == 'L');
	REQUIRE(test3a.lookup(15) == 'O');
	test3a.insert(8, 'Z');
	REQUIRE(test3a.lookup(8) == 'Z');
	test3a.insert(3, 'Z');
	REQUIRE(test3a.lookup(3) == 'Z');
	test3a.insert(5, 'Z');
	REQUIRE(test3a.lookup(5) == 'Z');
	REQUIRE_THROWS(test3a.lookup(0));
	REQUIRE_THROWS(test3a.lookup(90));
	REQUIRE_THROWS(test3a.lookup(-2));
}


TEST_CASE("testing contains/size/clear/isempty", "[contains]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1h;
	REQUIRE(test1h.is_empty() == true);
	test1h.insert(15, 'O');
	REQUIRE(test1h.is_empty() == false);
	REQUIRE(test1h.is_full() == false);
	test1h.insert(10, 'J');
	test1h.insert(17, 'Q');	
	test1h.insert(7, 'G');
	test1h.insert(13, 'M');
	test1h.insert(18, 'R');
	test1h.insert(14, 'N');
	REQUIRE(test1h.balance() == 1);	
	REQUIRE(test1h.size() == 7);
	REQUIRE(test1h.height() == 3);
	REQUIRE(test1h.contains(14) == true);
	REQUIRE(test1h.contains(18) == true);
	REQUIRE(test1h.contains(13) == true);
	REQUIRE(test1h.contains(7) == true);
	REQUIRE(test1h.contains(17) == true);
	REQUIRE(test1h.contains(10) == true);
	REQUIRE(test1h.contains(15) == true);
	REQUIRE(test1h.contains(99) == false);
	REQUIRE(test1h.contains(-9) == false);
	test1h.clear();
	REQUIRE(test1h.is_empty() == true);
}

TEST_CASE("testing height", "[height]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1i;
	REQUIRE(test1i.height() == -1);
	test1i.insert(1,'A');
	REQUIRE(test1i.height() == 0);
	test1i.insert(2, 'B');
	REQUIRE(test1i.height() == 1);
	test1i.remove(1);
	REQUIRE(test1i.height() == 0);
	test1i.remove(2);
	REQUIRE(test1i.height() == -1);
}

//skip j,k,l,m
TEST_CASE("same as avl remove1f", "[remove1n]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1n;
	test1n.insert(22, 'V');
	test1n.insert(18, 'R');
	test1n.insert(20, 'T');
	test1n.insert(19, 'S');
	test1n.insert(17, 'Q');
	test1n.insert(15, 'O');
	test1n.insert(10, 'J');
	test1n.insert(2, 'B');
	test1n.remove(10);
	REQUIRE(test1n.inorder_print() == "2B 15O 17Q 18R 19S 20T 22V ");
	test1n.remove(20);
	REQUIRE(test1n.inorder_print() == "2B 15O 17Q 18R 19S 22V ");
}

TEST_CASE("same as avl remove1g", "[remove1o]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1o;
	test1o.insert(26, 'Z');
	test1o.insert(5, 'E');
	test1o.insert(20, 'T');
	test1o.insert(13, 'M');
	test1o.insert(7, 'G');
	test1o.insert(14, 'N');
	test1o.remove(7);
	REQUIRE(test1o.inorder_print() == "5E 13M 14N 20T 26Z ");
	test1o.remove(14);
	REQUIRE(test1o.inorder_print() == "5E 13M 20T 26Z ");
	test1o.remove(26);
	REQUIRE(test1o.inorder_print() == "5E 13M 20T ");
}

TEST_CASE("same as avl remRR", "[remove1p]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1p;
	test1p.insert(5, 'E');
	test1p.insert(3, 'C');
	test1p.insert(10, 'J');
	test1p.insert(2, 'B');
	test1p.insert(7, 'G');
	test1p.insert(13, 'M');
	test1p.insert(12, 'L');
	test1p.remove(2);
	REQUIRE(test1p.inorder_print() == "3C 5E 7G 10J 12L 13M ");
}

TEST_CASE("same as avl remRL", "[remove1q]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1q;
	test1q.insert(5, 'E');
	test1q.insert(3, 'C');
	test1q.insert(10, 'J');
	test1q.insert(2, 'B');
	test1q.insert(7, 'G');
	test1q.insert(13, 'M');
	test1q.insert(9, 'I');
	test1q.remove(2);
	REQUIRE(test1q.inorder_print() == "3C 5E 7G 9I 10J 13M ");
}

TEST_CASE("same as avl remLL", "[remove1r]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1r;
	test1r.insert(15, 'O');
	test1r.insert(10, 'J');
	test1r.insert(17, 'Q');	
	test1r.insert(7, 'G');
	test1r.insert(13, 'M');
	test1r.insert(18, 'R');
	test1r.insert(9, 'I');
	test1r.remove(18);
	REQUIRE(test1r.inorder_print() == "7G 9I 10J 13M 15O 17Q ");
}

TEST_CASE("same as avl remLR", "[remLR]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1s;
	test1s.insert(15, 'O');
	test1s.insert(10, 'J');
	test1s.insert(17, 'Q');	
	test1s.insert(7, 'G');
	test1s.insert(13, 'M');
	test1s.insert(18, 'R');
	test1s.insert(14, 'N');
	test1s.remove(18);
	REQUIRE(test1s.size() == 6);
	REQUIRE(test1s.inorder_print() == "7G 10J 13M 14N 15O 17Q ");
}

TEST_CASE("testing is_empty", "[empty]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> test1t;
	REQUIRE_THROWS(test1t.remove(1));
	test1t.insert(1, 'A');
	REQUIRE(test1t.is_empty() == false);
	test1t.remove(1);
	REQUIRE(test1t.is_empty() == true);
	REQUIRE(test1t.is_full() == false);
	REQUIRE(test1t.size() == 0);
	REQUIRE_THROWS(test1t.remove(1));
}

TEST_CASE("github", "[github]"){
	cop3530::BSTLEAF<int,char,*compare_int,*equality_int> git;
	REQUIRE(git.contains(9) == false);
    REQUIRE(git.is_empty() == true);
    REQUIRE(git.is_full() == false);
    size_t size = git.size();
	REQUIRE(size == 0);
    git.clear();
    REQUIRE( git.height() == -1);
    REQUIRE( git.balance() == 0);
}
