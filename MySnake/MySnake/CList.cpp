
#ifdef CLIST_H


template<class T>
Node<T>::Node() :item(T()),next(nullptr) {};

template<class T>
Node<T>::Node(T I, Node<T>* nd) : item(I), next(nd) {}

template<class T>
Node<T>::Node(const Node<T>& node) : item(node.item), next(node.item){}

template<class T>
Node<T>& Node<T>::operator=(const Node<T>& node)
{
	return *this(node);
}

template<class T>
Node<T>::~Node()
{
	if (this->next) {
		this->next->~Node();
	}
	else {
	}
}


#endif

