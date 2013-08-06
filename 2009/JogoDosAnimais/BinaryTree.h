
#ifndef _BinaryTree_h
#define _BinaryTree_h

#include <iostream>


template <class DataType>
class BinaryTree
{
	private:
		typedef BinaryTree<DataType> Node;

		DataType m_data;
		Node* m_parent;
		Node* m_right;
		Node* m_left;

	public:
		BinaryTree()
		: m_data(0)
		, m_parent(0)
		, m_right(0)
		, m_left(0)
		{
		}

		explicit BinaryTree(DataType data, Node* parent = 0)
		: m_data(data)
		, m_parent(parent)
		, m_right(0)
		, m_left(0)
		{
		}

		virtual ~BinaryTree()
		{
			if (m_right) {
				delete m_right;
				m_right = 0;
			}

			if (m_left) {
				delete m_left;
				m_left = 0;
			}

			if (m_data)	{
				delete m_data;
				m_data = 0;
			}
		}

		DataType data() const
		{
			return m_data;
		}

		unsigned int count()
		{
			unsigned int result = 1;

			if (m_right)
				result += m_right->count();

			if (m_left)
				result += m_left->count();

			return result;
		}

		Node* addRight(DataType data)
		{
			if (m_right)
			{
				delete m_right;
				m_right = 0;
			}

			m_right = new Node(data, this);
			return m_right;
		}

		Node* right() const
		{
			return m_right;
		}

		Node* addLeft(DataType data)
		{
			if (m_left)
			{
				delete m_left;
				m_left = 0;
			}

			m_left = new Node(data, this);
			return m_left;
		}

		Node* left() const
		{
			return m_left;
		}

		Node* parent() const
		{
			return m_parent;
		}
};

#endif

