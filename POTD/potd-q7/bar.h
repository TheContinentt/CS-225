// your code here
#ifndef BAR_H
#define BAR_H

#include <string>
#include "foo.h"
using namespace std;

namespace potd
{
	class bar
	{
		public:
			bar(string);
			bar (const bar &);
			bar & operator=(const bar &);
			~bar();
			string get_name();
		private:
			foo *f_;
	};
}
#endif
