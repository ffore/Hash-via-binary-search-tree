#ifndef BSTRAND_H
#define BSTRAND_H
//#include "Map.h"
#include <stdexcept>
#include <iostream>
#include <string>


namespace cop3530{
	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	//class BSTRAND : public Map<K,V,comparison_function,equality_function>{
	class BSTRAND{
		private:
			struct Node{
				K key;
				V value;
				Node * left = nullptr;
				Node * right = nullptr;
			};
			Node * root;
		public:
			BSTRAND();
			BSTRAND(const BSTRAND<K,V,comparison_function,equality_function>& other); //copy constructor
			/*copy constructor helper*/ void do_cc(Node * &thisthing, Node * otherthing);
			BSTRAND<K,V,comparison_function,equality_function>& operator=(const BSTRAND<K,V,comparison_function,equality_function>& other);//copy asgmt
			BSTRAND(BSTRAND<K,V,comparison_function,equality_function>&& other); //move constructor
			BSTRAND<K,V,comparison_function,equality_function>&& operator=(BSTRAND<K,V,comparison_function,equality_function>&& other); //move asgmt
			~BSTRAND();
			/*destructor helper*/void destroy(Node * thing);
			
			void insert(K i_key, V i_val);
			void insert_rand(Node * &A, K i_key, V i_val);
			int get_size(Node * A);
			
			void remove(K key);
			/*remove helper*/ void del(Node * nwk, Node * p_nwk);
			/*remove helper*/ Node * get_ios(Node * thing);
			/*remove helper*/ Node * get_pios(Node * thing);
			///
			void partition(Node * &A, int k); //from book p.716
			Node * join(Node * a, Node * b); //from book p.718
			void rem(Node * &A, K i_key); //from book p.718
			///
			
			
			V& lookup(K key);
			
			//stuff from bstroot
			void insert_at_root(Node * &A, K i_key, V i_val);
			void rot_right(Node * &A);
			void rot_left(Node * &A);
			
			//printing
			std::string output = "";
			std::string inorder_print();
			void do_inorder_print(Node * x);
			
