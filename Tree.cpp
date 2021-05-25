#include "Tree.h"

void Tree::insert_to_node(int key, Node* node) {
    if (node->count == this->t * 2 - 1) {
        Node* child1 = restruct(node);
        int pos = getChildPosition(child1->parent, child1);
        if (child1->parent->keys[pos] > key) {
            addKeyToNode(child1, key);
        }
        else {
            Node* child2 = child1->parent->children[pos + 1];
            addKeyToNode(child2, key);
        }
    }
    else {
        addKeyToNode(node, key);
    }
}
    
int Tree::findPlaceToInsert(Node* node, int key) {
    for (int i = 0; i < node->count; i++) {
        if (node->keys[i] > key) {
            return i;
        }
    }
    return -1;
}
void Tree::updateNode(Node** node, int* temp) {
    delete (*node)->keys;
    (*node)->count = (*node)->count + 1;
    (*node)->keys = new int[(*node)->count];
    copyArray(&((*node)->keys), temp, (*node)->count);
}

int Tree::getChildPosition(Node* parent, Node* child) {
    for (int i = 0; i < parent->countSons; i++) {
        if (parent->children[i] == child) {
            return i;
        }
    }
    return -1;
}

int Tree::getKeyPosition(Node* node, int key) {
    for (int i = 0; i < node->count; i++) {
        if (node->keys[i] == key) {
            return i;
        }
    }
    return -1;
}

void Tree::copyArray(int** arr1, int* arr2, int count) {
    for (int i = 0; i < count; i++) {
        (*arr1)[i] = arr2[i];
    }
}

void Tree::copyArray(int** arr1, int* arr2, int start, int end) {
    int index = 0;
    for (int i = start; i < end; i++) {
        (*arr1)[index] = arr2[i];
        index++;
    }
}

void Tree::copyArray(int** arr1, int* arr2, int start, int end, int difference) {
    for (int i = start; i < end + difference; i++) {
        (*arr1)[i] = arr2[i - difference];
    }
}

void Tree::copyArray(Node*** arr1, Node** arr2, int count) {
    for (int i = 0; i < count; i++) {
        (*arr1)[i] = arr2[i];
    }
}

void Tree::Tree::copyArray(Node*** arr1, Node** arr2, int start, int end) {
    int index = 0;
    for (int i = start; i < end; i++) {
        (*arr1)[index] = arr2[i];
        index++;
    }
}

void Tree::copyArray(Node*** arr1, Node** arr2, int start, int end, int difference) {
    for (int i = start; i < end + difference; i++) {
        (*arr1)[i] = arr2[i - difference];
    }
}

Node* Tree::restruct(Node* node) {
    if (node->count < (2 * t - 1)) return nullptr;

    Node* child1 = new Node;
    child1->keys = new int[t - 1];
    for (int j = 0; j < (t - 1); j++) child1->keys[j] = node->keys[j];
    child1->count = t - 1;
    if (node->countSons > 0) {
        child1->children = new Node * [t];
        for (int i = 0; i < t; i++) {
            child1->children[i] = node->children[i];
            child1->children[i]->parent = child1;
        }
        child1->isLeaf = false;
        child1->countSons = t;
    }
    else {
        child1->isLeaf = true;
        child1->countSons = 0;
    }

    Node* child2 = new Node;
    child2->keys = new int[t - 1];
    for (int j = 0; j < (t - 1); j++) child2->keys[j] = node->keys[j + t];
    child2->count = t - 1;
    if (node->countSons > 0) {
        child2->children = new Node * [t];
        for (int i = 0; i < t; i++) {
            child2->children[i] = node->children[i + t];
            child2->children[i]->parent = child2;
        }
        child2->isLeaf = false;
        child2->countSons = t;
    }
    else {
        child2->isLeaf = true;
        child2->countSons = 0;
    }

    if (node->parent == nullptr) {
        int temp = node->keys[t - 1];
        delete[] node->keys;
        node->keys = new int[1];
        node->keys[0] = temp;
        if (node->countSons >= 2) {
            delete[] node->children;
        }
        node->children = new Node * [2];
        node->children[0] = child1;
        node->children[1] = child2;
        node->isLeaf = false;
        node->count = 1;
        node->countSons = 2;
        child1->parent = node;
        child2->parent = node;
    }
    else {
        insert_to_node(node->keys[t - 1], node->parent);
        int i = getChildPosition(node->parent, node);
        Node** temp = new Node * [node->parent->countSons + 1];
        copyArray(&temp, node->parent->children, i);
        temp[i + 1] = child2;
        temp[i] = child1;
        if (i != node->parent->countSons - 1) {
            copyArray(&temp, node->parent->children, i + 2, node->parent->countSons, 1);
        }

        node->parent->countSons = node->parent->countSons + 1;
        node->parent->children = new Node * [node->parent->countSons];
        copyArray(&(node->parent->children), temp, node->parent->countSons);
        delete[]temp;
        child1->parent = node->parent;
        child2->parent = node->parent;
        node->parent->isLeaf = false;
        free(node);
    }
    return child1;
}

