//#include "Map.h"
#include "AVL.h"
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
	cop3530::AVL<int,char,*compare_int,*equality_int> cc;
	cc.insert(26, 'Z');
	cc.insert(3, 'C');
	cc.insert(8, 'H');
	cc.insert(1, 'A');
	cc.insert(5, 'E');
	cc.insert(2, 'B');
	cop3530::AVL<int,char,*compare_int,*equality_int> ccnew(cc);
	const cop3530::AVL<int,char,*compare_int,*equality_int> constcc(cc);
	//constcc.insert(2, 'B'); /*uncomment to throw compiler error cannot modify const tree*/
	REQUIRE(ccnew.inorder_print() == cc.inorder_print());
	//std::cout << cc.get_bfstr() << std::endl;
}

TEST_CASE("copy assignment", "[copyasgmt]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> ca;
	ca.insert(26, 'Z');
	ca.insert(3, 'C');
	ca.insert(8, 'H');
	ca.insert(1, 'A');
	ca.insert(5, 'E');
	ca.insert(2, 'B');
	cop3530::AVL<int,char,*compare_int,*equality_int> ca1;
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
	cop3530::AVL<int,char,*compare_int,*equality_int> mc;
	mc.insert(19, 'S');
	mc.insert(17, 'Q');
	mc.insert(15, 'O');
	mc.insert(10, 'J');
	mc.insert(2, 'B');
	mc.insert(22, 'V');
	mc.insert(18, 'R');
	mc.insert(20, 'T');
	REQUIRE(mc.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	cop3530::AVL<int,char,*compare_int,*equality_int> movedmc(std::move(mc));
	REQUIRE(movedmc.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	REQUIRE(mc.inorder_print() == "<empty tree>");
}

TEST_CASE("move assignment", "[moveasmgt]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> ma;
	ma.insert(19, 'S');
	ma.insert(17, 'Q');
	ma.insert(15, 'O');
	ma.insert(10, 'J');
	ma.insert(2, 'B');
	ma.insert(22, 'V');
	ma.insert(18, 'R');
	ma.insert(20, 'T');
	REQUIRE(ma.inorder_print() == "2B 10J 15O 17Q 18R 19S 20T 22V ");
	cop3530::AVL<int,char,*compare_int,*equality_int> ma1;
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
	REQUIRE(ma1.check_bf() == true);
	REQUIRE(ma.check_bf() == true);
}

TEST_CASE("insert doesnt avl fix", "[insert no fix]"){	
	cop3530::AVL<int,char,*compare_int,*equality_int> test1;
	test1.insert(5, 'E');
	test1.insert(2, 'B');
	REQUIRE(test1.inorder_print() == "2B 5E ");
	test1.insert(26, 'Z');
	test1.insert(3, 'C');
	test1.insert(8, 'H');
	test1.insert(1, 'A');
	REQUIRE(test1.inorder_print() == "1A 2B 3C 5E 8H 26Z ");
	//std::cout << test1.get_bfstr() << std::endl;
	REQUIRE(test1.check_bf() == true);
}

TEST_CASE("insert that uses RL", "[insert RL]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1b;
	test1b.insert(10, 'J');
	test1b.insert(5, 'E');
	REQUIRE(test1b.inorder_print() == "5E 10J ");
	test1b.insert(13, 'M');
	test1b.insert(15, 'O');
	test1b.insert(14, 'N');
	REQUIRE(test1b.inorder_print() == "5E 10J 13M 14N 15O ");
	//std::cout << test1b.get_bfstr() << std::endl;
	REQUIRE(test1b.check_bf() == true);
}

TEST_CASE("insert that uses RR", "[RR]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1c;
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
	//std::cout << test1c.get_bfstr() << std::endl;
	REQUIRE(test1c.check_bf() == true);
}

TEST_CASE("insert that uses LR", "[LR]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1d;
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
	//std::cout << test1d.get_bfstr() << std::endl;
	REQUIRE(test1d.check_bf() == true);
}

TEST_CASE("insert that uses LL", "[LL]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1e;
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
	//std::cout << test1e.get_bfstr() << std::endl;
	REQUIRE(test1e.check_bf() == true);
}

TEST_CASE("testing remove1f", "[remove1f]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1f;
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
	//std::cout << test1f.get_bfstr() << std::endl;
	REQUIRE(test1f.check_bf() == true);
}

TEST_CASE("testing remove1g", "[remove1g]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1g;
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
	//std::cout << test1g.get_bfstr() << std::endl;
	REQUIRE(test1g.check_bf() == true);
}

TEST_CASE("testing lookup1", "[lu1]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1h;
	test1h.insert(26, 'Z');
	test1h.insert(5, 'E');
	test1h.insert(20, 'T');
	test1h.insert(13, 'M');
	test1h.insert(7, 'G');
	test1h.insert(14, 'N');
	REQUIRE(test1h.lookup(14) == 'N');
	REQUIRE(test1h.lookup(7) == 'G');
	REQUIRE(test1h.lookup(20) == 'T');
	REQUIRE(test1h.lookup(26) == 'Z');
	REQUIRE_THROWS(test1h.lookup(99));
	REQUIRE_THROWS(test1h.lookup(-9));
	//std::cout << test1h.get_bfstr() << std::endl;
	REQUIRE(test1h.check_bf() == true);
}

TEST_CASE("testing remove to trigger RR", "[remRR]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1i;
	test1i.insert(5, 'E');
	test1i.insert(3, 'C');
	test1i.insert(10, 'J');
	test1i.insert(2, 'B');
	test1i.insert(7, 'G');
	test1i.insert(13, 'M');
	test1i.insert(12, 'L');
	test1i.remove(2);
	REQUIRE(test1i.inorder_print() == "3C 5E 7G 10J 12L 13M ");
	REQUIRE(test1i.check_bf() == true);
}

TEST_CASE("testing remove to trigger RL", "[remRL]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1j;
	test1j.insert(5, 'E');
	test1j.insert(3, 'C');
	test1j.insert(10, 'J');
	test1j.insert(2, 'B');
	test1j.insert(7, 'G');
	test1j.insert(13, 'M');
	test1j.insert(9, 'I');
	test1j.remove(2);
	REQUIRE(test1j.inorder_print() == "3C 5E 7G 9I 10J 13M ");
	REQUIRE(test1j.check_bf() == true);
}

TEST_CASE("testing remove to trigger LL", "[remLL]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1k;
	test1k.insert(15, 'O');
	test1k.insert(10, 'J');
	test1k.insert(17, 'Q');	
	test1k.insert(7, 'G');
	test1k.insert(13, 'M');
	test1k.insert(18, 'R');
	test1k.insert(9, 'I');
	test1k.remove(18);
	REQUIRE(test1k.inorder_print() == "7G 9I 10J 13M 15O 17Q ");
	REQUIRE(test1k.check_bf() == true);
}

TEST_CASE("testing remove to trigger LR", "[remLR]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1l;
	test1l.insert(15, 'O');
	test1l.insert(10, 'J');
	test1l.insert(17, 'Q');	
	test1l.insert(7, 'G');
	test1l.insert(13, 'M');
	test1l.insert(18, 'R');
	test1l.insert(14, 'N');
	test1l.remove(18);
	REQUIRE(test1l.size() == 6);
	REQUIRE(test1l.inorder_print() == "7G 10J 13M 14N 15O 17Q ");
	REQUIRE(test1l.check_bf() == true);
}

TEST_CASE("testing remove to trigger new case (if node has bf of 2)", "[newcase1]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> newcase1;
	newcase1.insert(10, 'J');
	newcase1.insert(5, 'E');
	newcase1.insert(12, 'L');
	newcase1.insert(3, 'C');
	newcase1.insert(7, 'G');
	REQUIRE(newcase1.inorder_print() == "3C 5E 7G 10J 12L ");
	newcase1.remove(12);
	REQUIRE(newcase1.check_bf() == true);
	REQUIRE(newcase1.inorder_print() == "3C 5E 7G 10J ");
}

TEST_CASE("testing remove to trigger new case (if node has bf of -2)", "[newcase2]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> newcase2;
	newcase2.insert(10, 'J');
	newcase2.insert(5, 'E');
	newcase2.insert(12, 'L');
	newcase2.insert(11, 'K');
	newcase2.insert(13, 'M');
	REQUIRE(newcase2.inorder_print() == "5E 10J 11K 12L 13M ");
	newcase2.remove(5);
	REQUIRE(newcase2.check_bf() == true);
	REQUIRE(newcase2.inorder_print() == "10J 11K 12L 13M ");
}

TEST_CASE("testing contains/size/clear/isempty", "[contains]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1m;
	REQUIRE(test1m.is_empty() == true);
	test1m.insert(15, 'O');
	REQUIRE(test1m.is_empty() == false);
	REQUIRE(test1m.is_full() == false);
	test1m.insert(10, 'J');
	test1m.insert(17, 'Q');	
	test1m.insert(7, 'G');
	test1m.insert(13, 'M');
	test1m.insert(18, 'R');
	test1m.insert(14, 'N');
	REQUIRE(test1m.balance() == 1);
	REQUIRE(test1m.size() == 7);
	REQUIRE(test1m.height() == 3);
	REQUIRE(test1m.contains(14) == true);
	REQUIRE(test1m.contains(18) == true);
	REQUIRE(test1m.contains(13) == true);
	REQUIRE(test1m.contains(7) == true);
	REQUIRE(test1m.contains(17) == true);
	REQUIRE(test1m.contains(10) == true);
	REQUIRE(test1m.contains(15) == true);
	REQUIRE(test1m.contains(99) == false);
	REQUIRE(test1m.contains(-9) == false);
	test1m.clear();
	REQUIRE(test1m.is_empty() == true);
}

TEST_CASE("testing is_empty", "[empty]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1n;
	REQUIRE_THROWS(test1n.remove(9));
	test1n.insert(1, 'A');
	REQUIRE(test1n.is_empty() == false);
	test1n.remove(1);
	REQUIRE(test1n.is_empty() == true);
	REQUIRE(test1n.is_full() == false);
	REQUIRE(test1n.size() == 0);
	REQUIRE_THROWS(test1n.remove(9));
}


TEST_CASE("testing height", "[height]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> test1o;
	REQUIRE(test1o.height() == -1);
	test1o.insert(1,'A');
	REQUIRE(test1o.height() == 0);
	test1o.insert(2, 'B');
	REQUIRE(test1o.height() == 1);
	test1o.remove(1);
	REQUIRE(test1o.height() == 0);
	test1o.remove(2);
	REQUIRE(test1o.height() == -1);
}

TEST_CASE("github", "[github]"){
	cop3530::AVL<int,char,*compare_int,*equality_int> git;
	REQUIRE(git.contains(9) == false);
    REQUIRE(git.is_empty() == true);
    REQUIRE(git.is_full() == false);
    size_t size = git.size();
	REQUIRE(size == 0);
    git.clear();
    REQUIRE( git.height() == -1);
    REQUIRE( git.balance() == 0);
}


