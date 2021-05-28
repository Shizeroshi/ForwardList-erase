#include <iostream>

using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------------------\n"

class Element
{
	int Data; // Значение элемента
	Element* pNext; // Указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class Iterator;
	friend class ForwardList;
};

int Element::count = 0; // Инициализация статической переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr)
	{
		this->Temp = Temp;
		cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "IDestructor:\t" << this << endl;
	}

	// Operators

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	
	Element*& operator->()
	{
		return Temp;
	}
	Element* get_current_address()
	{
		return Temp;
	}
};

class ForwardList
{
	Element* Head;
	int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	// Operators

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}

	// Adding elements

	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		// Этот метод не умеет работать с пустым списком
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}

		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		//Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++, Temp = Temp->pNext)
			if (Temp->pNext == nullptr)break;
		//New->pNext = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	// Erasing elements

	void pop_front()
	{
		// Прежде чем исключить элемент из списка, нужно запомнить его адрес, для того чтобы можно было шото там
		Element* Temp = Head;
		// Удаляем элемент из списка
		Head = Head->pNext;
		// Удаляем элемент из памяти
		delete Temp;
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		//Element* Temp2 = Head = Head->pNext;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
			//Temp2 = Temp2->pNext;
			if (Temp->pNext->pNext == nullptr)
			{
				delete Temp->pNext;
				Temp->pNext = nullptr;
			}
		}
		size--;
	}

	void erase(int index)
	{
		if (index > size)return;
		if (index == 0)
		{
			pop_front();
			return;
		}

		// Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		// Запоминаем адрес удаляемого элемента
		Element* to_del = Temp->pNext;
		// Исключаем удаляемый элемент из списка
		Temp->pNext = Temp->pNext->pNext;
		// Удаляем элемент из памяти
		delete to_del;
		size--;
	}

	// Methods

	void Print()
	{
		/*Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		//for(Element* Temp = Head; Temp; Temp = Temp->pNext)
		for(Iterator Temp = Head; Temp != nullptr; Temp++)
			//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			cout << Temp.get_current_address() << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << endl;
		cout << "Кол-во элементов в списке: " << size << endl;
		cout << "Общее кол-во элементов: " << Element::count << endl;
	}
};

//#define BaseCheck

int main()
{
	setlocale(LC_ALL, "");
	system("color 0A");

	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList List;

	for (int i = 0; i < n; i++)
	{
		List.push_back(rand() % 100);
	}


	List = List;
	List.Print();



#ifdef BaseCheck
	/*cout << delimiter << endl;
List.pop_front();
List.Print();
cout << delimiter << endl;
List.pop_back();
List.Print();*/
	int value;
	int index;
	cout << "Добавить: "; cin >> value;
	cout << "Индекс: "; cin >> index;
	List.insert(value, index);
	List.Print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	List.erase(index);
	List.Print();
#endif // BaseCheck


	/*
	cout << "Ещё 1 список:\n";
	ForwardList List2;
	List2.push_back(3);
	List2.push_back(2);
	List2.push_back(1);
	List2.Print();*/

	//ForwardList List2(List); // CopyConstructor - Во время создания
	//List2.Print();

	//ForwardList List3;
	//List3 = List2; // CopyAssignment - После создания
	//List3.Print();


}