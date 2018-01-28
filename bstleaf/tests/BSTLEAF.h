#ifndef BSTLEAF_H
#define BSTLEAF_H
//#include "Map.h"
#include <stdexcept>
#include <iostream>
#include <string>


namespace cop3530{
	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	
	//class BSTLEAF : public Map<K,V,comparison_function,equality_function>{
	class BSTLEAF{
		private:
			struct Node{
				K key;
				V value;
				Node * left = nullptr;
				Node * right = nullptr;
			};
			Node * root;
		public:
			BSTLEAF();
			BSTLEAF(const BSTLEAF<K,V,comparison_function,equality_function>& other); //copy constructor
			/*copy constructor helper*/ void do_cc(Node * &thisthing, Node * otherthing);
			BSTLEAF<K,V,comparison_function,equality_function>& operator=(const BSTLEAF<K,V,comparison_function,equality_function>& other);//copy asgmt
			BSTLEAF(BSTLEAF<K,V,comparison_function,equality_function>&& other); //move constructor
			BSTLEAF<K,V,comparison_function,equality_function>&& operator=(BSTLEAF<K,V,comparison_function,equality_function>&& other); //move asgmt
			~BSTLEAF();
			/*destructor helper*/ void destroy(Node * thing);
			
			
			void insert(K i_key, V i_val);
			/*insert helper*/void do_ins(Node * &A, K i_key, V i_val);
			void remove(K key);
			/*remove helper*/ void del(Node * nwk, Node * p_nwk);
			///
			void partition(Node * &A, int k); //from book p.716
			Node * join(Node * a, Node * b); //from book p.718
			void rem(Node * &A, K i_key); //from book p.718
			///
			V& lookup(K key);
			
			void rot_right(Node * &A);
			void rot_left(Node * &A);
			
			//other functions
			Node * get_ios(Node * thing);
			Node * get_pios(Node * thing);
			K ios_test();
			
			//visual testing
			std::string output = "";
			std::string inorder_print();
			void do_inorder_print(Node * x);
			
			//bonus
			bool contains(K key);
			bool is_empty();
			bool is_full();
			int size();
			/*size helper*/int get_size(Node * A);
			void clear();
			int height();
			/*height helper*/int get_height(Node * A);
			/*height helper*/int get_max(int a, int b);
			int balance();
			/*balance helper*/int get_bf(Node * A);
	};
	
//==constructor=======================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	BSTLEAF<K,V,comparison_function,equality_function>::BSTLEAF(){
		root = nullptr;
		//std::cout << "regular constructor called" << std::endl;
	}
//====================================================================


//==copy constructor==================================================	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	BSTLEAF<K,V,comparison_function,equality_function>::BSTLEAF(const BSTLEAF<K,V,comparison_function,equality_function>& other){
		//std::cout << "copy constructor called" << std::endl;
		this->root = nullptr;
		if(other.root == nullptr){
			return;
		}
		do_cc(this->root, other.root);
		return;
	}
//====================================================================


//==do_cc=============================================================	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::do_cc(Node * &thisthing, Node * otherthing){
		//preorder traversal
		//self
		thisthing = new Node; thisthing->key=otherthing->key; thisthing->value = otherthing->value;
		//left
		if(otherthing->left){
			do_cc(thisthing->left, otherthing->left);
		}
		//right
		if(otherthing->right){
			do_cc(thisthing->right, otherthing->right);
		}
		return;
	}
//====================================================================


//==copy assignment===================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	BSTLEAF<K,V,comparison_function,equality_function>& BSTLEAF<K,V,comparison_function,equality_function>::
	operator=(const BSTLEAF<K,V,comparison_function,equality_function>& other){
		//std::cout << "copy assignment called" << std::endl;
		//delete this tree
		if(this->root){
			destroy(this->root);
		}
		this->root = nullptr;
		if(other.root != nullptr){
			do_cc(this->root, other.root);
		}
		//gives me warning
	}
//====================================================================


//==move constructor==================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	BSTLEAF<K,V,comparison_function,equality_function>::BSTLEAF(BSTLEAF<K,V,comparison_function,equality_function>&& other){
		//std::cout << "move constructor called" << std::endl;
		//copy stuff from other to this
		if(other.root == nullptr){
			this->root = nullptr;
			return;
		}
		do_cc(this->root, other.root);
		//delete other
		other.destroy(other.root);
		other.root = nullptr;
		return;
	}