			//bonus
			bool contains(K key);
			bool is_empty();
			bool is_full();
			int size();
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
	BSTRAND<K,V,comparison_function,equality_function>::BSTRAND(){
		root = nullptr;
	}
//====================================================================


//==copy constructor==================================================	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	BSTRAND<K,V,comparison_function,equality_function>::BSTRAND(const BSTRAND<K,V,comparison_function,equality_function>& other){
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
	void BSTRAND<K,V,comparison_function,equality_function>::do_cc(Node * &thisthing, Node * otherthing){
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
	BSTRAND<K,V,comparison_function,equality_function>& BSTRAND<K,V,comparison_function,equality_function>::
	operator=(const BSTRAND<K,V,comparison_function,equality_function>& other){
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
	BSTRAND<K,V,comparison_function,equality_function>::BSTRAND(BSTRAND<K,V,comparison_function,equality_function>&& other){
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
	BSTRAND<K,V,comparison_function,equality_function>&& BSTRAND<K,V,comparison_function,equality_function>::
	operator=(BSTRAND<K,V,comparison_function,equality_function>&& other){
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
	BSTRAND<K,V,comparison_function,equality_function>::~BSTRAND(){
		if(root){
			destroy(root);
		}	
	}
//====================================================================
	
	
//==destroy===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTRAND<K,V,comparison_function,equality_function>::destroy(Node* thing){
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
	void BSTRAND<K,V,comparison_function,equality_function>::insert(K i_key, V i_val){
		insert_rand(root, i_key, i_val);
		return;
	}
//====================================================================


//==insert_rand=======================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTRAND<K,V,comparison_function,equality_function>::insert_rand(Node * &A, K i_key, V i_val){
		if(A == nullptr){
			//std::cout << "insert at leaf" << std::endl;
			A = new Node; A->key = i_key; A->value = i_val;
			return;
		}
		if(rand() < RAND_MAX/(get_size(A)+1)){
			//std::cout << "rand worked insert at root" << std::endl;
			insert_at_root(A, i_key, i_val);
			return;
		}
		//this part mimicks leaf insertion
		if((*comparison_function)(i_key, A->key)){
			insert_rand(A->left, i_key, i_val);
			//return; book doesn't have return
		}
		else{
			insert_rand(A->right, i_key, i_val);
		}
	}
//====================================================================


//==get_size==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTRAND<K,V,comparison_function,equality_function>::get_size(Node * A){
		/*int s = 0;
		if(A->left){
			s += 1 + get_size(A->left);
		}
		if(A->right){
			s += 1 + get_size(A->right);
		}
		else{
			return 0;
		}
		return s+1;*/
		if(A == nullptr) 
			return 0;
		else 
			return (get_size(A->left) + 1 + get_size(A->right));
	}
//====================================================================


//==remove============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTRAND<K,V,comparison_function,equality_function>::remove(K key){
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
	void BSTRAND<K,V,comparison_function,equality_function>::del(Node * nwk, Node * p_nwk){
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


//==get_ios===========================================================	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	typename BSTRAND<K,V,comparison_function,equality_function>::Node * BSTRAND<K,V,comparison_function,equality_function>::get_ios(Node * thing){
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
	typename BSTRAND<K,V,comparison_function,equality_function>::Node * BSTRAND<K,V,comparison_function,equality_function>::get_pios(Node * thing){
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


//==partition=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTRAND<K,V,comparison_function,equality_function>::partition(Node * &A, int k){
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
	typename BSTRAND<K,V,comparison_function,equality_function>::Node * BSTRAND<K,V,comparison_function,equality_function>::join(Node * a, Node * b){
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
	void BSTRAND<K,V,comparison_function,equality_function>::rem(Node * &A, K i_key){
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


//==lookup============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	V& BSTRAND<K,V,comparison_function,equality_function>::lookup(K key){
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


//==insert_at_root====================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTRAND<K,V,comparison_function,equality_function>::insert_at_root(Node * &A, K i_key, V i_val){
		//base case
		if(A == nullptr){
			A = new Node;
			A->key = i_key;
			A->value = i_val;
			return;
		}
		//inserting at left, then rot right
		if((*comparison_function)(i_key, A->key)){
			insert_at_root(A->left, i_key, i_val);
			rot_right(A);
			return;
		}
		//if same key, update value
		if((*equality_function)(i_key, A->key)){
			A->value = i_val;
			return;
		}
		//inserting at right, then rot left
		else{
			insert_at_root(A->right, i_key, i_val);
			rot_left(A);
			return;
		}
	}
//====================================================================


//==rot_right=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTRAND<K,V,comparison_function,equality_function>::rot_right(Node * &A){
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
	void BSTRAND<K,V,comparison_function,equality_function>::rot_left(Node * &A){
		Node * temp = A;
		A = A -> right;
		temp -> right = A -> left;
		A -> left = temp;
	}
//====================================================================


//==inorder_print=====================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	std::string BSTRAND<K,V,comparison_function,equality_function>::inorder_print(){
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
	void BSTRAND<K,V,comparison_function,equality_function>::do_inorder_print(Node * x){
		if(x->left != nullptr){
			do_inorder_print(x->left);
		}
		output+= std::to_string(x->key) + (x->value)  + " ";
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
	bool BSTRAND<K,V,comparison_function,equality_function>::contains(K key){
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
	bool BSTRAND<K,V,comparison_function,equality_function>::is_empty(){
		if(root == nullptr) return true;
		else return false;
	}
//====================================================================


//==is_full==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	bool BSTRAND<K,V,comparison_function,equality_function>::is_full(){
		return false;
	}
//====================================================================


//==size==============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTRAND<K,V,comparison_function,equality_function>::size(){
		return get_size(root);
	}
//====================================================================


//==clear=============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void BSTRAND<K,V,comparison_function,equality_function>::clear(){
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
	int BSTRAND<K,V,comparison_function,equality_function>::get_max(int a, int b){
		if(a>b) return a;
		else return b;
	}
//====================================================================


//==get_height========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTRAND<K,V,comparison_function,equality_function>::get_height(Node * A){
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
	int BSTRAND<K,V,comparison_function,equality_function>::height(){
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
	int BSTRAND<K,V,comparison_function,equality_function>::get_bf(Node * A){
		if(A == nullptr){
			return 0;
		}
		//int ans = (get_height(A->left) - get_height(A->right));
		int ans = ((get_height(A->left)-1) - (get_height(A->right)-1));
		return ans;
	}
//====================================================================


//==balance===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int BSTRAND<K,V,comparison_function,equality_function>::balance(){
		return get_bf(root);
	}
//====================================================================

}

#endif