void Tree::deletenode(Node* node) {
    if (node != nullptr) {
        for (int i = 0; i < node->countSons; i++) {
            if (node->children[i] != nullptr) deletenode(node->children[i]);
            else {
                delete(node);
                break;
            }
        }
    }
}

bool Tree::searchKey(int key, Node* node) {
    if (node->isLeaf) {
        for (int i = 0; i < node->count; i++) {
            if (key == node->keys[i]) {
                return true;
            }
        }
        return false;
    }
    else {
        for (int i = 0; i < node->count; i++) {
            if (key == node->keys[i]) return true;
        }
        for (int i = 0; i < node->countSons; i++) {
            if (searchKey(key, node->children[i])) return true;
        }
    }
    return false;
}

int Tree::searchKeyLevel(int key, Node* node, int level) {
    if (node->isLeaf) {
        for (int i = 0; i < node->count; i++) {
            if (key == node->keys[i]) {
                return level;
            }
        }
        return 0;
    }
    else {
        for (int i = 0; i < node->count; i++) {
            if (key == node->keys[i]) return level;
        }
        for (int i = 0; i < node->countSons; i++) {
            int k = searchKeyLevel(key, node->children[i], level + 1);
            if (k != 0) return k;
        }
    }
    return 0;
}

void Tree::remove(int key, Node* node) {
    bool isLeaf = node->isLeaf;
    bool inArray = isInArray(node->keys, key, node->count);
    if (isLeaf && inArray) {
        if (node->count > t - 1 || node == root) removeKeyFromNode(key, node);
    }
    else if (!isLeaf && inArray) {
        int keyPos = getKeyPosition(node, key);
        Node* childRight = node->children[keyPos + 1];
        Node* childLeft = node->children[keyPos];
        if (childLeft->count == t - 1 && childRight->count == t - 1) {
            Node* newNode = mergeNodes(childLeft, childRight, node);
            removeKeyFromNode(key, node);
            if (newNode->isLeaf) removeKeyFromNode(key, newNode);
            else remove(key, newNode);
        }
        else if (childRight->count > t - 1) {
            turnLeft(childLeft, node, childRight);
            remove(key, childLeft);
        }
        else if (childLeft->count > t - 1) {
            turnRight(childLeft, node, childRight);
            remove(key, childRight);
        }
    }
    else if (!isLeaf && !inArray) {
        int keyPos = -1;
        for (int i = 0; i < node->count; i++) {
            if (node->keys[i] > key) {
                keyPos = i;
                break;
            }
        }
        Node* child;
        if (keyPos != -1) {
            child = node->children[keyPos];
        }
        else {
            child = node->children[node->countSons - 1];
        }
        if (child->count == t - 1) {
            if (keyPos == 0) {
                Node* right = node->children[keyPos + 1];
                if (right->count > t - 1) {
                    turnLeft(child, node, right);
                    remove(key, child);
                }
                else {
                    Node* newNode = mergeNodes(child, right, node);
                    removeKeyFromNode(node->keys[keyPos], node);
                    if (node == root && node->count == 0) {
                        free(node);
                        root = newNode;
                        root->parent = nullptr;
                    }
                    remove(key, newNode);
                }
            }
            else if (keyPos == -1) {
                Node* left = node->children[node->countSons - 2];
                if (left->count > t - 1) {
                    turnRight(left, node, child);
                    remove(key, child);
                }
                else {
                    Node* newNode = mergeNodes(left, child, node);
                    removeKeyFromNode(node->keys[node->count - 1], node);
                    if (node == root && node->count == 0) {
                        free(node);
                        root = newNode;
                        root->parent = nullptr;
                    }
                    remove(key, newNode);
                }
            }
            else {
                Node* right = node->children[keyPos + 1];
                Node* left = node->children[keyPos - 1];
                if (left->count > t - 1) {
                    turnRight(left, node, child);
                    remove(key, child);
                }
                else if (right->count > t - 1) {
                    turnLeft(child, node, right);
                    remove(key, child);
                }
                else {
                    Node* newNode = mergeNodes(left, child, node);
                    removeKeyFromNode(node->keys[keyPos - 1], node);
                    if (node == root && node->count == 0) {
                        free(node);
                        root = newNode;
                        root->parent = nullptr;
                    }
                    remove(key, newNode);
                }
            }
        }
        else {
            remove(key, child);
        }
    }
    else {
        return;
    }
}

