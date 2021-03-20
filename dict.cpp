#pragma once
template <typename Key, typename Val>
TDict<Key, Val>::TDict(){
    root = nullptr;
    Size_ = 0;
}
template <typename Key, typename Val>
void TDict<Key, Val>::DeleteNode(TNode<Key, Val>* node){
    if (node == nullptr) {
        return;
    }
    DeleteNode(node->left);
    DeleteNode(node->right);
    delete node;
}
template <typename Key, typename Val>
void TDict<Key, Val>::Clear(){
    DeleteNode(root);
    root = nullptr;
    Size_ = 0;
}
template <typename Key, typename Val>
TDict<Key, Val>::~TDict()
{
    Clear();
}
template <typename Key, typename Val>
void TDict<Key,Val>::FixRRDisbalance(TNode<Key, Val>* node){
    if (node == root){
        root = node->right;
        node->right=root->left;
        if(node->right!=nullptr){
            node->right->parent=node;
        }
        root->left = node;
        node->parent = root;
        root->parent = nullptr;
        root->balance=0;
        root->left->balance=0;
        return;
    }
    node->right->parent=node->parent;
    if (node == node->parent->left) {
        node->parent->left = node->right;
    }
    else {
        node->parent->right = node->right;
    }
    node->parent=node->right;
    node->right=node->right->left;
    if (node->right != nullptr){
        node->right->parent=node;
    }
    node->parent->left=node;
    node->balance=0;
    node->parent->balance=0;
    return;
}
template <typename Key, typename Val>
void TDict<Key,Val>::FixRLDisbalance(TNode<Key, Val>* node){
    if (node == root){
        root = node->right->left;
        node->right->left=root->right;
        if(node->right->left != nullptr){
            node->right->left->parent=node->right;
        }
        node->right=root->left;
        if(node->right != nullptr){
            node->right->parent=node;
        }
        
        root->left = node;
        node->parent=root;
        root->right = root->parent;
        root->right->parent = root;
        root->parent=nullptr;

        if(root->balance == 1){
            root->right->balance = 0;
            root->left->balance = -1;
        }else if(root->balance == -1){
            root->left->balance = 0;
            root->right->balance = 1;
        }else{
            root->left->balance = 0;
            root->right->balance = 0;
        }
        root->balance = 0;
        return;
    }

    TNode <Key, Val>* localRoot = node->right->left;
    if(node == node->parent->left) {
        node->parent->left = localRoot;
    }
    else{
        node->parent->right = localRoot;
    }
    node->right->left=localRoot->right;
    if(node->right->left != nullptr){
        node->right->left->parent = node->right;
    }
    node->right = localRoot->left;
    if(node->right != nullptr){
        node->right->parent = node;
    }
    
    localRoot->left = node;
    TNode<Key, Val>* localRootParent=node->parent;
    node->parent=localRoot;
    localRoot->right = localRoot->parent;
    localRoot->right->parent = localRoot;
    localRoot->parent=localRootParent;
    if(localRoot->balance == 1){
        localRoot->right->balance = 0;
        localRoot->left->balance = -1;
    }else if(localRoot->balance == -1){
        localRoot->left->balance = 0;
        localRoot->right->balance = 1;
    }else{
        localRoot->left->balance = 0;
        localRoot->right->balance = 0;
    }
    localRoot->balance = 0;
    return;

}
template <typename Key, typename Val>
void TDict<Key,Val>::FixLRDisbalance(TNode<Key, Val>* node) {
    if (node == root){
        root = node->left->right;
        node->left->right=root->left;
        if(node->left->right != nullptr){
            node->left->right->parent=node->left;
        }
        node->left=root->right;
        if(node->left != nullptr){
            node->left->parent=node;
        }
        
        root->right = node;
        node->parent=root;
        root->left = root->parent;
        root->left->parent = root;
        root->parent=nullptr;
        if(root->balance == 1){
            root->right->balance = 0;
            root->left->balance = -1;
        }else if(root->balance == -1){
            root->left->balance = 0;
            root->right->balance = 1;
        }else{
            root->left->balance = 0;
            root->right->balance = 0;
        }
        root->balance = 0;
        return;
    }

    TNode <Key, Val>* localRoot = node->left->right;
    if(node == node->parent->left) {
        node->parent->left = localRoot;
    }
    else{
        node->parent->right = localRoot;
    }
    node->left->right=localRoot->left;
    if(node->left->right != nullptr){
        node->left->right->parent=node->left;
    }
    node->left=localRoot->right;
    if(node->left != nullptr){
        node->left->parent=node;
    }
    
    localRoot->right = node;
    TNode<Key, Val>* localRootParent=node->parent;
    node->parent=localRoot;
    localRoot->left = localRoot->parent;
    localRoot->left->parent = localRoot;
    localRoot->parent=localRootParent;
    if(localRoot->balance == 1){
        localRoot->right->balance = 0;
        localRoot->left->balance = -1;
    }else if(localRoot->balance == -1){
        localRoot->left->balance = 0;
        localRoot->right->balance = 1;
    }else{
        localRoot->left->balance = 0;
        localRoot->right->balance = 0;
    }
    localRoot->balance = 0;
    return;

}
template <typename Key, typename Val>
void TDict<Key,Val>::FixLLDisbalance(TNode<Key, Val>* node) {
     if (node == root){
        root = node->left;
        node->left=root->right;
        if(node->left!=nullptr){
            node->left->parent=node;
        }
        root->right = node;
        node->parent = root;
        root->parent = nullptr;
        root->balance=0;
        root->right->balance=0;
        return;
    }
    node->left->parent=node->parent;
    if (node == node->parent->left) {
        node->parent->left = node->left;
    }
    else{
        node->parent->right = node->left;
    }
    node->parent=node->left;
    node->left=node->left->right;
    if(node->left!=nullptr){
        node->left->parent=node;
    }
    node->parent->right=node;
    node->balance=0;
    node->parent->balance=0;
    return;
}
template <typename Key, typename Val>
void TDict<Key, Val>::Balance(TNode<Key, Val>* node)
{   // balance is h(right) - h(left)
    if (node->parent == nullptr) {
        return;
    }
    if (node->parent->balance == 1) {
        if (node == node->parent->left) {
            node->parent->balance = 0;
            return;
        }
        else {
            if (node->balance == 1) {
                FixRRDisbalance(node->parent);
                return;
            }
            if (node->balance == -1) {
                FixRLDisbalance(node->parent);
                return;
            }
        }
    }
    if (node->parent->balance == 0) {
        if (node == node->parent->left) {
            node->parent->balance = -1;
            Balance(node->parent);
            return;
        }
        else {
            node->parent->balance = 1;
            Balance(node->parent);
            return;
        }
    }
    if (node->parent->balance == -1) {
        if (node == node->parent->left){
            if (node->balance == 1) {
                FixLRDisbalance(node->parent);
                return;
            }
            if (node->balance == -1) {
                FixLLDisbalance(node->parent);
                return;
            }
        }
        else {
            node->parent->balance=0;
            return;
        }
    }
}
template <typename Key, typename Val>
TNode<Key, Val>* TDict<Key, Val>::Insert(TNode<Key, Val>* node, const Key& key) {
    if (key < node->data->first) {
        if (node->left == nullptr) {
            node->left = new TNode<Key, Val>;
            node->left->data->first = key;
            node->left->parent = node;
            ++Size_;
            return node->left;
        }
        else {
            return Insert(node->left, key);
        }
    }
    if (node->data->first < key) {
        if (node->right == nullptr) {
            node->right = new TNode<Key, Val>;
            node->right->data->first = key;
            node->right->parent = node;
            ++Size_;
            return node->right;
        }
        else {
            return Insert(node->right, key);
        }
    }
    return node;
}
template <typename Key, typename Val>
TNode<Key, Val>* TDict<Key, Val>::FindNode(TNode<Key, Val>* node, const Key& key) {
    if (key < node->data->first) {
        if (node->left == nullptr) {
            return nullptr;
        }
        else {
            return FindNode(node->left, key);
        }
    }
    if (node->data->first < key) {
        if (node->right == nullptr) {
            return nullptr;
        }
        else {
            return FindNode(node->right, key);
        }
    }
    return node;
}
template <typename Key, typename Val>
void TDict<Key, Val>::BalanceAfterDeletion(TNode<Key,Val>* node){
    TNode<Key,Val>* oldParent = node->parent;
    bool nodeIsLeft;
    if (oldParent != nullptr) {
        nodeIsLeft = node == oldParent->left;
    }
    if (node->balance == 2) {
        if (node->right->balance == 1) {
            FixRRDisbalance(node);
            if (oldParent != nullptr) {
                if(nodeIsLeft){
                    oldParent->balance += 1;
                }
                else{
                    oldParent->balance -= 1;
                }
                BalanceAfterDeletion(oldParent);
            }
            return;
        }
        if (node->right->balance == 0) {
            FixRRDisbalance(node);
            node->balance = 1;
            node->parent->balance = -1;
            return;
        }
        if (node->right->balance == -1) {
            FixRLDisbalance(node);
            if (oldParent != nullptr) {
                if(nodeIsLeft) {
                    oldParent->balance +=1;
                }
                else {
                    oldParent->balance -=1;
                }
                BalanceAfterDeletion(oldParent);
            }
            return;
        }
    }
    if (node->balance == -2) {
        if (node->left->balance == -1) {
            FixLLDisbalance(node);
            if(oldParent != nullptr) {
                if(nodeIsLeft){
                    oldParent->balance += 1;
                }
                else {
                    oldParent->balance -= 1;
                }
                BalanceAfterDeletion(oldParent);
            }
            return;
        }
        if (node->left->balance == 0) {
            FixLLDisbalance(node);
            node->balance = -1;
            node->parent->balance = 1;
            return;
        }
        if (node->left->balance == 1) {
            FixLRDisbalance(node);
            if(oldParent != nullptr) {
                if(nodeIsLeft){
                    oldParent->balance += 1;
                }
                else {
                    oldParent->balance -= 1;
                }
                BalanceAfterDeletion(oldParent);
            }
            return;
        }
    }
    if (node->balance == 0) {
        if (oldParent != nullptr) {
            if (nodeIsLeft){
                oldParent->balance += 1;
                BalanceAfterDeletion(oldParent);
                return;
            }
            else{
                oldParent->balance -= 1;
                BalanceAfterDeletion(oldParent);
                return;
            }
        }
    }
}
template <typename Key, typename Val>
void TDict<Key, Val>::EraseNode(TNode<Key,Val>* node){
    if (node->left != nullptr && node->right != nullptr) {
        TNode<Key,Val>* leftmostOfRightSubtree = node->right;
        while(leftmostOfRightSubtree->left != nullptr) {
            leftmostOfRightSubtree = leftmostOfRightSubtree->left;
        }
        TPair<Key, Val>* tmp = leftmostOfRightSubtree->data;
        leftmostOfRightSubtree->data = node->data;
        node->data = tmp;
        EraseNode(leftmostOfRightSubtree);
        return;
    }
    if (node->right != nullptr) {
        TNode<Key,Val>* right=node->right;
        right->parent=node->parent;
        if(node->parent == nullptr) {
            root = right;
            delete node;
            --Size_;
            return;
        }
        else {
            if (node == node->parent->right) {
                node->parent->right = right;
                right->parent->balance -= 1;
            }
            else {
                node->parent->left = right;
                right->parent->balance += 1;
            }
        }
        node->right = nullptr;
        node->parent = nullptr;
        delete node;
        --Size_;
        BalanceAfterDeletion(right->parent);
        return;
    }
    if (node->left != nullptr) {
        TNode<Key,Val>* left=node->left;
        left->parent=node->parent;
        if(node->parent == nullptr) {
            root = left;
            delete node;
            --Size_;
            return;
        }
        else {
            if (node == node->parent->right) {
                node->parent->right = left;
                left->parent->balance -= 1;
            }
            else {
                node->parent->left = left;
                left->parent->balance += 1;
            }
        }
        node->left = nullptr;
        node->parent = nullptr;
        delete node;
        --Size_;
        BalanceAfterDeletion(left->parent);
        return;
    }


    if (node->parent == nullptr){
        Clear();
        return;
    }
    TNode<Key,Val>* parent=node->parent;
    if (node == node->parent->left) {
        node->parent->left=nullptr;
        node->parent->balance += 1;
    }
    else {
        node->parent->right=nullptr;
        node->parent->balance -= 1;
    }
    delete node;
    --Size_;
    BalanceAfterDeletion(parent);
    return;
}
template <typename Key, typename Val>
bool TDict<Key, Val>::Erase(const Key& key){
    if (root == nullptr){
        return false;
    }
    TNode<Key, Val>* node = FindNode(root, key);
    if (node == nullptr){
        return false;
    }
    EraseNode(node);
    return true;
}
template <typename Key, typename Val>
TDictIterator<Key, Val> TDict<Key, Val>::Find(const Key& key){
    if (root == nullptr) {
        return TDictIterator<Key, Val>{nullptr};
    }

    TNode<Key, Val>* node = FindNode(root, key);
    return TDictIterator<Key, Val>{ node };
}
template <typename Key, typename Val>
TDictIterator<Key, Val> TDict<Key, Val>::end(){
    return TDictIterator<Key, Val>{nullptr};
}
template <typename Key, typename Val>
TDictIterator<Key, Val> TDict<Key, Val>::begin(){
    if (root == nullptr) {
        return TDictIterator<Key, Val>{nullptr};
    }
    TNode<Key, Val> node = root;
    while (node->left != nullptr) {
        node = node->left;
    }
    return TDictIterator<Key, Val>{node};
}
template <typename Key, typename Val>
int TDict<Key, Val>::Size(){
    return Size_;
}
template <typename Key, typename Val>
TDictIterator<Key,Val> TDict<Key, Val>::FindOrCreate(const Key& key){
    if (root == nullptr) {
        root = new TNode<Key, Val>;
        root->data->first = key;
        Size_ = 1;
        return TDictIterator<Key,Val>{root};
    }
    int old_size=Size_;
    TNode<Key, Val>* inserted = Insert(root, key);
    if(Size_ > old_size){
        Balance(inserted);
    }
    return TDictIterator<Key, Val>{inserted};
}
template <typename Key, typename Val>
Val& TDict<Key, Val>::operator[](const Key& key) {
    if (root == nullptr) {
        root = new TNode<Key, Val>;
        root->data->dirst = key;
        Size_ = 1;
        return root->data->second;
    }
    int old_size=Size_;
    TNode<Key, Val>* inserted = Insert(root, key);
    if(Size_ > old_size){
        Balance(inserted);
    }
    return inserted->data->second;
}

