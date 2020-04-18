#pragma once
#include <QString>

class Properties
{
protected:
	QString	name;
	QString	desc;
	int		refCount;
	bool	keep;

public:
	Properties(QString name, bool keep = false);
	~Properties();

	QString	getName() const;
	QString	getDesc() const;
	bool	getKeep() const;

	void	setName(QString name);
	void	setDesc(QString desc);
	void	setKeep(bool keep);

	void	decrementRefCount();
	void	incrementRefCount();
	bool	canBeRemoved();
};