void Tree::turnRight(Node* left, Node* parent, Node* right) {
    int pos = getChildPosition(parent, left);
    addKeyToNode(right, parent->keys[pos]);
    parent->keys[pos] = takeKey(left, left->count - 1);
    if (left->countSons > 0) {
        Node* child = takeChild(left, left->countSons - 1);
        child->parent = right;
        addChildToNode(right, child, 0);
    }
}
 
void Tree::turnLeft(Node* left, Node* parent, Node* right) {
    int pos = getChildPosition(parent, right);
    addKeyToNode(left, parent->keys[pos - 1]);
    parent->keys[pos - 1] = takeKey(right, 0);
    if (right->countSons > 0) {
        Node* child = takeChild(right, 0);
        child->parent = left;
        addChildToNode(left, child, left->countSons);
    }
}
 
Node* Tree::mergeNodes(Node* node1, Node* node2, Node* parent) {
    Node* newNode = new Node;

    newNode->keys = new int[node1->count + node2->count + 1];
    for (int i = 0; i < node1->count; i++) {
        newNode->keys[i] = node1->keys[i];
    }
    newNode->keys[node1->count] = parent->keys[getChildPosition(parent, node1)];
    for (int i = 0; i < node2->count; i++) {
        newNode->keys[i + node1->count + 1] = node2->keys[i];
    }
    newNode->count = node1->count + node2->count + 1;

    if (node1->countSons > 0 && node2->countSons > 0) {
        newNode->children = new Node * [node1->countSons + node2->countSons + 1];
        for (int i = 0; i < node1->countSons; i++) {
            newNode->children[i] = node1->children[i];
            newNode->children[i]->parent = newNode;
        }
        for (int i = 0; i < node2->countSons; i++) {
            newNode->children[i + node1->countSons] = node2->children[i];
            newNode->children[i + node1->countSons]->parent = newNode;
        }
        newNode->countSons = node1->countSons + node2->countSons;
    }

    if (newNode->countSons > 0) {
        newNode->isLeaf = false;
    }
    else {
        newNode->isLeaf = true;
    }

    newNode->parent = node1->parent;
    removeChildFromNode(node2, parent);
    parent->children[getChildPosition(parent, node1)] = newNode;
    free(node1);
    free(node2);
    return newNode;
}

int Tree::takeKey(Node* node, int pos) {
        int key = node->keys[pos];
        int* temp = new int[node->count - 1];
        if (pos == 0) {
            copyArray(&temp, node->keys, 1, node->count);
        }
        else if (pos == node->count - 1) {
            copyArray(&temp, node->keys, node->count - 1);
        }
        delete[] node->keys;
        node->count--;
        node->keys = new int[node->count];
        copyArray(&(node->keys), temp, node->count);
        delete[]temp;
        return key;
    }
Node* Tree::takeChild(Node* node, int pos) {
    Node* child = node->children[pos];
    Node** temp = new Node * [node->countSons - 1];
    if (pos == 0) {
        copyArray(&temp, node->children, 1, node->countSons);
    }
    else if (pos == node->countSons - 1) {
        copyArray(&temp, node->children, node->countSons - 1);
    }
    delete[] node->children;
    node->countSons--;
    node->children = new Node * [node->countSons];
    copyArray(&(node->children), temp, node->countSons);
    delete[] temp;
    return child;
}

