# include <iostream>
# include <limits.h>
# include <cstdlib>
# include "Core.hpp"

int
main(int argc, char **argv)
{
	Core		*core = new Core();


	std::cout << "Bonjour" << std::endl;
#ifdef linux
		glutInit(&argc, argv);
#else
		(void)argc;
		(void)argv;
#endif
		core->init();
		core->loop();
		return (0);
}
