#include "Gate.hh"
#include <cmath>

Gate::Gate(QString name,bool keep) :Node(),prop(name, keep)
{}

Gate::~Gate()
{}

Properties& Gate::getProperties()
{
	return (prop);
}

QList<Node*>& Gate::getChildren()
{
	return (children);
}

Node* Gate::search(QPoint around)
{ 
	if (around.x() >= position.x() && around.x() < position.x() + (CARD_X) 
	&& around.y() <= position.y() && around.y() > position.y() - (CARD_Y + CARD_GAP_Y))
		return (this);
	Node *n = nullptr;
	for (int i = 0;
	i < children.size() && !(n = children.at(i)->search(around)); ++i);
	return (n);
}

QPoint Gate::top_node_coord(QPoint cpt)
{
	QPoint max;
	QPoint tmp;
	if(getChildren().size()>0)
	{
		if(!parent || parent->getChildren().indexOf(this) == 0)
		{
			for(int i = 0; i<(getChildren().size()/2);i++)
			{	
				cpt.setX(cpt.x()+CARD_X);
			}
		}
		max = cpt;
		for(int i = 0; i<(getChildren().size());i++)
		{
			tmp = this->getChildren()[i]->top_node_coord(cpt); 
			if(tmp.x() > max.x())
			{
				max.setX(tmp.x());
			}
		}
		return max;
	}
	else
	{
		return cpt;
	}
}

void Gate::balanceNodePos()
{
	int size = getChildren().size();
	int halfsize = size/2;
	int odd = size%2;
	QPoint tmp;
	QPoint top_pos;
	top_pos.setY(0);
	
	if(!parent)
	{
		this->setPosition(this->top_node_coord(top_pos));
	}
	
	if(size != 0)
	{
		tmp.ry() = this->getPosition().y() + CARD_Y+ CARD_GAP_Y;
		if(odd)
			tmp.rx() = this->getPosition().x() - ((halfsize) * CARD_X);
		else
			tmp.rx() = this->getPosition().x() - ((halfsize) * CARD_X)+(CARD_X/2);
		
		getChildren()[0]->setPosition(tmp);
		if(parent)
		{
			for(int k = 0;k<parent->getChildren().indexOf(this);k++)
				{	
					if(parent->getChildren()[k]->search(getChildren()[0]->getPosition()))
					{
						if(!odd)
							tmp.rx() = this->getPosition().x() + CARD_X;
						else
							tmp.rx() = this->getPosition().x() + CARD_X/2;
						tmp.ry() = this->getPosition().y();
						this->setPosition(tmp);
						this->balanceNodePos();
					}
				}
		}
		getChildren()[0]->balanceNodePos();
	}
	if(size >= 2)
	{
		for(int i = 1;i<size;i++)
		{
			tmp.rx() = getChildren()[i-1]->getPosition().x() + CARD_X;
			tmp.ry() = getChildren()[i-1]->getPosition().y();
			
			getChildren()[i]->setPosition(tmp);	
			if(parent)
			{
				
				for(int k = 0;k<parent->getChildren().indexOf(this);k++)
				{	
					if(parent->getChildren()[k]->search(getChildren()[i]->getPosition()))
					{
						if(!odd)
							tmp.rx() = this->getPosition().x() + CARD_X;
						else
							tmp.rx() = this->getPosition().x() + CARD_X/2;
						tmp.ry() = this->getPosition().y();
						this->setPosition(tmp);
						this->balanceNodePos();
					}
				}
			}
			getChildren()[i]->balanceNodePos();
		}
	}
}

/*
void Gate::balanceNodePos()//works sorta
{
	int size = getChildren().size();
	int halfsize = size/2;
	int odd = size%2;
	int tmp_2 = 0;
	int t = 0;
	QPoint tmp;
	QPoint top_pos;
	top_pos.setY(0);

	if(!parent)
	{
		this->setPosition(this->top_node_coord(top_pos));
	}
	
	for(int i =0; i<size ; i++)
	{
		if(odd)
		{	
			tmp.ry() = this->getPosition().y() + (CARD_Y +CARD_GAP_Y);

			t = i-halfsize;
			tmp.rx() = this->getPosition().x() + ((t)*CARD_X);

			children.at(i)->setPosition(tmp);
			children.at(i)->balanceNodePos();
		}
		else
		{	
			tmp.ry() = this->getPosition().y() + (CARD_Y +CARD_GAP_Y);
			t = abs(halfsize-i);
				
			if(i<halfsize)
			{
				tmp.rx() = this->getPosition().x()-((t-1)*CARD_X)-(CARD_X/2);
			}
			else
			{
				t++;
				tmp.rx() = this->getPosition().x()+((t-1)*CARD_X)+(CARD_X/2);
			}
			children.at(i)->setPosition(tmp);
			children.at(i)->balanceNodePos();	
		}
		if(parent)
		{
			tmp_2 = parent->getChildren().indexOf(this);

			for(int k =0 ; k<tmp_2;k++)
			{
				if(parent->getChildren()[k]->search(tmp))
				{	
					if(tmp_2 < ((parent->getChildren().size())/2)+odd)
					{
						
						for(int j = 0;j< tmp_2;j++)
						{
							tmp.setX(parent->getChildren().at(j)->getPosition().x() - CARD_X);
							tmp.setY(parent->getChildren().at(j)->getPosition().y());
							parent->getChildren().at(j)->setPosition(tmp);
							parent->getChildren().at(j)->balanceNodePos();
						}
					}
					else
					{
						for(int j =(parent->getChildren().size()-1);j>=tmp_2;j--)
						{
							tmp.setX(parent->getChildren().at(j)->getPosition().x() + CARD_X);
							tmp.setY(parent->getChildren().at(j)->getPosition().y());
							parent->getChildren().at(j)->setPosition(tmp);
						}
						//tmp.setX(this->getPosition().x() + CARD_X);
						//tmp.setY(this->getPosition().y());
						//this->setPosition(tmp);
						this->balanceNodePos();
					}			
				}	
			}
		}
	}
}
*/
void Gate::remove()
{
	if(getProperties().getKeep())
	{
		if(parent)
			this->detach();
		while (children.size())
			children[0]->remove();
		getProperties().setKeep(false);
		return ;
	}
	for (int i = 0; i < children.size(); ++i)
			children[i]->remove();
	delete this;
}