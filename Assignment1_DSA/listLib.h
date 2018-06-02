/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(L1Item<T>* p) : pNext(p) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
};

template <class T>
class L1List {
	L1Item<T>   *_pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
public:
	L1List() : _pHead(NULL), _size(0) {}
	~L1List() {
		delete[] this->_pHead;
		this->_size = 0;
	};

	void    clean() {
	// todo
	};
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	bool listIdRecord(char*id, L1List<T>* listRecord, L1List<T>&record) {
		L1Item<T> *p = this->_pHead;
		while (p!= NULL) {
			if (strcmp(id, p->data.id) == 0) {
				listRecord->insert(p->data);
			}
			p = p->pNext;
		}
		if (listRecord->isEmpty()) {
			return false;
		}
		return true;
	}

	L1Item<T>* getLastPointer() {
		L1Item<T> *p = this->_pHead;
		while (p->pNext != NULL) {
			p = p->pNext;
		}
		return p;
	}

	void printRecordSortId() {
		L1Item<T> *p = this->_pHead;
		while (p != NULL) {
			char time[25];
			strPrintTime(time, p->data.timestamp);
			cout << "id: " << p->data.id << " - ";
			cout << "latitude: " << p->data.x << " - ";
			cout << "longitude: " << p->data.y << " - ";
			cout << "time: " << time << " - " << endl;
			p = p->pNext;
		}
	}

	L1Item<T>* getFirstPointer() {
		return this->_pHead;
	}
	
	bool findRecordFirst(char*id, T& record) {
		L1Item<T> *p = this->_pHead;
		while (p!=NULL) {
			if (strcmp(id, p->data.id) == 0) {
				record = p->data;
				return true;
			}
			p = p->pNext;
		}
		return false;
	}

	T&      at(int i) {
		//todo
		L1Item<T> *p = _pHead;
		if (i == 0) {
			return _pHead->data;
		}
		while (i > 0)
		{
			p = p->pNext;
			i--;
		}
		return p->data;
	};
	T&      operator[](int i) {
		//todo
		L1Item<T> *p = _pHead;
		if (i == 0) {
			return _pHead->data;
		}
		while (i > 0)
		{
			p = p->pNext;
			i--;
		}
		return p->data;
	};

	bool    find(T& a, int& idx) {
		
	};
	bool	insert(T& a) {
		if (this->_pHead == NULL) {
			L1Item<T>* temp = new L1Item<T>(a);
			this->_pHead = temp;
			this->_size++;
			return true;
		}
		else {
			L1Item<T> *p = this->_pHead;
			while (p->pNext != NULL) {
				p = p->pNext;
			}
			L1Item<T>* temp = new L1Item<T>(a);
			p->pNext = temp;
			this->_size++;
			return true;
		}
		return false;
	}
	int     insert(int i, T& a) {
		//todo
		L1Item<T> * temp = _pHead;
		//if (i == 0){//insert head
		//	L1Item<T> *p = new L1Item<T>(a);
		//	p->pNext = _pHead;
		//	_pHead = p;
		//	_size++;
		//	return 0;
		//}
		while (i > 1)
		{
			temp = temp->pNext;
			i--;
		}
		L1Item<T> *newItem = new L1Item<T>(a);
		newItem->pNext = temp->pNext;
		temp->pNext = newItem;
		_size++;
		return 0;

	};
	int     remove(int i) {
		L1Item<T>*p = this->_pHead;
		L1Item<T>* curr;
		while (i < 1) {
			p = p->pNext;
			i--;
		}
		curr = p->pNext;
		p->pNext = curr->pNext;
		curr->pNext = NULL;
		delete curr;
		this->_size--;
	};

    int     push_back(T& a);
    int     insertHead(T& a);
    int     insertHead() {
        _pHead = new L1Item<T>(_pHead);
        _size++;
        return 0;
    }

    int     removeHead();
    int     removeLast();

	void    reverse() {
		L1Item<T> *curr = this->_pHead;
		L1Item<T> *prev = NULL;
		L1Item<T> *next = NULL;
		while (curr) {
			next = curr->pNext;
			curr->pNext = prev;
			prev = curr;
			curr = next;
		}
		this->_pHead = prev;
	};

    void    traverse(void (*op)(T&)) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}



#endif //A01_LISTLIB_H