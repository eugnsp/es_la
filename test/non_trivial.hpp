#pragma once

struct Non_trivial
{
	Non_trivial()
	{}

	Non_trivial(int i) : i(i)
	{}

	Non_trivial(const Non_trivial& nt) : i(nt.i)
	{}

	Non_trivial(Non_trivial&& nt) : i(nt.i)
	{}

	~Non_trivial()
	{}

	Non_trivial& operator=(const Non_trivial& nt)
	{
		i = nt.i;
		return *this;
	}

	Non_trivial& operator=(Non_trivial&& nt)
	{
		i = nt.i;
		return *this;
	}

	bool operator!=(Non_trivial nt) const
	{
		return i != nt.i;
	}

	bool operator==(Non_trivial nt) const
	{
		return i == nt.i;
	}

	int i = 0;
};
