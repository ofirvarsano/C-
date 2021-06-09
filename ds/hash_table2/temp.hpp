

/*
template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT>::HashIterator(VectorCIter a_vecItr, VectorCIter a_vecEnd) 
: m_vecItr(a_vecItr)
, m_vecEnd(a_vecEnd)
, m_listItr(m_vecItr->Begin()) {
    while(m_listItr == m_vecItr->End() && m_vecItr != m_vecEnd){
        m_vecItr++;
        if(m_vecItr != m_vecEnd) {
        	m_listItr = m_vecItr->Begin();
        }
	}
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::Next() {
    m_listItr++;
    if(m_listItr == m_vecItr->End() && m_vecItr != m_vecEnd) {
        do {
            m_vecItr++;
            if(m_vecItr != m_vecEnd) {
            	m_listItr = m_vecItr->Begin();
            }
        }
        while(m_listItr == m_vecItr->End());
    }
    return *this;
}

template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::End() {
	while(m_vecItr->next() != m_vecEnd) {
		m_vecItr++;
	}
	m_listItr = m_vecItr->Begin();
	while(m_listItr != m_vecItr->End() {
 	   m_listItr++;
	}
    if(m_listItr == m_vecItr->End() && m_vecItr != m_vecEnd) {
        do {
            m_vecItr++;
            if(m_vecItr != m_vecEnd) {
            	m_listItr = m_vecItr->Begin();
            }
        }
        while(m_listItr == m_vecItr->End());
    }
    return *this;
}
*/
/*
template<typename KeyT, typename ValueT>
HashIterator<KeyT, ValueT> HashIterator<KeyT, ValueT>::Prev() {
    if(m_listItr == m_vecItr->Begin()) {
        do{
            m_vecItr --;
            m_listItr = m_vecItr->End();
        }
        while(m_listItr == m_vecItr->Begin());
    }
    m_listItr--;
    return *this;
}
*/
