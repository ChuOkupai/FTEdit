#pragma once
#ifndef PROPERTIES_H
#define PROPERTIES_H 

#include <iostream>

class Properties
{
	public:
		Properties(QString name);
		~Properties();

		QString const getName();
		QString const getDesc();
		bool const getKeep();

		void setName(QString name);
		void setDesc(QString desc);
		void setKeep(bool keep);

		void decrementRefCount();
		void incrementRefCount();
		bool canBeRemoved();

	private:
		QString name;
		QString desc;
		int refCount;
		bool keep;
};
#endif
