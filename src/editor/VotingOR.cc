#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"
#include "CopyVisitor.hh"

VotingOR::VotingOR(QString name) : Gate(name), k(1) , subTree(nullptr)
{}

VotingOR::VotingOR(VotingOR& cop) : Gate(cop.getProperties().getName()) ,k(cop.getK()) , subTree(cop.getSubTree())
{}


VotingOR::~VotingOR()
{}


void VotingOR::updateSubTree()
{
	subTree = generateComb(0,k,children.size());	
}

Gate* VotingOR::generateComb(int i,int k,int n)
{
	Gate *t;
	Gate *t2;
	CopyVisitor v;
	//Node *c;
	int j = 0;

	if(n == 1)
	{
		return nullptr;
	}

	if(k==1 || (k==n))
	{
		if(k == 1)
		{
			t = new Or("");
		}
		else
		{
			t = new And("");
		}
		for(j=0;j<n;j++)
		{
			/*
			if(dynamic_cast<Container>(children.at(i+j)))
				c = new Container(dynamic_cast<Container>(children.at(i+j)));
			if(dynamic_cast<Transfert>(children.at(i+j)))
				c = new Transfert(dynamic_cast<Transfert>(children.at(i+j)));
			if(dynamic_cast<And>(children.at(i+j)))
				c = new And(dynamic_cast<And>(children.at(i+j)));
			if(dynamic_cast<Or>(children.at(i+j)))
				c = new Or(dynamic_cast<Or>(children.at(i+j)));
			if(dynamic_cast<Xor>(children.at(i+j)))
				c = new Xor(dynamic_cast<Xor>(children.at(i+j)));
			if(dynamic_cast<Inhibit>(children.at(i+j)))
				c = new Inhibit(dynamic_cast<Inhibit>(children.at(i+j)));
			if(dynamic_cast<VotingOR>(children.at(i+j)))
				c = new VotingOR(dynamic_cast<VotingOR>(children.at(i+j)));
			*/
			
			//c = new Node(children.at(i+j));
			//c->attach(t);
			this->children.at(i+j)->accept(v);
			v.getCopied()->attach(t);
			v.setCopied(nullptr);
			//this->children.at(i+j)->attach(t);//cannot attach , children already has a parent. 
			//delete c;

		}
		return t;
	}

	t = new Or("");
	for(j=0; j< n-k;j++)
	{
		t2 = new And("");
		t2->attach(t);
		//c = new Node(children.at(i+j));
		
		/*
		if(dynamic_cast<Container>(children.at(i+j)))
			c = new Container(dynamic_cast<Container>(children.at(i+j)));
		if(dynamic_cast<Transfert>(children.at(i+j)))
			c = new Transfert(dynamic_cast<Transfert>(children.at(i+j)));
		if(dynamic_cast<And>(children.at(i+j)))
			c = new And(dynamic_cast<And>(children.at(i+j)));
		if(dynamic_cast<Or>(children.at(i+j)))
			c = new Or(dynamic_cast<Or>(children.at(i+j)));
		if(dynamic_cast<Xor>(children.at(i+j)))
			c = new Xor(dynamic_cast<Xor>(children.at(i+j)));
		if(dynamic_cast<Inhibit>(children.at(i+j)))
			c = new Inhibit(dynamic_cast<Inhibit>(children.at(i+j)));
		if(dynamic_cast<VotingOR>(children.at(i+j)))
			c = new VotingOR(dynamic_cast<VotingOR>(children.at(i+j)));
		
		*/
		//c->attach(t2);
		this->children.at(i+j)->accept(v);
		v.getCopied()->attach(t2);
		v.setCopied(nullptr);
		//this->children.at(i+j)->attach(t2);//cannot attach , children already has a parent.
		//delete c;
		this->generateComb(i+j+1,k-1,n-j-1)->attach(t2);
	}
	this->generateComb(i+n-k,k,k)->attach(t);
	return t;
	
}


int VotingOR::getK()const
{
    return k;
}

void VotingOR::setK(int k)
{
    this->k = k;
}

Gate* VotingOR::getSubTree()const
{
    return subTree;
}


bool VotingOR::check(QList<QString>& errors)
{
	if (children.size() < k)
	{
		errors << prop.getName() + ": k value must be less or equal children value.";
		return (false);
	}
	if(children.size() < 2)
	{
		errors << prop.getName() + ": must have a least 2 children.";
		return(false);
	}
	for (int i = 0; i < children.size(); ++i)
		children.at(i)->check(errors);
	return (errors.size() > 0);
}


void VotingOR::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}

double VotingOR::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}