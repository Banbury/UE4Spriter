# UE4Spriter
An Unreal Engine 4 plugin for [Spriter](http://brashmonkey.com).

Spriter is a software to create cut-out style animations for 2D games. UE4Spriter allows to import those animations and play them back. The animation is created procedurally at runtime. No spritesheets are used.

## Usage
UE4Spriter provides a Spriter Component that renders the Spriter animations. The Spriter project file and sprites are imported as assets in the Unreal Engine editor. This way everything will be packaged with the game.
The Unreal Engine project comes with a simple sample level, that shows how to use the Spriter component.

### Importing Assets
The Spriter project file and the sprites for the animation have to be imported into the UE project. The Spriter project can be imported like any other asset via the Import button in the Content Browser.

The Sprites have to be in the same folder structure as in the original Spriter project, but can be stored in any folder otherwise. The location of the sprites can be configured in the Spriter Component. The default value is 'Sprites' at the top level of the Content Browser (/Game/Sprites).

### Creating a Spriter Actor
Create a blueprint derived from any of the Actor classes and add a Spriter Component to it. The Spriter Component has several properties, that have to be configured.

* ***Texture Size***: This is the size of the texture, the sprites are rendered on. The texture needs to be big enough to display the whole animation. If parts of your animation are cut off, make these values bigger. Usually both value should be the same, or the animation will be squashed.

* ***Spriter Project***: Select the Spriter project, you have imported earlier. The drop down box should only show appropriate files.

* ***Sprites***: The folder containing the sprites for the animation. The path usually starts with `/Game`. This is the root of the games content folder.

* ***Animation***: This is the name of the animation, that should be played. The animation can be changed in blueprints.

### Using the Actor in Game
Place the blueprint actor in your scene as usual. You should see a placeholder image. If you cannot see the image, try rotating the actor. The image is only visible from one side.

### Blueprint functions
There are a number of Blueprint functions to control the animation. They can be found under the 'Spriter' category.

* ***ApplyCharacterMap***: This activates a character map defined in the Spriter project.
* ***RemoveCharacterMap***: This is the opposite of ApplyCharacterMap and removes a character map.
* ***RemoveAllCharacterMaps***: As the name says, the function removes all character maps previously applied.
* ***SetAnimation***: This changes the the animation of the Spriter character, but allows blending the animations.
* ***StopAnimation***: This stops the current animation.
* ***PlayAnimation***: Restarts the animation, after it has been stopped.
* ***GetTriggerCount***: Returns the number oft times a trigger has been activated. Should be used inside a tick event.

## Implementation Details
Currently the plugin only supports animations, but no sounds.

Unreal Engine is not well suited to render 2D animations, the way Spriter requires. The plugin does not use Paper2D. There is no built-in support for 2D physics yet. 

The Spriter animation is rendered onto a texture, that is in turn applied to a square plane. The texture is much larger, than it needs to be, to make certain, that it accomodates the whole animation. If your animated character is 'standing on' the origin in Spriter, about half of the texture will go unused. Keep this in mind, when placing the actor in the scene.

UE4Spriter uses a modified version of SpriterPlusPlus. The source code of these changes can be found [here](https://github.com/Banbury/SpriterPlusPlus/tree/cleanup).
