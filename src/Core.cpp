
#include "Core.hpp"

Core::Core(void)
{
	return ;
}

Core::Core(Core const &src)
{
	*this = src;
	return ;
}

Core::~Core(void)
{
	return ;
}


int
Core::sdlError(int code)
{
	std::cerr << "(" << code << ") " << "SDL Error: " << SDL_GetError() << std::endl;
	return (code);
}

void
Core::onMouseButton(SDL_MouseButtonEvent const &e)
{
	this->camera->onMouseButton(e);
}

void
Core::onMouseMotion(SDL_MouseMotionEvent const &e)
{
	this->camera->onMouseMotion(e);
}

void
Core::onMouseWheel(SDL_MouseWheelEvent const &e)
{
	this->camera->onMouseWheel(e);
}

void
Core::onKeyboard(SDL_KeyboardEvent const &e)
{
	this->camera->onKeyboard(e);
}

int
Core::init(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (sdlError(0));
	this->window_width = 1400;
	this->window_height = 1400;
	this->window = SDL_CreateWindow("Template",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									this->window_width,
									this->window_height,
									SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (this->window == NULL)
		return (sdlError(0));
	if (!(this->context = SDL_GL_CreateContext(this->window)))
		return (sdlError(0));
	SDL_SetRelativeMouseMode(SDL_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (float)(this->window_width / this->window_height), 0.1, 100.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	this->camera = new Camera(Vec3<float>(0.0f, 0.0f, 0.0f));
	glMatrixMode(GL_PROJECTION);
	return (1);
}

void
Core::renderAxes(void)
{
	glBegin(GL_LINES);
	// X red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void
Core::update(Uint32 const &elapsed_time)
{
	this->camera->animate(elapsed_time);
}

void
Core::render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// --------------------------------------
// 3D
// --------------------------------------
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	this->camera->look();
	this->renderAxes();
	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
	glMatrixMode(GL_MODELVIEW);
	// --------------------------------------
	glFlush();
}

void
Core::loop(void)
{
	SDL_Event		e;
	int32_t			quit;
	Uint32			current_time = 0;
	Uint32			elapsed_time = 0;
	Uint32			last_time = 0;
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					onMouseButton(e.button);
					break;
				case SDL_MOUSEBUTTONUP:
					onMouseButton(e.button);
				case SDL_MOUSEMOTION:
					onMouseMotion(e.motion);
					break;
				case SDL_MOUSEWHEEL:
					onMouseWheel(e.wheel);
					break;
				case SDL_KEYUP:
					onKeyboard(e.key);
					break;
				case SDL_KEYDOWN:
					onKeyboard(e.key);
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						quit = 1;
					break;
			}
		}
		current_time = SDL_GetTicks();
		elapsed_time = current_time - last_time;
		last_time = current_time;
		SDL_SetWindowTitle(window, "HumanGL");
		this->update(elapsed_time);
		this->render();
		SDL_GL_SwapWindow(this->window);
	}
}

Core &
Core::operator=(Core const &rhs)
{
	if (this != &rhs)
	{
		// copy members here
	}
	return (*this);
}

std::ostream &
operator<<(std::ostream &o, Core const &i)
{
	o	<< "Core: " << &i;
	return (o);
}
