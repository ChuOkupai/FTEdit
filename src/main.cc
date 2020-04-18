#include <cstdlib>
#include <ctime>
#include <QDebug>
#include "FTEdit.hh"

int main(void)
{
	Editor e;

	std::srand(std::time(nullptr));
	for (int i = 0; i < 10; ++i)
	{
		if (std::rand() % 2)
		{
			e.detach();
			qDebug() << "New tree: " << e.getSelection()->getProperties().getName() << "\n";
		}
		else
		{
			e.getEvents().append(Event(e.generateName(PREFIX_EVENT)));
			qDebug() << "New event: " << e.getEvents().last().getProperties().getName() << "\n";
		}
		
	}
	return (0);
}
