#include <iostream>
#include <memory>

using namespace std;
struct base: public std::enable_shared_from_this<base>
{
	int val;
	std::shared_ptr<base> share_more()
	{
		return shared_from_this();
	}
};

int main (int argc, char *argv[])
{
	auto sp1 = std::make_shared<base>();
	auto sp2 = sp1->share_more();
	sp1->val = 3;
	std::cout << "sp2->val == " << sp2->val << std::endl;
	std::cout << "sp1 count: " << sp1.use_count() << std::endl; 
	std::cout << "sp2 count: " << sp2.use_count() << std::endl;
	sp1.reset();
	std::cout << "sp1 count: " << sp1.use_count() << std::endl; 
	std::cout << "sp2 count: " << sp2.use_count() << std::endl;

	std::shared_ptr<int> p1(new(int));
	std::shared_ptr<int> p2 = p1;
	std::cout << "p1 count: " << p1.use_count() << std::endl; 
	std::cout << "p2 count: " << p2.use_count() << std::endl;
	p1.reset();
	std::cout << "p1 count: " << p1.use_count() << std::endl;
	p2.reset(); 
	std::cout << "p2 count: " << p2.use_count() << std::endl;


	return 0;
}

/* output:
sp2->val == 3
sp1 count: 2
sp2 count: 2
sp1 count: 0
sp2 count: 1
p1 count: 2
p2 count: 2
p1 count: 0
p2 count: 0

*/
	

