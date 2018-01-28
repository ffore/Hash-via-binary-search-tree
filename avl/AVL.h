#ifndef AVL_H
#define AVL_H
//#include "Map.h"
#include <stdexcept>
#include <iostream>
#include <string>

namespace cop3530{
	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	
	
	//class AVL : public Map<K,V,comparison_function,equality_function>{
	class AVL{
		private:
			struct Node{
				K key;
				V value;
				Node * left = nullptr;
				Node * right = nullptr;
			};
			Node * root;
		public:
			AVL();
			AVL(const AVL<K,V,comparison_function,equality_function>& other); //copy constructor
			/*copy constructor helper*/ void do_cc(Node * &thisthing, Node * otherthing);
			AVL<K,V,comparison_function,equality_function>& operator=(const AVL<K,V,comparison_function,equality_function>& other);//copy asgmt
			AVL(AVL<K,V,comparison_function,equality_function>&& other); //move constructor
			AVL<K,V,comparison_function,equality_function>&& operator=(AVL<K,V,comparison_function,equality_function>&& other); //move asgmt
			~AVL();
			/*destructor helper*/void destroy(Node * thing);
			
			void insert(K i_key, V i_val);
			void avl_ins(Node * &A, K i_key, V i_val);
			
			//AVL specific
			int get_bf(Node * A);
			int get_height(Node * A);
			int get_max(int a, int b);
			void rot_right(Node * &A);
			void rot_left(Node * &A);
			Node * get_parent(Node * &A);
			
			void partition(Node * &A, int k); //from book p.716
			int get_size(Node * A);
			Node * join(Node * a, Node * b); //from book p.718
			void rem(Node * &A, K i_key); //from book p.718
			void remove(K key);
			
			
			V& lookup(K key);
			
			//bonus
			bool contains(K key);
			bool is_empty();
			bool is_full();
			int size();
			void clear();
			int height();
			int balance();
			
			//checking bf
			std::string bfstr = "";
			std::string get_bfstr();
			void do_bfstr(Node * x);
			bool check_bf();
			
			//printing
			std::string output = "";
			std::string inorder_print();
			void do_inorder_print(Node * x);
			
		
	};
	
//==constructor=======================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	AVL<K,V,comparison_function,equality_function>::AVL(){
		root = nullptr;
	}
//====================================================================


//==copy constructor==================================================	
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	AVL<K,V,comparison_function,equality_function>::AVL(const AVL<K,V,comparison_function,equality_function>& other){
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
	void AVL<K,V,comparison_function,equality_function>::do_cc(Node * &thisthing, Node * otherthing){
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
	AVL<K,V,comparison_function,equality_function>& AVL<K,V,comparison_function,equality_function>::
	operator=(const AVL<K,V,comparison_function,equality_function>& other){
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
	AVL<K,V,comparison_function,equality_function>::AVL(AVL<K,V,comparison_function,equality_function>&& other){
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
	AVL<K,V,comparison_function,equality_function>&& AVL<K,V,comparison_function,equality_function>::
	operator=(AVL<K,V,comparison_function,equality_function>&& other){
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
	AVL<K,V,comparison_function,equality_function>::~AVL(){
		//std::cout << "destructor called" << std:: endl;
		if(root){
			//std::cout << "doing destroy" << std::endl;
			destroy(root);
		}
	}
//====================================================================


//==destroy===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::destroy(Node* thing){
		//delete via post-order
		if(thing->left){
			destroy(thing->left);
		}
		if(thing->right){
			destroy(thing->right);
		}
		//std::cout << "deleting key at " << thing << std::endl;
		delete thing;
		return;
	}
//====================================================================


//==insert============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::insert(K i_key, V i_val){
		//std::cout << "now inserting key " << i_key << std::endl;
		avl_ins(root, i_key, i_val);
		return;
	}
//====================================================================


//==avl_ins===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::avl_ins(Node * &A, K i_key, V i_val){
		if(A == nullptr){
			A = new Node; A->key = i_key; A->value = i_val;
			//std::cout << "made " << i_key << " at location " << A << std::endl;
			return;
		}
		
		if((*equality_function)(i_key, A->key)){
			A->value = i_val;
			return;
		}
		
		if((*comparison_function)(i_key, A->key)){
			avl_ins(A->left, i_key, i_val);
			int bfp = get_bf(A); int bfc = get_bf(A->left);
			if(bfp == 2 && bfc == 1){	//LL rotation (rotate right on p)
				rot_right(A);
				return;
			}
			if(bfp == 2 && bfc == -1){	//LR rotation (rotate left on c then rotate right on p)
				rot_left(A->left);
				rot_right(A);
				return;
			}
			return;
		}
		else{
			avl_ins(A->right, i_key, i_val);
			int bfp = get_bf(A); int bfc = get_bf(A->right);
			if(bfp == -2 && bfc == -1){	//RR rotation (rotate left on p)
				rot_left(A);
				return;
			}
			if(bfp == -2 && bfc == 1){	//RL rotation (rotate right on c then rotate left on p)
				rot_right(A->right);
				rot_left(A);
				return;
			}
			return;
		}
	}
//====================================================================


//==get_max===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int AVL<K,V,comparison_function,equality_function>::get_max(int a, int b){
		if(a>b) return a;
		else return b;
	}
//====================================================================


//==get_height========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int AVL<K,V,comparison_function,equality_function>::get_height(Node * A){
		if(A == nullptr){
		//if(A->left==nullptr && A->right==nullptr){
			return 0;
		}
		return 1 + get_max(get_height(A->left), get_height(A->right));
	}