void Tree::removeKeyFromNode(int key, Node* node) {
    int* temp = new int[node->count - 1];
    int index = 0;
    for (int i = 0; i < node->count; i++) {
        if (node->keys[i] != key) {
            temp[index++] = node->keys[i];
        }
    }
    delete[]node->keys;
    node->count--;
    node->keys = new int[node->count];
    copyArray(&(node->keys), temp, node->count);
    delete[]temp;
}
 
void Tree::removeChildFromNode(Node* child, Node* node) {
    Node** temp = new Node * [node->countSons - 1];
    int index = 0;
    for (int i = 0; i < node->countSons; i++) {
        if (node->children[i] != child) {
            temp[index++] = node->children[i];
        }
    }
    delete[]node->children;
    node->countSons--;
    node->children = new Node * [node->countSons];
    copyArray(&(node->children), temp, node->countSons);
    delete[]temp;
}
 
void Tree::printNode(Node* node) {
    if (node->isLeaf) {
        for (int i = 0; i < node->count; i++) {
            cout << node->keys[i] << " ";
        }
    }
    else {
        for (int i = 0; i < node->count; i++) {
            printNode(node->children[i]);
            cout << node->keys[i] << " ";
        }
        printNode(node->children[node->countSons - 1]);
    }
}

void Tree::printNodeS(Node* node) {
    if (node->isLeaf) {
        for (int i = 0; i < node->count; i++) {
            cout << node->keys[i] << " ";
        }
    }
    else {
        for (int i = 0; i < node->count; i++) {
            cout << "( ";
            printNodeS(node->children[i]);
            cout << ") ";
            cout << node->keys[i] << " ";
        }
        cout << "( ";
        printNodeS(node->children[node->countSons - 1]);
        cout << ") ";
    }
}
 
void Tree::addKeyToNode(Node* node, int  key) {
    if (node->count == 0) {
        node->count = 1;
        node->keys = new int[node->count];
        node->keys[0] = key;
    }
    else {
        for (int i = 0; i < node->count; i++) {
            if (node->keys[i] > key) {
                int* temp = new  int[node->count + 1];
                copyArray(&temp, node->keys, i);
                temp[i] = key;
                copyArray(&temp, node->keys, i + 1, node->count, 1);
                updateNode(&node, temp);
                delete[]temp;
                return;
            }
            else if (i == node->count - 1) {
                int* temp = new  int[node->count + 1];
                copyArray(&temp, node->keys, i + 1);
                temp[i + 1] = key;
                updateNode(&node, temp);
                delete[] temp;
                return;
            }
        }
    }
}
 
void Tree::addChildToNode(Node* node, Node* child, int pos) {
    if (node->countSons == 0) {
        node->children = new Node * [++node->countSons];
        node->children[0] = child;
    }
    else {
        Node** temp = new Node * [node->countSons + 1];
        if (pos == 0) {
            int index = 1;
            temp[0] = child;
            for (int i = 0; i < node->countSons; i++) {
                temp[index] = node->children[i];
                index++;
            }
        }
        else {
            copyArray(&temp, node->children, node->countSons);
            temp[node->countSons] = child;
        }

        delete[] node->children;
        node->countSons++;

        node->children = new Node * [node->countSons];
        copyArray(&(node->children), temp, node->countSons);
        delete[] temp;
    }
}

Node* Tree::strToNode(string line, Node* parent) {
    Node* node = new Node;
    node->count = 0;
    node->countSons = 0;
    node->isLeaf = true;
    node->parent = parent;
    int counter = 0;
    string subline = "";
    string digit = "";
    int size = line.size();
    for (int i = 0; i < size; i++) {
        if (line[i] == '(') {
            counter++;
        }
        else if (line[i] == ')') {
            counter--;
            if (counter == 0) {
                node->isLeaf = false;
                Node* child = strToNode(subline.substr(2), node);
                addChildToNode(node, child, node->countSons);
                subline = "";
            }
        }
        else if (counter == 0 && '0' <= line[i] && line[i] <= '9') {
            digit += line[i];
        }
        else if (counter == 0 && line[i] == ' ' && digit != "") {
            int num = stoi(digit);
            addKeyToNode(node, num);
            digit = "";
        }
        if (counter > 0) {
            subline += line[i];
        }
    }
    return node;
}

