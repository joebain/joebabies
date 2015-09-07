## All the Lua things ##

A nice part about the engine so far is supposed to be the Lua integration. Here is a quick rundown of that.

At the moment there must be a lua file called 'grind.lua' and it must contain or link to two functions.

### Functions you must write ###

**start(world)**

This should set everything in the game world up, or as much as you would like to set up. This is the one and only reference to the world you'll get too so it needs to be kept as a global variable probably.

**step(delta)**

This gets called approximately every 33 ms which should get us 30fps ish. This might get changed later but the important bit is the _delta_. This gives you the amount in seconds since the last call to step(), so the action should be smooth even with a choppy framerate.

### Functions you can call ###

These are all defined in LuaBinder.cpp so if this list gets out of date look there.

  * **World**
    * _get\_display()_ - Get the display.
    * _get\_block\_factory()_ - Get the block factory.
    * _get\_buttons()_ - Get the buttons, information about button presses.
    * _new\_audio\_file(string name, bool is\_music)_ - Create a new AudioFile object, will look in audio sub-directory for name + .ogg if is\_music is true, .wav if it's false.

  * **Display**
    * _get\_camera()_ - Get the camera.

  * **Camera**
    * _follow(Block3D subject)_ - Set the camera to follow a block (i.e. a character)

  * **BlockFactory**
    * _Block3D new\_block3d(string object, string texture)_ - Create a new block and add it too the world.
    * _Block3D new\_character(string object, string texture)_ - Create a new character. Characters are actually blocks but a flag is set so they move forward along the direction they are facing. A normal block is moved always in world coords and rotated on the spot.
    * _Block2D new\_blockHUD(Vector2f size, string texture)_ - A HUD style sprite. At the moment the transparent colour is black so you can only use near black in the textures. I will change this at some point.
    * _Block2DText new\_blockText(Vector2f pos, Vector2f size, string text, string font)_ - A HUD style piece of text.
    * _Floor new\_floor(string height\_map, string texture, float scale)_ - The floor. The height map is just a text file. See _simple\_hmap_ for an example.
    * _Sky new\_sky(string texture)_ - The sky.

  * **Buttons**
> > Holds members which indicate whether a key is being pressed. Currently:
    * up, down, left, right

  * **Sky**
    * _set\_scale(float scale)_ - Resize the sky.

  * **Floor**
    * _get\_height(Vector2f pos)_ - Get the height of the floor at this position.

  * **Block3D**
    * _move(Vector3f)_ - Move along this vector.
    * _rotate(Vector3f)_ - Rotate around the x, y and z axes by these amounts.
    * _Vector3f get\_pos()_ - Get the position.
    * _set\_pos(Vector3f pos)_ - Set the position.

  * **Block2D**
    * _move(Vector3f)_ - Move along this vector.
    * _rotate(Vector3f)_ - Rotate around the x, y and z axes by these amounts.
    * _set\_depth(float depth)_ - Alters the depth, for making sure the right sprites are on top.
    * _set\_tex\_size(Vector2f size)_ - Set the number of times a texture will repeat in the x and y. This is (1,1) by default.

  * **VectorNx**
    * _Constructor()_ - These can be constructed by passing the appropriate number of values.
    * _x, y, z_ - Read and write the coordinates.

  * **AudioFile**
    * _play()_ - Plays the audio sample.
    * _play\_loop(int times) - Plays the sample times+1 times. -1 gives infinite repeat.
    *_stop()