//====================================================================


//==get_bf============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int AVL<K,V,comparison_function,equality_function>::get_bf(Node * A){
		if(A == nullptr){
			return 0;
		}
		//int ans = (get_height(A->left) - get_height(A->right));
		int ans = ((get_height(A->left)-1) - (get_height(A->right)-1));
		return ans;
	}
//====================================================================


//==rot_right=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::rot_right(Node * &A){
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
	void AVL<K,V,comparison_function,equality_function>::rot_left(Node * &A){
		Node * temp = A;
		A = A -> right;
		temp -> right = A -> left;
		A -> left = temp;
	}
//====================================================================


//==get_parent=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	typename AVL<K,V,comparison_function,equality_function>::Node * AVL<K,V,comparison_function,equality_function>::get_parent(Node * &A){
		//assuming the input is valid
		if(A -> left == nullptr && A-> right ==nullptr){
			return A;
		}
		Node * probe = root;
		while(probe){
			if((*comparison_function)(A->key, probe->key)){
				if((*equality_function)(A->key, probe->left->key)){
					return probe;
				}
				probe = probe->left;
			}
			if((*comparison_function)(probe->key, A->key)){
				if((*equality_function)(A->key, probe->right->key)){
					return probe;
				}
				probe = probe->right;
			}
		}
	}
	
//====================================================================


//==partition=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::partition(Node * &A, int k){
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


//==get_size==============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int AVL<K,V,comparison_function,equality_function>::get_size(Node * A){
		if(A == nullptr) 
			return 0;
		else 
			return (get_size(A->left) + 1 + get_size(A->right));
	}
//====================================================================


//==join==============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	typename AVL<K,V,comparison_function,equality_function>::Node * AVL<K,V,comparison_function,equality_function>::join(Node * a, Node * b){
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
	void AVL<K,V,comparison_function,equality_function>::rem(Node * &A, K i_key){
		if(A == nullptr){
			return;
		}
		if((*comparison_function)(i_key, A->key)){
			if(A->left == nullptr){
				throw std::runtime_error("cant find what to remove on");
			}
			//std::cout << "rem A->left" << std::endl;
			rem(A->left, i_key);
			///
			//Node * Ap = get_parent(A);
			if(A->right){
				int bfp = get_bf(A); int bfc = get_bf(A->right);
				if(bfp == -2 && bfc == -1){	//RR rotation (rotate left on p)
					//std::cout << "RR" << std::endl;
					rot_left(A);
					return;
				}
				if(bfp == -2 && bfc == 1){	//RL rotation (rotate right on c then rotate left on p)
					//std::cout << "RL" << std::endl;
					rot_right(A->right);
					rot_left(A);
					return;
				}
				//new caseee
				if(bfp == -2){
					//std::cout << "new case" << std::endl;
					rot_left(A);
					return;
				}
			}
			return;
			///
			
		}
		if((*comparison_function)(A->key, i_key)){
			if(A->right == nullptr){
				throw std::runtime_error("cant find what to remove on");
			}
			//std::cout << "rem A->right" << std::endl;
			rem(A->right, i_key);
			///			
			//Node * Ap = get_parent(A);
			if(A->left){
				int bfp = get_bf(A); int bfc = get_bf(A->left);
				if(bfp == 2 && bfc == 1){	//LL rotation (rotate right on p)
					//std::cout << "LL" << std::endl;
					rot_right(A);
					return;
				}
				if(bfp == 2 && bfc == -1){	//LR rotation (rotate left on c then rotate right on p)
					//std::cout << "LR" << std::endl;
					rot_left(A->left);
					rot_right(A);
					return;
				}
				//new caseee
				if(bfp == 2){
					//std::cout << "new case" << std::endl;
					rot_right(A);
					return;
				}
			}
			return;
			///
			
			
		}
		if((*equality_function)(A->key, i_key)){
			Node * tempdel = A;
			A = join(A->left, A->right);
			//std::cout << "deleting " << tempdel << std::endl;
			delete tempdel;
		}
		
	}
