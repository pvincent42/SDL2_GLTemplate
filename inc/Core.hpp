
#ifndef		CORE_HPP
# define	CORE_HPP

# include <iostream>
# include <stdint.h>
# include "Camera.hpp"

class Core
{
public:
	SDL_Window *		window;
	SDL_GLContext		context;
	uint32_t			window_width;
	uint32_t			window_height;
	Camera				*camera;
	Core(void);
	~Core(void);

	int					init(void);
	int					sdlError(int code);
	void				onMouseButton(SDL_MouseButtonEvent const &e);
	void				onMouseMotion(SDL_MouseMotionEvent const &e);
	void				onMouseWheel(SDL_MouseWheelEvent const &e);
	void				onKeyboard(SDL_KeyboardEvent const &e);
	void				renderAxes(void);
	void				update(Uint32 const &elapsed_time);
	void				render(void);
	void				loop(void);

	Core				&operator=(Core const &rhs);

private:
	Core(Core const &src);
};

std::ostream				&operator<<(std::ostream &o, Core const &i);

#endif