//====================================================================
	
	
//==move assignment===================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	BSTLEAF<K,V,comparison_function,equality_function>&& BSTLEAF<K,V,comparison_function,equality_function>::
	operator=(BSTLEAF<K,V,comparison_function,equality_function>&& other){
		//clear lhs
		if(this->root){
			destroy(this->root);
		}
		this->root = nullptr;
		//copy rhs into lhs
		if(other.root == nullptr){
			this->root = nullptr;
			//return; cant have return
		}
		else{
			do_cc(this->root, other.root);
		}
		//delete rhs
		other.destroy(other.root);
		other.root=nullptr;
		//return; cant have return
	}
//====================================================================

	
//==destructor========================================================	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	BSTLEAF<K,V,comparison_function,equality_function>::~BSTLEAF(){
		//std::cout << "destructor called" << std::endl;
		if(root){
			destroy(root);
		}
	}
//====================================================================


//==destroy===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::destroy(Node* thing){
		//delete via post-order
		if(thing->left){
			destroy(thing->left);
		}
		if(thing->right){
			destroy(thing->right);
		}
		delete thing;
		return;
	}
//====================================================================


//==insert============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::insert(K i_key, V i_val){
		/*Node * thing = new Node;
		thing->key = i_key;
		thing->value = i_val;
		
		if(root == nullptr){
			root = thing;
			return;
		}
		
		if((*equality_function)(thing->key, root->key)){
			root->value = thing->value;
			delete thing;
			return;
		}
		
		Node * probe;
		if((*comparison_function)(thing->key, root->key)){
			if(root->left == nullptr){
				root->left = thing;
				return;
			}
			probe = root->left;
		}
		else{
			if(root->right == nullptr){
				root->right = thing;
				return;
			}
			probe = root->right;
		}
		
		while(probe){
			if((*comparison_function)(thing->key, probe->key)){
				if(probe->left == nullptr){
					probe->left = thing;
					return;
				}
				probe = probe->left;
			}
			if((*equality_function)(thing->key, probe->key)){
				probe->value = thing->value;
				delete thing;
				return;
			}
			if(!(*comparison_function)(thing->key, probe->key)){
				if(probe->right == nullptr){
					probe->right = thing;
					return;
				}
				probe = probe->right;
			}
		}*/
		
		//recursive
		do_ins(root, i_key, i_val);
	}
//====================================================================


//==do_ins============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::do_ins(Node * &A, K i_key, V i_val){
		if(A == nullptr){
			A = new Node; A->key = i_key; A->value = i_val;
			return;
		}
		if((*comparison_function)(i_key, A->key)){
			do_ins(A->left, i_key, i_val);
			return;
		}
		if((*equality_function)(i_key, A->key)){
			A->value = i_val;
			return;
		}
		else{
			do_ins(A->right, i_key, i_val);
			return;
		}
	}
//====================================================================


//==remove============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::remove(K key){
		/*//navigate to node with key (nwk)
		if((*equality_function)(root->key, key)){
			del(root,root);
			return;
		}
		Node * nwk = root;
		Node * p_nwk = root;
		while(nwk){
			if((*comparison_function)(key, nwk->key)){
				if(nwk->left){
					p_nwk = nwk;
					nwk = nwk->left;
				}
				else {
					throw std::runtime_error("no key match found to remove");
					return;
				}
			}
			else{
				if(nwk->right){
					p_nwk = nwk;
					nwk = nwk->right;
				}
				else{
					throw std::runtime_error("no key match found to remove");
					return;
				}
			}
			if((*equality_function)(key, nwk->key)){
				del(nwk, p_nwk);
				return;
			}
		}*/
		if(root == nullptr){
			throw std::runtime_error("cannot remove on an empty list");
		}
		rem(root, key);
		return;
	}
//====================================================================