template <typename Key, typename Val>
void TDict<Key, Val>::WriteNode(TNode<Key, Val>* node, std::ostream& file){
    if (file.good()) {
        WriteKeyToFile(node->data->first, file);
        WriteValueToFile(node->data->second, file);
        unsigned char balance = (node->balance + 1); //converting balance: -1->00b, 0->01b, 1->10b
        balance <<= 2; //shifting balance to make space for last two bits for storing left and right nodes state
        unsigned char left_good = node->left != nullptr;
        unsigned char right_good = node->right != nullptr;
        char info = static_cast<char>(balance | (left_good << 1u) | right_good); // bit before last says whether node has left child, last says same about right
        file.write(&info, 1);
        if (left_good) {
            WriteNode(node->left, file);
        }
        if (right_good) {
            WriteNode(node->right, file);
        }
    }
}

template <typename Key, typename Val>
TNode<Key, Val>* TDict<Key, Val>::ReadNode(TNode<Key, Val>* parent, std::istream& file){
    if (file.good()) {
        TNode<Key, Val>* node = new TNode<Key, Val>;
        node->parent = parent;
        node->data->first = ReadKeyFromFile(file);
        node->data->second = ReadValueFromFile(file);
        
        char info;
        file.read(&info, 1);
        unsigned char left_good = info & (1u << 1);
        unsigned char right_good = info & 1u;
        char balance = (info & 255u) >> 2;
        --balance;
        node->balance = balance;
        ++Size_;
        if (left_good) {
            node->left = ReadNode(node, file);
        }
        if (right_good) {
            node->right = ReadNode(node, file);
        }
        return node;
    }
    return nullptr;
}
template <typename Key, typename Val>
void TDict<Key, Val>::WriteHeader(std::ostream& file){
    int headerSize=0;
    while(FileHeader[headerSize] != 0){
        ++headerSize;
    }
    file.write(FileHeader, headerSize+1);
}
template <typename Key, typename Val>
bool TDict<Key, Val>::HeaderGood(std::istream& file){
    int headerSize=0;
    while(FileHeader[headerSize] != 0){
        ++headerSize;
    }
    char* buff = new char[headerSize+1];
    file.read(buff, headerSize+1);
    bool good = true;
    for(int i = 0; i<headerSize; ++i) {
        if(buff[i] != FileHeader[i]) {
            good = false;
            break;
        }
    }
    delete[] buff;
    return good;
}
template <typename Key, typename Val>
bool TDict<Key, Val>::Save(const char* path) {
    std::ofstream file;
    char empty = 0;
    file.open(path, std::ios::binary);
    if (file.good()) {
        if (root == nullptr) {
            WriteHeader(file);
            empty = 1;
            file.write(&empty, 1);
            file.close();
            return true;
        }
        WriteHeader(file);
        file.write(&empty, 1);
        WriteNode(root, file);
    }
    file.close();
    return true;
}
template <typename Key, typename Val>
bool TDict<Key, Val>::Load(const char* path)
{
    std::ifstream file;
    char empty;
    bool good = false;
    file.open(path, std::ios::binary);
    if (file.good() && HeaderGood(file)) {
        if (root != nullptr) {
            Clear();
        }
        file.read(&empty, 1);
        if(!empty){
            root = ReadNode(nullptr, file);
        }
        good = true;
    }
    file.close();
    return good;
}
template <typename Key, typename Val>
void TDict<Key, Val>::PrintNode(TNode<Key,Val>* node, int depth){
    static const int INDENT_SIZE=5;
    if(node->right!=nullptr){
        PrintNode(node->right, depth+1);
    }
    int totalDepth=depth*INDENT_SIZE;
    for(int i = 0;i < totalDepth; ++i){
        std::cout << " ";
    }
    std::cout << node->data->first << " " << (int)node->balance << "\n";
    
    if(node->left!=nullptr){
        PrintNode(node->left, depth+1);
    }
}
template <typename Key, typename Val>
void TDict<Key, Val>::PrintTree(){
    if(root != nullptr){
        PrintNode(root, 0);
    }
}
