
Linhas e erros causados
mStateStack.top()->Update(mDeltaTime);
-> malloc(): unaligned tcache chunk detected

mStateStack.top()->Update(mDeltaTime);
-> Segmentation fault (core dumped)

SDL_RenderPresent(mRenderer);
-> Segmentation fault (core dumped)

mStateStack.top()->Update(mDeltaTime);
-> Aborted (core dumped)

mStateStack.pop();
-> Segmentation fault (core dumped)