//==del===============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::del(Node * nwk, Node * p_nwk){
		if(nwk->right){
			Node * ios = get_ios(nwk);
			Node * pios = get_pios(nwk);
			nwk->key = ios->key;
			nwk->value = ios->value;
			del(ios,pios);
		}
		else{
			if(p_nwk->left == nwk){
				p_nwk -> left = nwk->left;
				nwk->left = nullptr;
				delete nwk;
				return;
			}
			else{
				p_nwk -> right = nwk->left;
				nwk->left = nullptr;
				delete nwk;
				return;
			}
		}
	}
//====================================================================


//==partition=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::partition(Node * &A, int k){
		int t;
		if(A->left == nullptr){
			t = 0;
		}
		else{ 
			t = get_size(A->left);
		}
		if(t > k){
			partition(A->left, k);
			rot_right(A);
		}
		if(t < k){
			partition(A->right, k-t-1);
			rot_left(A);
		}
	}
//====================================================================


//==join==============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	typename BSTLEAF<K,V,comparison_function,equality_function>::Node * BSTLEAF<K,V,comparison_function,equality_function>::join(Node * a, Node * b){
		//std::cout << "join" << std::endl;
		if(b == nullptr){
			//std::cout << "a" << std::endl;
			return a;
		}
		//std::cout << "b" << std::endl;
		partition(b, 0);
		//std::cout << "c" << std::endl;
		b->left = a;
		return b;
	}
//====================================================================


//==rem===============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::rem(Node * &A, K i_key){
		if(A == nullptr){
			return;
		}
		if((*comparison_function)(i_key, A->key)){
			if(A->left == nullptr){
				throw std::runtime_error("cant find what to remove on");
			}
			//std::cout << "rem A->left" << std::endl;
			rem(A->left, i_key);	
			return;
		}
		if((*comparison_function)(A->key, i_key)){
			if(A->right == nullptr){
				throw std::runtime_error("cant find what to remove on");
			}
			//std::cout << "rem A->right" << std::endl;
			rem(A->right, i_key);
			return;
		}
		if((*equality_function)(A->key, i_key)){
			Node * tempdel = A;
			A = join(A->left, A->right);
			//std::cout << "deleting " << tempdel << std::endl;
			delete tempdel;
		}
	}
//====================================================================


//==get_ios===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	typename BSTLEAF<K,V,comparison_function,equality_function>::Node* BSTLEAF<K,V,comparison_function,equality_function>::get_ios(Node * thing){
		//ios is the left most child of thing's right child
		Node * flag;
		if(thing->right){
			flag = thing->right;
			while(flag->left){
				flag = flag->left;
			}
			//returns either thing's IOS OR (if there is no IOS) thing->right
			return flag;
		}
		//if no IOS OR right, then return thing back
		else return thing;
	}
//====================================================================


//==get_pios==========================================================
	template <typename K, typename V,
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	typename BSTLEAF<K,V,comparison_function,equality_function>::Node* BSTLEAF<K,V,comparison_function,equality_function>::get_pios(Node * thing){
		Node * flag = thing;
		if(flag->right){
			if(flag->right->left){
				flag = flag->right;
				while(flag->left->left){
					flag = flag->left;
				}
			}
			return flag;
		}
		else return thing;
	
	}
//====================================================================


//==lookup============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	V& BSTLEAF<K,V,comparison_function,equality_function>::lookup(K key){
		if(root == nullptr){
			throw std::runtime_error("empty tree, nothing to lookup");
		}
		
		if((*equality_function)(key, root->key)){
			return root->value;
		}
		
		Node * probe;
		if((*comparison_function)(key, root->key)){
			if(root->left == nullptr){
				throw std::runtime_error("no such key exists");
			}
			probe = root->left;
		}
		else{
			if(root->right == nullptr){
				throw std::runtime_error("no such key exists");
			}
			probe = root->right;
		}
		
		while(probe){
			if((*comparison_function)(key, probe->key)){
				if(probe->left == nullptr){
					throw std::runtime_error("no such key exists");
				}
				probe = probe->left;
			}
			if((*equality_function)(key, probe->key)){
				return probe->value;
			}
			if(!(*comparison_function)(key, probe->key)){
				if(probe->right == nullptr){
					throw std::runtime_error("no such key exists");
				}
				probe = probe->right;
			}
		}	
	}
//====================================================================


//==rot_right=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::rot_right(Node * &A){
		//std::cout << "rotating right on key " << A->key << " ("<< A << ")" << std::endl;
		Node * temp = A;
		A = A -> left;
		temp -> left = A -> right;
		A -> right = temp;
	}
