//#include "Map.h"
#include "BSTRAND.h"
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> cc;
	cc.insert(26, 'Z');
	cc.insert(3, 'C');
	cc.insert(8, 'H');
	cc.insert(1, 'A');
	cc.insert(5, 'E');
	cc.insert(2, 'B');
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> ccnew(cc);
	REQUIRE(ccnew.inorder_print() == cc.inorder_print());
	const cop3530::BSTRAND<int,char,*compare_int,*equality_int> constcc(cc); 
	//constcc.remove(1);/*uncomment to throw compiler error cannot modify const tree*/
}

TEST_CASE("copy assignment", "[copyasgmt]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> ca;
	ca.insert(26, 'Z');
	ca.insert(3, 'C');
	ca.insert(8, 'H');
	ca.insert(1, 'A');
	ca.insert(5, 'E');
	ca.insert(2, 'B');
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> ca1;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> mc;
	mc.insert(19, 'S');
	mc.insert(17, 'Q');
	mc.insert(15, 'O');
	mc.insert(10, 'J');
	mc.insert(2, 'B');
	mc.insert(22, 'V');
	mc.insert(18, 'R');
	mc.insert(20, 'T');
	REQUIRE(mc.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> movedmc(std::move(mc));
	REQUIRE(movedmc.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	REQUIRE(mc.inorder_print() == "<empty tree>");
}

TEST_CASE("move assignment", "[moveasmgt]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> ma;
	ma.insert(19, 'S');
	ma.insert(17, 'Q');
	ma.insert(15, 'O');
	ma.insert(10, 'J');
	ma.insert(2, 'B');
	ma.insert(22, 'V');
	ma.insert(18, 'R');
	ma.insert(20, 'T');
	REQUIRE(ma.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> ma1;
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

TEST_CASE("test1", "[insert1]"){	
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1;
	test1.insert(5, 'E');
	test1.insert(2, 'B');
	REQUIRE(test1.inorder_print() == "2B 5E ");
	test1.insert(26, 'Z');
	test1.insert(3, 'C');
	test1.insert(8, 'H');
	test1.insert(1, 'A');
	REQUIRE(test1.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
}


TEST_CASE("test2", "[insert2]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1b;
	test1b.insert(10, 'J');
	test1b.insert(5, 'E');
	REQUIRE(test1b.inorder_print() == "5E 10J ");
	test1b.insert(13, 'M');
	test1b.insert(15, 'O');
	test1b.insert(14, 'N');
	REQUIRE(test1b.inorder_print() == "5E 10J 13M 14N 15O ");
}

TEST_CASE("test3", "[insert3]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1c;
	test1c.insert(2, 'B');
	REQUIRE(test1c.inorder_print() == "2B ");
	test1c.insert(10, 'J');
	REQUIRE(test1c.inorder_print() == "2B 10J ");
	test1c.insert(15, 'O');
	REQUIRE(test1c.inorder_print() == "2B 10J 15O ");
	test1c.insert(17, 'Q');
	REQUIRE(test1c.inorder_print() == "2B 10J 15O 17Q ");
	test1c.insert(19, 'S');
	REQUIRE(test1c.inorder_print() == "2B 10J 15O 17Q 19S ");
	test1c.insert(20, 'T');
	REQUIRE(test1c.inorder_print() == "2B 10J 15O 17Q 19S 20T ");
	test1c.insert(18, 'R');
	REQUIRE(test1c.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T ");
	test1c.insert(22, 'V');
	REQUIRE(test1c.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	
}

TEST_CASE("test4", "[insert4]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1d;
	test1d.insert(26, 'Z');
	REQUIRE(test1d.inorder_print() == "26Z ");
	test1d.insert(5, 'E');
	REQUIRE(test1d.inorder_print() == "5E 26Z ");
	test1d.insert(20, 'T');
	REQUIRE(test1d.inorder_print() == "5E 20T 26Z ");
	test1d.insert(13, 'M');
	REQUIRE(test1d.inorder_print() == "5E 13M 20T 26Z ");
	test1d.insert(7, 'G');
	REQUIRE(test1d.inorder_print() == "5E 7G 13M 20T 26Z ");
	test1d.insert(14, 'N');
	REQUIRE(test1d.inorder_print() == "5E 7G 13M 14N 20T 26Z ");
}

TEST_CASE("test5", "[insert5]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1e;
	test1e.insert(22, 'V');
	REQUIRE(test1e.inorder_print() == "22V ");
	test1e.insert(18, 'R');
	REQUIRE(test1e.inorder_print() == "18R 22V ");
	test1e.insert(20, 'T');
	REQUIRE(test1e.inorder_print() == "18R 20T 22V ");
	test1e.insert(19, 'S');
	REQUIRE(test1e.inorder_print() == "18R 19S 20T 22V ");
	test1e.insert(17, 'Q');
	REQUIRE(test1e.inorder_print() == "17Q 18R 19S 20T 22V ");
	test1e.insert(15, 'O');
	REQUIRE(test1e.inorder_print() == "15O 17Q 18R 19S 20T 22V ");
	test1e.insert(10, 'J');
	REQUIRE(test1e.inorder_print() == "10J 15O 17Q 18R 19S 20T 22V ");
	test1e.insert(2, 'B');
	REQUIRE(test1e.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	
}

TEST_CASE("test6", "[remove6]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1f;
	test1f.insert(22, 'V');
	test1f.insert(18, 'R');
	test1f.insert(20, 'T');
	test1f.insert(19, 'S');
	test1f.insert(17, 'Q');
	test1f.insert(15, 'O');
	test1f.insert(10, 'J');
	test1f.insert(2, 'B');
	test1f.remove(10);
	REQUIRE(test1f.inorder_print() == "2B 15O 17Q 18R 19S 20T 22V ");
	test1f.remove(20);
	REQUIRE(test1f.inorder_print() == "2B 15O 17Q 18R 19S 22V ");
}

TEST_CASE("test7", "[remove7]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1g;
	test1g.insert(26, 'Z');
	test1g.insert(5, 'E');
	test1g.insert(20, 'T');
	test1g.insert(13, 'M');
	test1g.insert(7, 'G');
	test1g.insert(14, 'N');
	test1g.remove(7);
	REQUIRE(test1g.inorder_print() == "5E 13M 14N 20T 26Z ");
	test1g.remove(14);
	REQUIRE(test1g.inorder_print() == "5E 13M 20T 26Z ");
	test1g.remove(26);
	REQUIRE(test1g.inorder_print() == "5E 13M 20T ");
}

TEST_CASE("test8", "[lookup8]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1g;
	test1g.insert(26, 'Z');
	test1g.insert(5, 'E');
	test1g.insert(20, 'T');
	test1g.insert(13, 'M');
	test1g.insert(7, 'G');
	test1g.insert(14, 'N');
	REQUIRE(test1g.lookup(14) == 'N');
	REQUIRE(test1g.lookup(7) == 'G');
	REQUIRE(test1g.lookup(20) == 'T');
	REQUIRE(test1g.lookup(26) == 'Z');
	REQUIRE_THROWS(test1g.lookup(99));
	REQUIRE_THROWS(test1g.lookup(-9));
}

TEST_CASE("testing contains/size/clear/isempty", "[contains]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1h;
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
	//REQUIRE(test1h.height() == 4);
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

TEST_CASE("same as RL", "[sameRL]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1i;
	test1i.insert(10, 'J');
	test1i.insert(5, 'E');
	REQUIRE(test1i.inorder_print() == "5E 10J ");
	test1i.insert(13, 'M');
	test1i.insert(15, 'O');
	test1i.insert(14, 'N');
	REQUIRE(test1i.inorder_print() == "5E 10J 13M 14N 15O ");
}

TEST_CASE("same as RR", "[sameRR]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1j;
	test1j.insert(2, 'B');
	REQUIRE(test1j.inorder_print() == "2B ");
	test1j.insert(10, 'J');
	REQUIRE(test1j.inorder_print() == "2B 10J ");
	test1j.insert(15, 'O');
	REQUIRE(test1j.inorder_print() == "2B 10J 15O ");
	test1j.insert(17, 'Q');
	REQUIRE(test1j.inorder_print() == "2B 10J 15O 17Q ");
	test1j.insert(19, 'S');
	REQUIRE(test1j.inorder_print() == "2B 10J 15O 17Q 19S ");
	test1j.insert(20, 'T');
	REQUIRE(test1j.inorder_print() == "2B 10J 15O 17Q 19S 20T ");
	test1j.insert(18, 'R');
	REQUIRE(test1j.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T ");
	test1j.insert(22, 'V');
	REQUIRE(test1j.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
}

TEST_CASE("same as LR", "[sameLR]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1k;
	test1k.insert(26, 'Z');
	REQUIRE(test1k.inorder_print() == "26Z ");
	test1k.insert(5, 'E');
	REQUIRE(test1k.inorder_print() == "5E 26Z ");
	test1k.insert(20, 'T');
	REQUIRE(test1k.inorder_print() == "5E 20T 26Z ");
	test1k.insert(13, 'M');
	REQUIRE(test1k.inorder_print() == "5E 13M 20T 26Z ");
	test1k.insert(7, 'G');
	REQUIRE(test1k.inorder_print() == "5E 7G 13M 20T 26Z ");
	test1k.insert(14, 'N');
	REQUIRE(test1k.inorder_print() == "5E 7G 13M 14N 20T 26Z ");
}

TEST_CASE("same as LL", "[sameLL]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1l;
	test1l.insert(22, 'V');
	REQUIRE(test1l.inorder_print() == "22V ");
	test1l.insert(18, 'R');
	REQUIRE(test1l.inorder_print() == "18R 22V ");
	test1l.insert(20, 'T');
	REQUIRE(test1l.inorder_print() == "18R 20T 22V ");
	test1l.insert(19, 'S');
	REQUIRE(test1l.inorder_print() == "18R 19S 20T 22V ");
	test1l.insert(17, 'Q');
	REQUIRE(test1l.inorder_print() == "17Q 18R 19S 20T 22V ");
	test1l.insert(15, 'O');
	REQUIRE(test1l.inorder_print() == "15O 17Q 18R 19S 20T 22V ");
	test1l.insert(10, 'J');
	REQUIRE(test1l.inorder_print() == "10J 15O 17Q 18R 19S 20T 22V ");
	test1l.insert(2, 'B');
	REQUIRE(test1l.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
}


TEST_CASE("testing height", "[height]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1m;
	REQUIRE(test1m.height() == -1);
	test1m.insert(1,'A');
	REQUIRE(test1m.height() == 0);
	test1m.insert(2, 'B');
	REQUIRE(test1m.height() == 1);
	test1m.remove(1);
	REQUIRE(test1m.height() == 0);
	test1m.remove(2);
	REQUIRE(test1m.height() == -1);
}

TEST_CASE("same as avl remove1f", "[remove1n]"){
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1n;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1o;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1p;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1q;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1r;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1s;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> test1t;
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
	cop3530::BSTRAND<int,char,*compare_int,*equality_int> git;
	REQUIRE(git.contains(9) == false);
    REQUIRE(git.is_empty() == true);
    REQUIRE(git.is_full() == false);
    size_t size = git.size();
	REQUIRE(size == 0);
    git.clear();
    REQUIRE( git.height() == -1);
    REQUIRE( git.balance() == 0);
}
