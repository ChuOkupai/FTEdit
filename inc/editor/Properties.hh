#pragma once
#include <QString>

class Properties
{
	public:
		Properties(QString name, bool keep = false);
		~Properties();

		QString getName() const;
		QString getDesc() const;
		bool getKeep() const;

		void setName(QString name);
		void setDesc(QString desc);
		void setKeep(bool keep);

		void decrementRefCount();
		void incrementRefCount();
		bool canBeRemoved();

	protected:
		QString name;
		QString desc;
		int refCount;
		bool keep;
};