//====================================================================


//==rot_left=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::rot_left(Node * &A){
		//std::cout << "rotating left on key " << A->key << " ("<< A << ")" << std::endl;
		Node * temp = A;
		A = A -> right;
		temp -> right = A -> left;
		A -> left = temp;
	}
//====================================================================


//==ios_test==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	K BSTLEAF<K,V,comparison_function,equality_function>::ios_test(){
		return get_ios(root)->key;
	}
//====================================================================


//==inorder_print=====================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	std::string BSTLEAF<K,V,comparison_function,equality_function>::inorder_print(){
		if(output != ""){
			output = "";
		}
		if(root == nullptr){
			output = "<empty tree>";
			return output;
		}
		do_inorder_print(root);
		return output;
	}
//====================================================================


//==do_inorder_print==================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::do_inorder_print(Node * x){
		if(x->left != nullptr){
			do_inorder_print(x->left);
		}
		//std::cout << "(" << x->key << "," << x->value << ")" << std::endl;
		//add to string
		//output+= std::to_string(x->key) + " ";
		output+= std::to_string(x->key) + (x->value) + " ";
		if(x->right != nullptr){
			do_inorder_print(x->right);
		}
		return;
	}
//====================================================================


//==contains==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	bool BSTLEAF<K,V,comparison_function,equality_function>::contains(K key){
		if(root == nullptr){
			return false;
		}
		
		if((*equality_function)(key, root->key)){
			return true;
		}
		
		Node * probe;
		if((*comparison_function)(key, root->key)){
			if(root->left == nullptr){
				return false;
			}
			probe = root->left;
		}
		else{
			if(root->right == nullptr){
				return false;
			}
			probe = root->right;
		}
		
		while(probe){
			if((*comparison_function)(key, probe->key)){
				if(probe->left == nullptr){
					return false;
				}
				probe = probe->left;
			}
			if((*equality_function)(key, probe->key)){
				return true;
			}
			if((*comparison_function)(probe->key, key)){
				if(probe->right == nullptr){
					return false;
				}
				probe = probe->right;
			}
		}
	}
//====================================================================


//==is_empty==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	bool BSTLEAF<K,V,comparison_function,equality_function>::is_empty(){
		if(root == nullptr) return true;
		else return false;
	}
//====================================================================


//==is_full==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	bool BSTLEAF<K,V,comparison_function,equality_function>::is_full(){
		return false;
	}
//====================================================================


//==get_size==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTLEAF<K,V,comparison_function,equality_function>::get_size(Node * A){
		if(A == nullptr) 
			return 0;
		else 
			return (get_size(A->left) + 1 + get_size(A->right));
	}
//====================================================================


//==size==============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTLEAF<K,V,comparison_function,equality_function>::size(){
		return get_size(root);
	}
//====================================================================


//==clear=============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTLEAF<K,V,comparison_function,equality_function>::clear(){
		if(root == nullptr){
			return;
		}
		destroy(root);
		root = nullptr;
		return;
	}
//====================================================================


//==get_max===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTLEAF<K,V,comparison_function,equality_function>::get_max(int a, int b){
		if(a>b) return a;
		else return b;
	}
//====================================================================


//==get_height========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTLEAF<K,V,comparison_function,equality_function>::get_height(Node * A){
		if(A == nullptr){
		//if(A->left==nullptr && A->right==nullptr){
			return 0;
		}
		return 1 + get_max(get_height(A->left), get_height(A->right));
	}
//====================================================================


//==height============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTLEAF<K,V,comparison_function,equality_function>::height(){
		if(root==nullptr){
			return -1;
		}
		return get_height(root)-1;
	}
//====================================================================


//==get_bf============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTLEAF<K,V,comparison_function,equality_function>::get_bf(Node * A){
		//int ans = (get_height(A->left) - get_height(A->right));
		if(A == nullptr){
			return 0;
		}
		int ans = ((get_height(A->left)-1) - (get_height(A->right)-1));
		return ans;
	}
//====================================================================


//==balance===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTLEAF<K,V,comparison_function,equality_function>::balance(){
		return get_bf(root);
	}
//====================================================================
	
}

#endif