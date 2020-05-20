#include "Gate.hh"
#include "VisitorNode.hh"
#include "EvalVisitor.hh"

VotingOR::VotingOR(QString name,bool keep) : Gate(name,keep), k(0) , subTree(nullptr)
{}

VotingOR::~VotingOR()
{}

void VotingOR::updateSubTree()
{
	if (subTree)
		subTree->remove();
	if (k > 0 && k <= children.size())
		subTree = (Gate*)generateComb(0,k,children.size());
	else
		subTree = nullptr;
}

Node* VotingOR::generateComb(int i,int k,int n)
{
	Gate *t;
	Gate *t2;

	if(n == 1)
		return children[i];
	if(k == 1 || k == n)
	{
		if (k == 1)
			t = new Or("", false);
		else
			t = new And("", false);
		for(int j = 0; j < n; ++j)
			t->getChildren() << children[i + j];
		return t;
	}
	t = new Or("", false);
	for(int j = 0; j < n - k; ++j)
	{
		t2 = new And("",false);
		t2->attach(t);
		t2->getChildren() << children[i + j];
		generateComb(i + j + 1, k - 1, n - j - 1)->attach(t2);
	}
	generateComb(i + n - k, k, k)->attach(t);
	return t;
}


int VotingOR::getK()const
{
    return k;
}

void VotingOR::setK(int k)
{
	this->k = 0;
	updateSubTree();
    this->k = k;
}

Gate* VotingOR::getSubTree()
{
	if (!subTree)
		updateSubTree();
    return subTree;
}

bool VotingOR::check(QList<QString>& errors)
{
	if (subTree)
	{
		subTree->remove();
		subTree = nullptr;
	}
	if (!k)
		errors << prop.getName() + ": k value must have a strictly positive value.";
	else if (children.size() < k)
	{
		errors << prop.getName() + ": k value must be less or equal children value.";
	}
	else if(children.size() < 2)
	{
		errors << prop.getName() + ": must have a least 2 children.";
	}
	for (int i = 0; i < children.size(); ++i)
		children.at(i)->check(errors);
	return (errors.size() == 0);
}

void VotingOR::remove()
{
	if(parent)
		this->detach();
	if(subTree)
		subTree->remove();
	while (children.size())
		children[0]->remove();
	if(getProperties().getKeep() == false)
		delete this;
	else
		getProperties().setKeep(false);
}

void VotingOR::accept(VisitorNode& visitor)
{
	visitor.visit(*this);
}

double VotingOR::accept(EvalVisitor& eval)
{
	return eval.visit(*this);
}