//====================================================================


//==remove============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::remove(K key){
		if(root == nullptr){
			throw std::runtime_error("cannot remove on an empty list");
		}
		rem(root, key);
		return;
	}
//====================================================================


//==lookup============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	V& AVL<K,V,comparison_function,equality_function>::lookup(K key){
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


//==get_bfstr=========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	std::string AVL<K,V,comparison_function,equality_function>::get_bfstr(){
		if(bfstr != ""){
			bfstr = "";
		}
		if(root == nullptr){
			bfstr = "<empty tree>";
			return bfstr;
		}
		do_bfstr(root);
		return bfstr;
	}
//====================================================================


//==do_bfstr==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::do_bfstr(Node * x){
		if(x->left != nullptr){
			do_bfstr(x->left);
		}
		//bfstr += std::to_string(get_bf(x))  + " ";
		bfstr += std::to_string(abs(get_bf(x)))  + " ";
		if(x->right != nullptr){
			do_bfstr(x->right);
		}
		return;
	}
//====================================================================


//==check_bf==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	bool AVL<K,V,comparison_function,equality_function>::check_bf(){
		//checks if all of the nodes have bf of 0 or 1 (uses absolute value)
		if(bfstr == "") return true;
		
		//std::cout << "size " << bfstr.size() << std::endl;
		for(unsigned int i = 0; i < bfstr.size(); i++){
			//std::cout << bfstr[i] << "_";
			if(bfstr[i] != '0' && bfstr[i] != ' ' && bfstr[i] != '1'){
				//std::cout << "falsee" << std::endl;
				return false;
			}
		}
		//std::cout << "\n";
		return true;
	}
//====================================================================


//==inorder_print=====================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	std::string AVL<K,V,comparison_function,equality_function>::inorder_print(){
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
	void AVL<K,V,comparison_function,equality_function>::do_inorder_print(Node * x){
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
	bool AVL<K,V,comparison_function,equality_function>::contains(K key){
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
	bool AVL<K,V,comparison_function,equality_function>::is_empty(){
		if(root == nullptr) return true;
		else return false;
	}
//====================================================================


//==is_full==========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	bool AVL<K,V,comparison_function,equality_function>::is_full(){
		return false;
	}
//====================================================================


//==size==============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int AVL<K,V,comparison_function,equality_function>::size(){
		return get_size(root);
	}
//====================================================================


//==clear=============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	void AVL<K,V,comparison_function,equality_function>::clear(){
		if(root == nullptr){
			return;
		}
		destroy(root);
		root = nullptr;
		return;
	}
//====================================================================


//==height============================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int AVL<K,V,comparison_function,equality_function>::height(){
		if(root==nullptr){
			return -1;
		}
		return get_height(root)-1;
	}
//====================================================================


//==balance===========================================================
	template <typename K, typename V, 
	bool (*comparison_function)(const K& key1, const K& key2),
	bool (*equality_function)(const K& key1, const K& key2)>
	int AVL<K,V,comparison_function,equality_function>::balance(){
		return get_bf(root);
	}
//====================================================================


}

#endif