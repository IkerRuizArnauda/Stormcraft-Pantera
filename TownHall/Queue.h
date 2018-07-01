/*****************************************************************************
EQIMBase, the Base C++ classes for handling EQIM
Copyright (C) 2003-2004 Lax

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2,
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Usage of these EQIM clients and derivatives subject you to the rules of
the EQIM network.  Access to the network is restricted to paying
subscribers of the online game EverQuest.  This software and the EQIM
protocol is provided in good faith to the EverQuest community, and not
intended for malicious purposes.  Usage of this software for malicious
purposes is prohibited and any distribution, usage, or mention of
malicious activity can and will be reported to the administrators of the
EQIM network.
******************************************************************************/

// Queue.hpp
//
//////////////////////////////////////////////////////////////////////

#ifndef QUEUE_H
#define QUEUE_H

template <class QT>
class Queue
{
public:
	Queue();
	virtual ~Queue();

	bool Empty() const;

	QT Pop();
	void Push(const QT&);

	void Remove(const QT&);

	QT& Peek();

	void Clear();


private:
	struct QueueNode
	{
		QT data;
		QueueNode* prev;
	};
	CSemaphore S;
	QueueNode* head;
	QueueNode* tail;
};

template <class QT>
Queue<QT>::Queue(void)
{
	head=NULL;
	tail=NULL;
}

template <class QT>
Queue<QT>::~Queue(void)
{
	Clear();
}


template <class QT>
bool Queue<QT>::Empty(void) const
{
	if(tail) return false;
	return true;
}

template <class QT>
QT Queue<QT>::Pop(void)
{
	CLock L(&S,true);

	QT TempData;

	if(tail)
	{
		QueueNode* Temp;

		Temp = tail;
		TempData = tail->data;

		tail = tail->prev;
		if (!tail)
			head=0;
		delete Temp;
	}
	return TempData;
}

template <class QT>
void Queue<QT>::Push(const QT& iData)
{
	CLock L(&S,true);

	QueueNode* Temp = new QueueNode;//(iData, 0);
	Temp->prev=NULL;
	Temp->data=iData;

	if (head)
	{
		//head->Prev(Temp);
		head->prev=Temp;
		head=head->prev;
	}
	else
	{
		head=Temp;
		tail=head;
	}
}

template <class QT>
QT& Queue<QT>::Peek(void)
{
	return tail->data;
}

template <class QT>
void Queue<QT>::Clear(void)
{
	CLock L(&S,true);
	if(head)
	{
		QueueNode* Temp;
		QueueNode* Index;

		Temp  = tail;
		Index = tail;

		do
		{
			Index = Temp->prev;
			delete Temp;
		} while(Temp = Index);

		tail = 0;
		head = 0;
	}
}

#endif // QUEUE_H
