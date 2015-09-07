# Introduction #

This is a list of all the stuff that needs to be done in the engine.


# Details #

  * ~~make 2d blocks just 2d - take out all the vector3f stuff~~
  * ~~collision checks~~
  * make it easy to view a cage from above
  * better transparency:
    * different transparent colour
    * or proper transparency (look into SDL\_image maybe)
  * allow removing objects and sprites from the world

  * ~~Fix the 'stuff doesn't appear bug' - Very important~~ - done!
  * ~~Sound and music~~ - done!
  * Animation for objects and sprites
  * ~~Transparency for 2D sprites~~ ~~(actually its not quite working)~~ it is, it was just lighting problems which are now fixed
  * ~~2D text (for huds)~~
  * ~~Skybox~~ kind of done, not exactly beautiful and ~~floors~~ ~~(improvements are happening with the floors)~~ floors are so done!
  * ~~Timing - make each call to 'step()' pass the amount of intervening time~~ done!
  * ~~Make sure all the things in the world are operating with the same coords~~ They are
  * Maybe quarternion rotations (yeah right)
  * Maybe some anti aliasing or toon shading - something to make it look nice
  * ~~Improve the camera - less rigid / fixed~~ done
  * ~~Make it possible to press forward and left at the same time~~
  * Come up with some way of using lua to script the animals behaviour
  * Make the grass dance

# and some stuff in lua #

  * make dialogues better:
    * dont split words over lines
    * allow multi box speech
  * add menus
  * some way to load/store levels