bool Tree::isInArray(int* arr, int key, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

void Tree::addKeyToArray(int** array, int key, int* arraySize) {
    int* temp = new int[*arraySize + 1];
    copyArray(&(temp), *array, *arraySize);
    temp[*arraySize] = key;
    (*arraySize)++;
    delete[] * array;
    *array = new int[*arraySize];
    copyArray(array, temp, *arraySize);
    delete[] temp;
}

void Tree::updateArray(int** array, int key, int size) {
    for (int i = size - 1; i > 0; i--) {
        (*array)[i] = (*array)[i - 1];
    }
    (*array)[0] = key;
}

int Tree::getBottomRightNodeLevel() {
    Node* ptr = root;
    int level = 1;
    while (ptr != nullptr && ptr->isLeaf == false) {
        for (int i = 0; i < ptr->count; i++) {
            if ((i + 1 == ptr->count) && ptr->countSons > 0 && ptr->children[i + 1] != nullptr) {
                ptr = ptr->children[i + 1];
                level++;
                break;
            }
        }
    }
    return level;
}
 
void Tree::calculateCache(int size, string str) {
    string digit = "";
    int arraySize = 0;
    int* array = new int[1];
    for (int i = 0; i < str.size(); i++) {
        if ((str[i] == ' ' && digit != "") || (i == str.size() - 1 && '0' <= str[i] && str[i] <= '9')) {
            if (i == str.size() - 1) digit += str[i];
            int num = stoi(digit);
            addKeyToArray(&array, num, &arraySize);
            digit = "";
            num = 0;
        }
        else if ('0' <= str[i] && str[i] <= '9') {
            digit += str[i];
        }
    }
    cacheArray = new int[size];
    for (int i = 0; i < size; i++) {
        cacheArray[i] = 0;
    }
    for (int i = 0; i < arraySize; i++) {
        int level = searchKeyLevel(array[i], root, 1);
        if (level == 0) {
            level = getBottomRightNodeLevel();
        }
        if (!isInArray(cacheArray, array[i], size)) {
            updateArray(&cacheArray, array[i], size);
            cache += level;
        }
        noCache += level;
    }
    delete[]array;
}

Tree::Tree() {
    root = nullptr;
}
 
Tree::~Tree() { if (root != nullptr) deletenode(root); }

void Tree::setT(int t) {
    this->t = t;
}


void Tree::insert(int key) {
    if (root == nullptr) {
        Node* newRoot = new Node;
        newRoot->keys = new int[1];
        newRoot->keys[0] = key;
        newRoot->count = 1;
        newRoot->countSons = 0;
        newRoot->isLeaf = true;
        newRoot->parent = nullptr;
        root = newRoot;
    }
    else {
        Node* ptr = root;
        while (ptr != nullptr && ptr->isLeaf == false) {
            for (int i = 0; i < ptr->count; i++) {
                if (key < ptr->keys[i] && ptr->countSons > 0 && ptr->children[i] != nullptr) {
                    ptr = ptr->children[i];
                    break;
                }
                else if ((i + 1 == ptr->count) && (key > ptr->keys[i]) && ptr->countSons > 0 && ptr->children[i + 1] != nullptr) {
                    ptr = ptr->children[i + 1];
                    break;
                }
            }
        }
        insert_to_node(key, ptr);
    }
}

bool Tree::search(int key) {
    return searchKey(key, this->root);
}
 
void Tree::remove(int key) {
    remove(key, root);
}

void Tree::load(string line) {
    root = strToNode(line.substr(2, line.size() - 3), nullptr);
}

void Tree::print() {
    printNode(root);
    cout << endl;
}

void Tree::printS() {
    cout << this->t << endl << "( ";
    printNodeS(root);
    cout << ") " << endl;
}

void Tree::getCache(string str) {
    int index = 0;
    string substr = "";
    while (str[index] != ' ') {
        substr[index] = str[index];
        index++;
    }
    int size = stoi(substr);
    calculateCache(size, str.substr(index + 1));
    cout << "NO CACHE: " << noCache << " CACHE: " << cache << endl;
}